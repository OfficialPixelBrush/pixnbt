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
        /*
        Tag NewTag(int8_t type, std::string name) {
            switch(type) {
                case TAG_END:
                    return new End
                case TAG_BYTE:
                    return "Tag_Byte";
                case TAG_SHORT:
                    return "TAG_Short";
                case TAG_INT:
                    return "TAG_Int";
                case TAG_LONG:
                    return "TAG_Long";
                case TAG_FLOAT:
                    return "TAG_Float";
                case TAG_BYTE_ARRAY:
                    return "TAG_Byte_Array";
                case TAG_INT_ARRAY:
                    return "TAG_Int_Array";
                case TAG_STRING:
                    return "TAG_String";
                case TAG_LIST:
                    return "TAG_List";
                case TAG_COMPOUND:
                    return "TAG_Compound";
            }
            return "UNKNOWN";
        }
        */
        void Write(std::ofstream stream);
        void Read(std::ifstream stream);

        std::shared_ptr<Tag> ReadNamedTag(std::ifstream stream);
        void WriteNamedTag(Tag tag, std::ofstream stream);
        std::shared_ptr<Tag> SetName(std::string name);
        std::string GetName();
};