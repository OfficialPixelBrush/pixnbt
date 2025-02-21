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
        uint8_t GetTagId() override {
            return (uint8_t)TAG_DOUBLE;
        }
        void Write(std::ofstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            stream.write(reinterpret_cast<const char*>(&data), sizeof(data));
        }
};