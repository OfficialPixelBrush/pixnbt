#pragma once
#include "tag.h"

class FloatTag : public Tag {
    private:
        float data = 0;
    public:
        FloatTag(std::string name, float data = 0) : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(Float) " << GetName() << ": " << std::fixed << data << std::dec << std::endl;
        }
};