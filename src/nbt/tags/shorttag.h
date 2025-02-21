#pragma once
#include "tag.h"

class ShortTag : public Tag {
    private:
    int16_t data = 0;
    public:
        ShortTag(std::string name, int16_t data = 0) : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(Short) " << GetName() << ": 0x" << std::hex << (int)data << std::dec << std::endl;
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_SHORT;
        }
        void Write(std::ofstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
        }
};