#pragma once
#include <libdeflate.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include <algorithm>
#include "endian.h"
#include <sstream>

#include "tags/tag.h"
#include "tags/alltags.h"

// Compress binary data with libdeflate
std::vector<uint8_t> NbtCompressData(const std::vector<uint8_t>& inputData, int level = 6);
std::shared_ptr<Tag> NbtItem(int8_t slot, int16_t id, int8_t count, int16_t damage);
void NbtWriteToFile(std::string filename, std::shared_ptr<Tag> tag, bool compress = true);
std::shared_ptr<Tag> NbtReadFromFile(std::string filename, bool compressed = true);