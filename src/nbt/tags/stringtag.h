#pragma once
#include "tag.h"

class StringTag : public Tag {
    private:
        std::string data = "";
    public:
        StringTag(std::string name, std::string data = "") : Tag(name){ this->data = data; }
        void PrintData() override {
            std::cout << "(String) " << GetName() << ": " << data << std::endl;
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_STRING;
        }
        void Write(std::ofstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            stream << data.size() << data;
        }
};