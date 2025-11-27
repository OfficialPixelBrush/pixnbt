#pragma once
#include "tag.h"

class ByteTag : public Tag {
    private:
        int8_t data = 0;
    public:
        ByteTag(std::string pName, int8_t pData = 0) : Tag(pName){ this->data = pData; }
        void NbtPrintData() override {
            std::cout << "(Byte) " << GetName() << ": " << static_cast<int32_t>(data) << std::endl;
        }
        uint8_t GetTagId() override {
            return static_cast<uint8_t>(TAG_BYTE);
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
        }
        void Read(std::istringstream& stream) override {
            stream.get(reinterpret_cast<char&>(data));
        }
        int8_t GetData() {
            return data;
        }
};