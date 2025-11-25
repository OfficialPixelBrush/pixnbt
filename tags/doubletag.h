#pragma once
#include "tag.h"

class DoubleTag : public Tag {
    private:
        double data = 0;
    public:
        DoubleTag(std::string name, double data = 0) : Tag(name){ this->data = data; }
        void NbtPrintData() override {
            std::cout << "(Double) " << GetName() << ": " << std::fixed << data << std::dec << std::endl;
        }
        uint8_t GetTagId() override {
            return static_cast<uint8_t>(TAG_DOUBLE);
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint64_t writtenData = std::bit_cast<uint64_t>(data);
            writtenData = Swap64(writtenData);  // Swap bytes if needed
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
        void Read(std::istringstream& stream) override {
            uint64_t rawData;
            stream.read(reinterpret_cast<char*>(&rawData), sizeof(rawData));  // Read raw bytes for integer
            rawData = Swap64(rawData);
            data = std::bit_cast<double>(rawData);
        }
        double GetData() {
            return data;
        }
};