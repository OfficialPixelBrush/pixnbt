#pragma once
#include <libdeflate.h>
#include "tags/tag.h"
#include "tags/alltags.h"

enum CompressionAlgorithm : uint8_t {
    NBT_GZIP,
    NBT_ZLIB,
    NBT_UNCOMPRESSED
};

// Generic Stream
void NbtWrite(
    std::ofstream& stream,
    std::shared_ptr<Tag> tag,
    CompressionAlgorithm algorithm = NBT_GZIP
);
std::shared_ptr<Tag> NbtRead(
    std::istream& stream,
    CompressionAlgorithm algorithm = NBT_GZIP,
    size_t multiplier = 10,
    size_t maxSize = 0
);

std::vector<uint8_t> NbtCompressData(
    const std::vector<uint8_t>& inputData,
    CompressionAlgorithm algorithm = NBT_GZIP,
    int32_t level = 6
);