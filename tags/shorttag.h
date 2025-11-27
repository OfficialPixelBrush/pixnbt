#pragma once
#include "tag.h"

class ShortTag : public Tag {
    private:
        int16_t data = 0;
    public:
        ShortTag(std::string pName, int16_t pData = 0) : Tag(pName){ this->data = pData; }
        void NbtPrintData() override {
            std::cout << "(Short) " << GetName() << ": " << static_cast<int32_t>(data) << "\n";
        }
        uint8_t GetTagId() override {
            return static_cast<uint8_t>(TAG_SHORT);
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint16_t writtenData = Swap16(static_cast<uint16_t>(data));
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
        void Read(std::istringstream& stream) override {
            uint16_t rawData;
            stream.read(reinterpret_cast<char*>(&rawData), sizeof(rawData));  // Read raw bytes for integer
            data = static_cast<int16_t>(Swap16(rawData));
        }
        int16_t GetData() {
            return data;
        }
};