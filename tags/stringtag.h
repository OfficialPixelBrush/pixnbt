#pragma once
#include "tag.h"

class StringTag : public Tag {
    private:
        std::string data = "";
    public:
        StringTag(std::string name, std::string data = "") : Tag(name){ this->data = data; }
        void NbtPrintData() override {
            std::cout << "(String) " << GetName() << ": " << data << " (" << data.size() << ")" << std::endl;
        }
        uint8_t GetTagId() override {
            return static_cast<uint8_t>(TAG_STRING);
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint16_t writtenData = Swap16(static_cast<uint16_t>(data.size()));
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
            stream << data;
        }
        void Read(std::istringstream& stream) override {
            uint16_t stringSize;
            if (!stream.read(reinterpret_cast<char*>(&stringSize), sizeof(stringSize))) {
                return;
            }
            stringSize = Swap16(stringSize);
            std::string tempdata(stringSize, '\0');
            
            if (!stream.read(tempdata.data(), stringSize)) {
                std::cerr << "Failed to read from stream!" << std::endl;
                return;
            }
            data = tempdata;
        }
        std::string GetData() {
            return data;
        }
};