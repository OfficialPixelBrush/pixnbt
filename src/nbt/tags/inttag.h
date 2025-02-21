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
};