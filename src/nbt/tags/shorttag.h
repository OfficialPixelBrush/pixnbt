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
};