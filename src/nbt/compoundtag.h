#pragma once
#include "tag.h"
#include "alltags.h"
#include <unordered_map>

class CompoundTag : public Tag {
    private:
        std::unordered_map<std::string, Tag*> tags;
    public:
        std::string data;
        CompoundTag(std::string name) : Tag(name){};

        void PutString(std::string name, StringTag* value) {
            tags[name] = value->SetName(name);
        }

        void PutCompound(std::string name, CompoundTag* value) {
            tags[name] = value->SetName(name);
        }

        std::unordered_map<std::string, Tag*> GetTags() {
            return tags;
        }

        StringTag* GetString(const std::string& name) {
            auto it = tags.find(name);
            if (it != tags.end()) {
                return static_cast<StringTag*>(it->second);
            }
            return new StringTag(name);
        }

        CompoundTag* GetCompound(const std::string& name) {
            auto it = tags.find(name);
            if (it != tags.end()) {
                return static_cast<CompoundTag*>(it->second);
            }
            return new CompoundTag(name);
        }
};