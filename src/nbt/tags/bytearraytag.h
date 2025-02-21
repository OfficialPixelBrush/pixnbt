#pragma once
#include "tag.h"

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
        uint8_t GetTagId() override {
            return (uint8_t)TAG_BYTE_ARRAY;
        }
        void Write(std::ofstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            int32_t size = static_cast<int32_t>(data.size());
            stream.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (const auto& d : data) {
                stream << d;
            }
        }
};