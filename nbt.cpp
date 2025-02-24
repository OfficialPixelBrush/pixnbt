#include "nbt.h"

std::vector<uint8_t> NbtCompressData(const std::vector<uint8_t>& inputData, int level) {
    libdeflate_compressor* compressor = libdeflate_alloc_compressor(level);
    if (!compressor) {
        throw std::runtime_error("Failed to allocate libdeflate compressor");
    }

    // Allocate max possible compressed size
    size_t maxCompressedSize = libdeflate_gzip_compress_bound(compressor, inputData.size());
    std::vector<uint8_t> compressedData(maxCompressedSize);

    // Perform compression
    size_t actualSize = libdeflate_gzip_compress(compressor, 
                                                 inputData.data(), inputData.size(), 
                                                 compressedData.data(), compressedData.size());

    libdeflate_free_compressor(compressor);

    if (actualSize == 0) {
        throw std::runtime_error("Compression failed");
    }

    compressedData.resize(actualSize);  // Resize buffer to actual size
    return compressedData;
}

std::shared_ptr<Tag> NbtItem(int8_t slot, int16_t id, int8_t count, int16_t damage) {
	auto invSlot = std::make_shared<CompoundTag>(std::to_string((int)slot));
	invSlot->Put(std::make_shared<ByteTag> ("Slot"  , slot));
	invSlot->Put(std::make_shared<ShortTag>("id"    , id));
	invSlot->Put(std::make_shared<ByteTag> ("Count" , count));
	invSlot->Put(std::make_shared<ShortTag>("Damage", damage));
	return invSlot;
}

void NbtWriteToFile(std::string filename, std::shared_ptr<Tag> tag, bool compress) {
    std::ostringstream buffer(std::ios::binary);

	tag->Write(buffer,true);

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open output file\n";
        return;
    }
    if (compress) {
        std::string str = buffer.str();
        std::vector<uint8_t> inputData(str.begin(), str.end());
        std::vector<uint8_t> compressedData = NbtCompressData(inputData);

        file.write(reinterpret_cast<const char*>(compressedData.data()), compressedData.size());
    } else {
        file.write(buffer.str().c_str(), buffer.str().size());
    }
    file.close();
}

std::shared_ptr<Tag> NbtReadFromFile(std::string filename, bool compressed) {
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
    std::string decompressed_data;
    if (!compressed) {
        decompressed_data.assign(compressed_data.begin(), compressed_data.end());
    } else {
        // Step 1: Create decompressor
        libdeflate_decompressor* decompressor = libdeflate_alloc_decompressor();
        if (!decompressor) {
            std::cerr << "Failed to allocate libdeflate decompressor!" << std::endl;
            return nullptr;
        }

        // Step 2: Estimate decompressed size (adjust if needed)
        size_t estimated_size = size * 10; // Guessing the decompressed size
        decompressed_data.resize(estimated_size);

        // Step 3: Decompress
        size_t actual_size;
        libdeflate_result result = libdeflate_gzip_decompress(
            decompressor,
            compressed_data.data(), size,           // Input data
            decompressed_data.data(), estimated_size, // Output buffer
            &actual_size                              // Actual decompressed size
        );

        libdeflate_free_decompressor(decompressor);

        if (result != LIBDEFLATE_SUCCESS) {
            std::cerr << "Decompression failed!" << std::endl;
            return nullptr;
        }

        decompressed_data.resize(actual_size); // Trim to actual decompressed size
    }

    // Append a single null byte
    // End tag of above root
    decompressed_data.push_back('\0'); 
    
    std::istringstream iss(decompressed_data, std::ios::binary);

	auto overRoot = std::make_shared<CompoundTag>("");
    overRoot->Read(iss);
    auto root = *overRoot->GetTags().begin();
    if (!root) {
        std::cerr << "No root found!" << std::endl;
    }
    return root;
}

int8_t NbtConvertToSlot(int8_t slot) {
    // shift to hotbar
    if (slot >= 36) {
        return slot - 36;
    }
    // shift to rest(?)
    if (slot <= 8) {
        return slot + 35;
    }
    return 0;
}