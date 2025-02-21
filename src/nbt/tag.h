#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include <memory>

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
        Tag(std::string name = "");
        std::string GetTagName(int8_t type);

        Tag* ReadNamedTag(std::ifstream stream);
        void WriteNamedTag(Tag tag, std::ofstream stream);
        Tag* SetName(std::string name);
        std::string GetName();
        virtual void PrintData() {
            std::cout << "(Tag) " << GetName() << ": " << "RAW" << std::endl;
        };
        void Write(std::ofstream stream);
        void Read(std::ifstream stream);
};