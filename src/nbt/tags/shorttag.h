#pragma once
#include "tag.h"

class ShortTag : public Tag {
    private:
    int16_t data = 0;
    public:
        ShortTag(std::string name, int16_t data = 0) : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(Short) " << GetName() << ": " << (int)data << std::endl;
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_SHORT;
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint16_t writtenData = Swap16(data);
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
        void Read(std::istringstream& stream) override {
            uint16_t rawData;
            stream.read(reinterpret_cast<char*>(&rawData), sizeof(rawData));  // Read raw bytes for integer
            data = Swap16(rawData);
        }
};