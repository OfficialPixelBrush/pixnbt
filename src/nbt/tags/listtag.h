#pragma once
#include "tag.h"
#include "alltags.h"

class ListTag : public Tag {
    private:
        std::vector<Tag*> tags;
        uint8_t tagType;
    public:
        ListTag(std::string name) : Tag(name){};

        void Put(std::shared_ptr<Tag> tag) {
            // This is the first tag we put in
            if (tags.size() == 0) {
                tagType = tag->GetTagId();
            }
            if (tag->GetTagId() == tagType) {
                tags.push_back(tag.get());
            } else {
                std::cout << "Non-matching Tag in list!" << std::endl;
            }
        }

        std::vector<Tag*> GetTags() {
            return tags;
        }

        Tag* Get(size_t index) {   
            return tags[index];
        }

        void PrintData() override {
            std::cout << "(List) " << GetName() << ": " << tags.size() << std::endl;
            for (const auto& t : tags) {
                std::cout << "\t";
                t->PrintData();
            }
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_LIST;
        }
        void Write(std::ofstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            for (size_t i = 0; i < tags.size(); ++i) {
                if (i == 0) {
                    stream << (uint8_t)tagType;
                }
                tags[i]->Write(stream,false);
            }
            stream << (uint8_t)TAG_END;
        }
};