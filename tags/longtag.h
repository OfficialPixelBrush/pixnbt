#pragma once
#include "tag.h"

class LongTag : public Tag {
    private:
        int64_t data = 0;
    public:
        LongTag(std::string name, int64_t data = 0) : Tag(name){ this->data = data; }
        void NbtPrintData() override {
            std::cout << "(Long) " << GetName() << ": " << data << std::endl;
        }
        uint8_t GetTagId() override {
            return static_cast<uint8_t>(TAG_LONG);
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            uint64_t writtenData = Swap64(static_cast<uint64_t>(data));
            stream.write(reinterpret_cast<const char*>(&writtenData), sizeof(writtenData));
        }
        void Read(std::istringstream& stream) override {
            uint64_t rawData;
            stream.read(reinterpret_cast<char*>(&rawData), sizeof(rawData));  // Read raw bytes for integer
            data = static_cast<int64_t>(Swap64(rawData));
        }
        int64_t GetData() {
            return data;
        }
};