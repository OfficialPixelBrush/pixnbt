#pragma once
#include "tag.h"

class IntTag : public Tag {
    private:
    int32_t data = 0;
    public:
        IntTag(std::string name, int32_t data = 0) : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(Int) " << GetName() << ": 0x" << std::hex << (int)data << std::dec << std::endl;
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
};