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
            uint64_t writtenData = *reinterpret_cast<uint64_t*>(&data);
            writtenData = Swap64(writtenData);  // Swap bytes if needed
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
};