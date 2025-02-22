#pragma once
#include "tag.h"

class StringTag : public Tag {
    private:
        std::string data = "";
    public:
        StringTag(std::string name, std::string data = "") : Tag(name){ this->data = data; }
        void NbtPrintData() override {
            std::cout << "(String) " << GetName() << ": " << data << std::endl;
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_STRING;
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            stream << Swap16(data.size()) << data;
        }
        void Read(std::istringstream& stream) override {
            uint16_t stringSize;
            stream.read(reinterpret_cast<char*>(&stringSize), sizeof(stringSize));  // Read raw bytes for integer
            stringSize = Swap16(stringSize);
            std::string data(stringSize, '\0');
            stream.read(&data[0], stringSize);
        }
        std::string GetData() {
            return data;
        }
};