#include "tag.h"

Tag::Tag(std::string name) {
    this->name = name;
}

std::shared_ptr<Tag> Tag::SetName(std::string name) {
    this->name = name;
    return std::make_shared<Tag>(*this);
}

std::string Tag::GetName() {
    return name;
}

std::string Tag::GetTagName(int8_t type) {
    switch(type) {
        case TAG_END:
            return "TAG_End";
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