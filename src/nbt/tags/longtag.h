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
};