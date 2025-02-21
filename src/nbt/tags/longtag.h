#pragma once
#include "tag.h"

class LongTag : public Tag {
    private:
    int64_t data = 0;
    public:
        LongTag(std::string name, int64_t data = 0) : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(Long) " << GetName() << ": 0x" << std::hex << data << std::dec << std::endl;
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_LONG;
        }
        void Write(std::ofstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint64_t writtenData = Swap64(data);
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
};