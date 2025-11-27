#pragma once
#include "tag.h"

class StringTag : public Tag {
    private:
        std::string data = "";
    public:
        StringTag(std::string pName, std::string pData = "") : Tag(pName){ this->data = pData; }
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
            std::string tempData(stringSize, '\0');
            
            if (!stream.read(tempData.data(), stringSize)) {
                std::cerr << "Failed to read from stream!" << std::endl;
                return;
            }
            data = tempData;
        }
        std::string GetData() {
            return data;
        }
};