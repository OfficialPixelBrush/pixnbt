#pragma once
#include "tag.h"
#include <vector>

class ByteArrayTag : public Tag {
    private:
        std::vector<int8_t> data;
    public:
        ByteArrayTag(std::string name, std::vector<int8_t> data) : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(ByteArray) " << GetName() << ": " << data.size() << std::endl;
            std::cout << std::hex << "(";
            for (size_t i = 0; i < data.size(); ++i) {
                std::cout << "0x" << (int)((uint8_t)data[i]);
                if (i < data.size() - 1) {
                    std::cout << ",";
                }
            }
            std::cout << ")" << std::dec << std::endl;
        }
};