#pragma once
#include "tag.h"

class StringTag : public Tag {
    private:
        std::string data = "";
    public:
        StringTag(std::string name, std::string data = "") : Tag(name){this->data = data; }
};