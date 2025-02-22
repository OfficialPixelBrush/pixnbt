#pragma once
#include "tag.h"

class FloatTag : public Tag {
    private:
        float data = 0;
    public:
        FloatTag(std::string name, float data = 0) : Tag(name){ this->data = data; }
        void NbtPrintData() override {
            std::cout << "(Float) " << GetName() << ": " << std::fixed << data << std::dec << std::endl;
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_FLOAT;
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint32_t writtenData = *reinterpret_cast<uint32_t*>(&data);
            writtenData = Swap32(writtenData);  // Swap bytes if needed
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
        void Read(std::istringstream& stream) override {
            uint32_t rawData;
            stream.read(reinterpret_cast<char*>(&rawData), sizeof(rawData));  // Read raw bytes for integer
            rawData = Swap32(rawData);
            data = *reinterpret_cast<float*>(&rawData);
        }
};