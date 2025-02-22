#include "tag.h"
#include "alltags.h"

std::string GetTagName(int8_t type) {
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

std::shared_ptr<Tag> NewTag(uint8_t type, std::string name) {
    switch(type) {
        case TAG_BYTE:
            return std::make_shared<ByteTag>(name);
        case TAG_SHORT:
            return std::make_shared<ShortTag>(name);
        case TAG_INT:
            return std::make_shared<IntTag>(name);
        case TAG_LONG:
            return std::make_shared<LongTag>(name);
        case TAG_FLOAT:
            return std::make_shared<FloatTag>(name);
        case TAG_DOUBLE:
            return std::make_shared<DoubleTag>(name);
        case TAG_BYTE_ARRAY:
            return std::make_shared<ByteArrayTag>(name);
        case TAG_STRING:
            return std::make_shared<StringTag>(name);
        case TAG_LIST:
            return std::make_shared<ListTag>(name);
        case TAG_COMPOUND:
            return std::make_shared<CompoundTag>(name);
        default:
            return nullptr;
    }
}