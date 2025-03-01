#pragma once
#include <libdeflate.h>
#include "tags/tag.h"
#include "tags/alltags.h"

enum CompressionAlgorithm {
    NBT_GZIP,
    NBT_ZLIB,
    NBT_UNCOMPRESSED
};

// Compress binary data with libdeflate
void NbtWriteToFile(std::string filename, std::shared_ptr<Tag> tag, int algorithm = NBT_GZIP);
std::shared_ptr<Tag> NbtReadFromFile(std::string filename, int algorithm = NBT_GZIP);

std::vector<uint8_t> NbtCompressData(const std::vector<uint8_t>& inputData, int algorithm = NBT_GZIP, int level = 6);

std::shared_ptr<Tag> NbtItem(int8_t slot, int16_t id, int8_t count, int16_t damage);
int8_t NbtConvertToSlot(int8_t slot);