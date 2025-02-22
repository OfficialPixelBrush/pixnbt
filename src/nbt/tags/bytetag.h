#pragma once
#include "tag.h"

class ByteTag : public Tag {
    private:
        int8_t data = 0;
    public:
        ByteTag(std::string name, int8_t data = 0) : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(Byte) " << GetName() << ": 0x" << std::hex << (int)data << std::dec << std::endl;
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_BYTE;
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
        }
};