#pragma once
#include "tag.h"

class ByteArrayTag : public Tag {
    private:
        std::vector<int8_t> data;
    public:
        ByteArrayTag(std::string name) : Tag(name){};
        ByteArrayTag(std::string name, std::vector<int8_t> data) : Tag(name){ this->data = data; }
        void NbtPrintData() override {
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
        uint8_t GetTagId() override {
            return (uint8_t)TAG_BYTE_ARRAY;
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint32_t writtenSize = Swap32(data.size());
            stream.write(reinterpret_cast<const char*>(&writtenSize), sizeof(writtenSize));
            for (const auto& d : data) {
                stream << d;
            }
        }
        void Read(std::istringstream& stream) override {
            uint32_t readSize;
            stream.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));  // Read raw bytes for integer
            readSize = Swap32(readSize);

            // Reserve the size beforehand
            data.reserve(readSize);

            for (uint32_t i = 0; i < readSize; i++) {
                uint8_t readData;
                stream.get(reinterpret_cast<char&>(readData));
                data.push_back(readData);
            }
        }
        std::vector<int8_t> GetData() {
            return data;
        }
};