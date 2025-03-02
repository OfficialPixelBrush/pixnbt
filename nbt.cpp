#include "nbt.h"

std::vector<uint8_t> NbtCompressData(const std::vector<uint8_t>& inputData, int algorithm, int level) {
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

void NbtWriteToFile(std::string filename, std::shared_ptr<Tag> tag, int algorithm) {
    std::ostringstream buffer(std::ios::binary);

	tag->Write(buffer,true);

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open output file\n";
        return;
    }
    if (algorithm == NBT_UNCOMPRESSED) {
        file.write(buffer.str().c_str(), buffer.str().size());
    } else {
        std::string str = buffer.str();
        std::vector<uint8_t> inputData(str.begin(), str.end());
        std::vector<uint8_t> compressedData = NbtCompressData(inputData,algorithm);

        file.write(reinterpret_cast<const char*>(compressedData.data()), compressedData.size());
    }
    file.close();
}

std::shared_ptr<Tag> NbtReadFromFile(std::string filename, int algorithm) {
    // Open the file in binary mode
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: File is not open!" << std::endl;
        return nullptr;
    }

    // Read the entire file into memory
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> compressed_data(size);
    file.read(reinterpret_cast<char*>(compressed_data.data()), size);
    file.close();

    // If not compressed, use the data as is
    size_t estimated_size = size * 25;
    std::vector<uint8_t> decompressed_data(estimated_size);
    libdeflate_result result;
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

std::shared_ptr<Tag> NbtItem(int8_t slot, int16_t id, int8_t count, int16_t damage) {
	auto invSlot = std::make_shared<CompoundTag>(std::to_string((int)slot));
	invSlot->Put(std::make_shared<ByteTag> ("Slot"  , slot));
	invSlot->Put(std::make_shared<ShortTag>("id"    , id));
	invSlot->Put(std::make_shared<ByteTag> ("Count" , count));
	invSlot->Put(std::make_shared<ShortTag>("Damage", damage));
	return invSlot;
}

int8_t NbtConvertToSlot(int8_t slot) {
    // Hotbar slots in NBT
    if (slot >= 36 && slot <= 44) {
        return slot - 36;
    }
    // Hotbar slots in GUI
    if (slot >= 0 && slot <= 8) {
        return slot + 36;
    }
    // Preserve main inventory slots (9-35)
    return slot;
}