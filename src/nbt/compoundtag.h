#pragma once
#include "tag.h"
#include "alltags.h"
#include <unordered_map>

class CompoundTag : public Tag {
    private:
        std::unordered_map<std::string, std::shared_ptr<Tag>> tags;
    public:
        std::string data;
        CompoundTag(std::string name) : Tag(name){};

        void Put(const std::string& name, std::shared_ptr<Tag> tag) {
            tags[name] = tag->SetName(name);
        }

        std::unordered_map<std::string, std::shared_ptr<Tag>> GetTags() {
            return tags;
        }

        std::shared_ptr<StringTag> GetString(const std::string& name) {
            auto it = tags.find(name);
            if (it == tags.end()) return nullptr;
        
            // Cast the raw pointer from the unique_ptr
            if (auto* ptr = dynamic_cast<StringTag*>(it->second.get())) {
                return std::make_shared<StringTag>(*ptr);  // Create a new unique_ptr with a copy
            }
        
            return nullptr;
        }        

        std::shared_ptr<CompoundTag> GetCompound(const std::string& name) {
            auto it = tags.find(name);
            if (it == tags.end()) return nullptr;
        
            // Cast the raw pointer from the unique_ptr
            if (auto* ptr = dynamic_cast<CompoundTag*>(it->second.get())) {
                return std::make_shared<CompoundTag>(*ptr);  // Create a new unique_ptr with a copy
            }
        
            return nullptr;
        }
        void PrintData() override {
            std::cout << tags.size();
        }
};