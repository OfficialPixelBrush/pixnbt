#pragma once
#include "tag.h"

class FloatTag : public Tag {
    private:
        float data = 0;
    public:
        FloatTag(std::string pName, float pData = 0) : Tag(pName){ this->data = pData; }
        void NbtPrintData() override {
            std::cout << "(Float) " << GetName() << ": " << std::fixed << data << std::dec << std::endl;
        }
        uint8_t GetTagId() override {
            return static_cast<uint8_t>(TAG_FLOAT);
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint32_t writtenData = std::bit_cast<uint32_t>(data);
            writtenData = Swap32(writtenData);  // Swap bytes if needed
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
        void Read(std::istringstream& stream) override {
            uint32_t rawData;
            stream.read(reinterpret_cast<char*>(&rawData), sizeof(rawData));  // Read raw bytes for integer
            rawData = Swap32(rawData);
            data = std::bit_cast<float>(rawData);
        }
        float GetData() {
            return data;
        }
};