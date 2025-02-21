#pragma once
#include "tag.h"

class DoubleTag : public Tag {
    private:
        double data = 0;
    public:
        DoubleTag(std::string name, double data = 0) : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(Double) " << GetName() << ": " << std::fixed << data << std::dec << std::endl;
        }
};