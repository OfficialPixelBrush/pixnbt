#pragma once
#include <libdeflate.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include <algorithm>
#include "endian.h"
#include <sstream>
#include <bit>

enum Tags {
    TAG_END         =  0,
    TAG_BYTE        =  1,
    TAG_SHORT       =  2,
    TAG_INT         =  3,
    TAG_LONG        =  4,
    TAG_FLOAT       =  5,
    TAG_DOUBLE      =  6,
    TAG_BYTE_ARRAY  =  7,
    TAG_STRING      =  8,
    TAG_LIST        =  9,
    TAG_COMPOUND    = 10,
    TAG_INT_ARRAY   = 11
};

class Tag {
    private:
        std::string name = "";
    public:
        virtual ~Tag() = default;  
        virtual uint8_t GetTagId() = 0;
        virtual void Write(std::ostringstream& stream, bool primary = true) = 0;
        virtual void Read(std::istringstream& stream) = 0;
        virtual void NbtPrintData() {
            std::cout << "(Tag) " << GetName() << ": " << "RAW" << std::endl;
        };
        Tag(std::string pName = "") { this->name = pName; }

        std::string GetName() { return name; }
        Tag* SetName(std::string pName) {
            this->name = pName;
            return this;
        }

        void WriteHeader(std::ostringstream& stream) {
            stream << GetTagId();
            uint16_t nameSize = Swap16(static_cast<uint16_t>(name.size())); 
            stream.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
            stream << name;
        };
};

std::shared_ptr<Tag> NewTag(uint8_t type, std::string name = "");
std::string GetTagName(int8_t type);