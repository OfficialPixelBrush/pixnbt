#pragma once
#include "tag.h"

class IntTag : public Tag {
    private:
    int32_t data = 0;
    public:
        IntTag(std::string name, int32_t data = 0) : Tag(name){ this->data = data; }
        void NbtPrintData() override {
            std::cout << "(Int) " << GetName() << ": " << (int)data << std::endl;
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_INT;
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint32_t writtenData = Swap32(data);
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
        void Read(std::istringstream& stream) override {
            uint32_t rawData;
            stream.read(reinterpret_cast<char*>(&rawData), sizeof(rawData));  // Read raw bytes for integer
            data = Swap32(rawData);
        }
};