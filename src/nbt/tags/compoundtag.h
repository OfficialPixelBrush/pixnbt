#pragma once
#include "tag.h"
#include "alltags.h"

class CompoundTag : public Tag {
    private:
        std::unordered_map<std::string, Tag*> tags;
    public:
        CompoundTag(std::string name) : Tag(name){};

        // TODO: Check if a tag of the same name already exists?
        void Put(const std::string& name, std::shared_ptr<Tag> tag) {
            tags[name] = tag->SetName(name);
        }

        void Put(std::shared_ptr<Tag> tag) {
            tags[tag->GetName()] = tag.get();
        }

        std::unordered_map<std::string, Tag*> GetTags() {
            return tags;
        }

        Tag* Get(const std::string& name) {
            auto it = tags.find(name);
            if (it == tags.end()) return nullptr;        
            return it->second;
        }

        void PrintData() override {
            std::cout << "(Compound) " << GetName() << ": " << tags.size() << std::endl;
            for (const auto& t : tags) {
                std::cout << "\t";
                t.second->PrintData();
            }
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_COMPOUND;
        }
        void Write(std::ofstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            for (const auto& t : tags) {
                t.second->Write(stream);
            }
            stream << (uint8_t)TAG_END;
        }
};