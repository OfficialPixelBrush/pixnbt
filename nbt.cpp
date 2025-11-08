#include "nbt.h"

std::vector<uint8_t> NbtCompressData(const std::vector<uint8_t>& inputData, CompressionAlgorithm algorithm, int level) {
    libdeflate_compressor* compressor = libdeflate_alloc_compressor(level);
    if (!compressor) {
        throw std::runtime_error("Failed to allocate libdeflate compressor");
    }

    // Allocate max possible compressed size
    size_t maxCompressedSize;
    size_t actualSize;
    std::vector<uint8_t> compressedData;
    if (algorithm == NBT_GZIP) {
        maxCompressedSize = libdeflate_gzip_compress_bound(compressor, inputData.size());
        compressedData.resize(maxCompressedSize);

        // Perform compression
        actualSize = libdeflate_gzip_compress(compressor, 
                                                    inputData.data(), inputData.size(), 
                                                    compressedData.data(), compressedData.size());
    } else if (algorithm == NBT_ZLIB) {
        maxCompressedSize = libdeflate_zlib_compress_bound(compressor, inputData.size());
        compressedData.resize(maxCompressedSize);

        // Perform compression
        actualSize = libdeflate_zlib_compress(compressor, 
                                                    inputData.data(), inputData.size(), 
                                                    compressedData.data(), compressedData.size());
    } else {
        maxCompressedSize = inputData.size();
        actualSize = inputData.size();
        compressedData = inputData;
    }

    libdeflate_free_compressor(compressor);

    if (actualSize == 0) {
        throw std::runtime_error("Compression failed");
    }

    compressedData.resize(actualSize);  // Resize buffer to actual size
    return compressedData;
}

void NbtWrite(std::ofstream& stream, std::shared_ptr<Tag> tag, CompressionAlgorithm algorithm) {
    if (!stream.is_open()) {
        std::cerr << "Error: Failed to open stream or invalid stream!" << std::endl;
        return;
    }
    // Creat temporary buffer
    std::ostringstream buffer(std::ios::binary);
	tag->Write(buffer,true);
    // Write to stream
    if (algorithm == NBT_UNCOMPRESSED) {
        stream.write(buffer.str().c_str(), static_cast<std::streamsize>(buffer.str().size()));
    } else {
        std::string str = buffer.str();
        std::vector<uint8_t> inputData(str.begin(), str.end());
        std::vector<uint8_t> compressedData = NbtCompressData(inputData,algorithm);

        stream.write(reinterpret_cast<const char*>(compressedData.data()), static_cast<std::streamsize>(compressedData.size()));
    }
}

std::shared_ptr<Tag> NbtRead(std::istream& stream, CompressionAlgorithm algorithm, size_t multiplier, size_t maxSize) {
    // Open the file in binary mode
    if (!stream) {
        std::cerr << "Error: Failed to open stream or invalid stream!" << std::endl;
        return nullptr;
    }

    // Read the entire file into memory
    stream.seekg(0, std::ios::end);
    std::streamsize ssize = stream.tellg();
    if (ssize <= 0) {
        std::cerr << "Error: Invalid or empty stream!" << std::endl;
        return nullptr;
    }
    size_t size = static_cast<size_t>(ssize);
    stream.seekg(0, std::ios::beg);

    std::vector<uint8_t> compressed_data(size);
    stream.read(reinterpret_cast<char*>(compressed_data.data()), ssize);

    // If not compressed, use the data as is
    size_t estimated_size;
    if (maxSize == 0 && multiplier != 0) {
        estimated_size = size * multiplier;
    } else {
        estimated_size = maxSize;
    }
    std::vector<uint8_t> decompressed_data(estimated_size);
    libdeflate_result result = LIBDEFLATE_SUCCESS;
    if (algorithm == NBT_UNCOMPRESSED) {
        decompressed_data.assign(compressed_data.begin(), compressed_data.end());
    } else {
        libdeflate_decompressor* decompressor = libdeflate_alloc_decompressor();
        if (!decompressor) {
            std::cerr << "Failed to allocate libdeflate decompressor!" << std::endl;
            return nullptr;
        }

        size_t actual_size;
        if (algorithm == NBT_GZIP) {
            result = libdeflate_gzip_decompress(
                decompressor,
                compressed_data.data(), size,           // Input data
                decompressed_data.data(), estimated_size, // Output buffer
                &actual_size                              // Actual decompressed size
            );
        } else if (algorithm == NBT_ZLIB) {
            result = libdeflate_zlib_decompress(
                decompressor,
                compressed_data.data(), size,           // Input data
                decompressed_data.data(), estimated_size, // Output buffer
                &actual_size                              // Actual decompressed size
            );
        }

        libdeflate_free_decompressor(decompressor);

        if (result != LIBDEFLATE_SUCCESS) {
            std::cerr << "Decompression failed! (" << result << ")" << std::endl;
            return nullptr;
        }

        decompressed_data.resize(actual_size); // Trim to actual decompressed size
    }

    // Append a single null byte
    // End tag of above root
    decompressed_data.push_back('\0'); 

    std::string_view decompressed_str(reinterpret_cast<const char*>(decompressed_data.data()), decompressed_data.size());
    std::istringstream iss(std::string(decompressed_str), std::ios::binary);

	auto overRoot = std::make_shared<CompoundTag>("");
    overRoot->Read(iss);
    auto root = *overRoot->GetTags().begin();
    if (!root) {
        std::cerr << "No root found!" << std::endl;
    }
    return root;
}