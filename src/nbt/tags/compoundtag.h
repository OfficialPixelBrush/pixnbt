#pragma once
#include "tag.h"
#include "alltags.h"

class CompoundTag : public Tag {
    private:
        std::vector<Tag*> tags;
    public:
        CompoundTag(std::string name) : Tag(name){};

        // TODO: Check if a tag of the same name already exists?
        void Put(const std::string& name, std::shared_ptr<Tag> tag) {
            tags.push_back(tag->SetName(name));
        }

        void Put(std::shared_ptr<Tag> tag) {
            tags.push_back(tag.get());
        }

        std::vector<Tag*> GetTags() {
            return tags;
        }

        Tag* Get(const std::string& name) {
            auto it = std::find_if(tags.begin(), tags.end(),
                [&](Tag* tag) { return tag->GetName() == name; });

            if (it == tags.end()) return nullptr;
            return *it;
        }

        void PrintData() override {
            std::cout << "(Compound) " << GetName() << ": " << tags.size() << std::endl;
            for (const auto& t : tags) {
                std::cout << "\t";
                t->PrintData();
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
                t->Write(stream);
            }
            stream << (uint8_t)TAG_END;
        }
};