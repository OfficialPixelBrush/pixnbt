#pragma once
#include "tag.h"

class IntTag : public Tag {
    private:
    int32_t data = 0;
    public:
        IntTag(std::string pName, int32_t pData = 0) : Tag(pName){ this->data = pData; }
        void NbtPrintData() override {
            std::cout << "(Int) " << GetName() << ": " << static_cast<int32_t>(data) << "\n";
        }
        uint8_t GetTagId() override {
            return  static_cast<uint8_t>(TAG_INT);
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint32_t writtenData = Swap32(static_cast<uint32_t>(data));
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
        void Read(std::istringstream& stream) override {
            uint32_t rawData;
            stream.read(reinterpret_cast<char*>(&rawData), sizeof(rawData));  // Read raw bytes for integer
            data = static_cast<int32_t>(Swap32(rawData));
        }
        int32_t GetData() {
            return data;
        }
};