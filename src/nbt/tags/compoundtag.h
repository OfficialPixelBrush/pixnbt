#pragma once
#include "tag.h"
#include "alltags.h"

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
        void Read(std::istringstream& stream) {
            while(true) {
                uint8_t type;
                stream.get(reinterpret_cast<char&>(type));
                if (type == 0) {
                    break;
                }
                uint16_t nameLength;
                stream.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));  // Read raw bytes for integer
                nameLength = Swap16(nameLength);
                std::string tagName(nameLength, '\0');
                stream.read(&tagName[0], nameLength);

                std::cout << tagName << std::endl;

                auto newTag = NewTag(type, tagName);
                //newTag->Read(stream);
                Put(newTag);
            }
        }
};