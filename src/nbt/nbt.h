#pragma once
#include "tags/alltags.h"

// Compress binary data with libdeflate
std::vector<uint8_t> compressData(const std::vector<uint8_t>& inputData, int level = 6) {
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

std::shared_ptr<Tag> Item(int8_t slot, int16_t id, int8_t count, int16_t damage) {
	auto invSlot = std::make_shared<CompoundTag>(std::to_string((int)slot));
	invSlot->Put(std::make_shared<ByteTag> ("Slot"  , slot));
	invSlot->Put(std::make_shared<ShortTag>("id"    , id));
	invSlot->Put(std::make_shared<ByteTag> ("Count" , count));
	invSlot->Put(std::make_shared<ShortTag>("Damage", damage));
	return invSlot;
}

void WriteToFile(std::string filename, std::shared_ptr<Tag> tag, bool compress = true) {
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
        std::vector<uint8_t> compressedData = compressData(inputData);

        file.write(reinterpret_cast<const char*>(compressedData.data()), compressedData.size());
    } else {
        file.write(buffer.str().c_str(), buffer.str().size());
    }
    file.close();
}

std::shared_ptr<Tag> ReadFromFile(std::string filename, bool compressed = true) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: File is not open!" << std::endl;
        return nullptr;
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer(size, '\0');
    
    file.read(&buffer[0], size);
    file.close();
    
    std::istringstream iss(buffer, std::ios::binary);

	auto root = std::make_shared<CompoundTag>("");
    root->Read(iss);
    return root;
}