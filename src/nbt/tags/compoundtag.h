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

        void Put(const std::string& name, std::shared_ptr<Tag> tag) {
            tags[name] = tag->SetName(name);
        }

        void Put(std::shared_ptr<Tag> tag) {
            tags[tag->GetName()] = tag.get();
        }

        std::unordered_map<std::string, Tag*> GetTags() {
            return tags;
        }

        std::shared_ptr<StringTag> GetString(const std::string& name) {
            auto it = tags.find(name);
            if (it == tags.end()) return nullptr;
        
            // Cast the raw pointer from the unique_ptr
            if (auto* ptr = dynamic_cast<StringTag*>(it->second)) {
                return std::make_shared<StringTag>(*ptr);  // Create a new unique_ptr with a copy
            }
        
            return nullptr;
        }        

        std::shared_ptr<CompoundTag> GetCompound(const std::string& name) {
            auto it = tags.find(name);
            if (it == tags.end()) return nullptr;
        
            // Cast the raw pointer from the unique_ptr
            if (auto* ptr = dynamic_cast<CompoundTag*>(it->second)) {
                return std::make_shared<CompoundTag>(*ptr);  // Create a new unique_ptr with a copy
            }
        
            return nullptr;
        }
        void PrintData() override {
            std::cout << "(Compound) " << GetName() << ": " << tags.size() << std::endl;
            for (const auto& t : tags) {
                std::cout << "\t";
                t.second->PrintData();
            }
        }
};