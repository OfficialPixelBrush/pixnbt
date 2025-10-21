#pragma once
#include "tag.h"

class ByteArrayTag : public Tag {
    private:
        std::vector<uint8_t> data;
    public:
        ByteArrayTag(std::string name) : Tag(name){};
        // When std::array is passed
        template <size_t N>
            ByteArrayTag(std::string name, const std::array<uint8_t, N>& arr)
                : Tag(std::move(name)), data(arr.begin(), arr.end()) {}
        // When std::vector is passed
        ByteArrayTag(std::string name, std::vector<uint8_t> data) : Tag(name){ this->data = data; }
        void NbtPrintData() override {
            std::cout << "(ByteArray) " << GetName() << ": " << data.size() << std::endl;
            std::cout << std::hex << "(";
            for (size_t i = 0; i < data.size(); ++i) {
                std::cout << "0x" << static_cast<int>(static_cast<uint8_t>(data[i]));
                if (i < data.size() - 1) {
                    std::cout << ",";
                }
            }
            std::cout << ")" << std::dec << std::endl;
        }
        uint8_t GetTagId() override {
            return static_cast<uint8_t>(TAG_BYTE_ARRAY);
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint32_t writtenSize = Swap32(static_cast<uint32_t>(data.size()));
            stream.write(reinterpret_cast<const char*>(&writtenSize), sizeof(writtenSize));
            stream.write(reinterpret_cast<const char*>(data.data()), static_cast<int32_t>(data.size()));
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
        std::vector<uint8_t> GetData() {
            return data;
        }
};