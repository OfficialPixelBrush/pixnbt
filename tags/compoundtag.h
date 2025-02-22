#pragma once
#include "tag.h"

class CompoundTag : public Tag {
    private:
        std::vector<std::shared_ptr<Tag>> tags;
    public:
        CompoundTag(std::string name) : Tag(name){};

        // TODO: Check if a tag of the same name already exists?
        void Put(const std::string& name, std::shared_ptr<Tag> tag) {
            tag->SetName(name);
            tags.push_back(tag);
        }

        void Put(std::shared_ptr<Tag> tag) {
            tags.push_back(tag);
        }

        std::vector<std::shared_ptr<Tag>> GetTags() {
            return tags;
        }
        
        std::shared_ptr<Tag> Get(const std::string& name) {
            auto it = std::find_if(tags.begin(), tags.end(),
                [&](const std::shared_ptr<Tag>& tag) { return tag->GetName() == name; });

            if (it == tags.end()) return nullptr;
            return *it; // Return the shared_ptr<Tag>
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
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            for (const auto& t : tags) {
                t->Write(stream);
            }
            stream << (uint8_t)TAG_END;
        }
        void Read(std::istringstream& stream) override {
            int tags = 0;
            while(true) {
                uint8_t type;
                stream.get(reinterpret_cast<char&>(type));
                if (type == 0) {
                    break;
                }
                uint16_t nameSize;
                stream.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
                nameSize = Swap16(nameSize);
                std::string tagName(nameSize, '\0');
                stream.read(&tagName[0], nameSize);

                auto newTag = NewTag(type, tagName);
                if (!newTag) {
                    break;
                }
                newTag->Read(stream);
                Put(newTag);
                tags++;
            }
        }
};