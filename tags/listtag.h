#pragma once
#include "tag.h"

class ListTag : public Tag {
    private:
        std::vector<std::shared_ptr<Tag>> tags;
        uint8_t tagType;
    public:
        ListTag(std::string name) : Tag(name){};

        void Put(std::shared_ptr<Tag> tag) {
            // This is the first tag we put in
            if (tags.size() == 0) {
                tagType = tag->GetTagId();
            }
            if (tag->GetTagId() == tagType) {
                tags.push_back(tag);
            } else {
                std::cout << "Non-matching Tag in list!" << std::endl;
            }
        }

        std::vector<std::shared_ptr<Tag>> GetTags() {
            return tags;
        }

        size_t GetNumberOfTags() {
            return tags.size();
        }

        std::shared_ptr<Tag> Get(size_t index) {   
            return tags[index];
        }

        void NbtPrintData() override {
            std::cout << "(List) " << GetName() << ": " << tags.size() << std::endl;
            for (const auto& t : tags) {
                std::cout << "\t";
                t->NbtPrintData();
            }
        }
        uint8_t GetTagId() override {
            return (uint8_t)TAG_LIST;
        }
        void Write(std::ostringstream& stream, bool primary = true) override {
            if (primary) {
                WriteHeader(stream);
            }
            stream << (uint8_t)tagType;
            uint32_t writtenSize = Swap32(tags.size());
            stream.write(reinterpret_cast<const char*>(&writtenSize), sizeof(writtenSize));
            for (size_t i = 0; i < tags.size(); ++i) {
                // TODO: Can sometimes use-after-free??
                if (tags[i]) {
                    tags[i]->Write(stream,false);
                }
            }
        }
        void Read(std::istringstream& stream) override {
            uint8_t type;
            stream.get(reinterpret_cast<char&>(type));

            uint32_t readSize;
            stream.read(reinterpret_cast<char*>(&readSize), sizeof(readSize));  // Read raw bytes for integer
            readSize = Swap32(readSize);

            for (uint32_t i = 0; i < readSize; i++) {
                auto newTag = NewTag(type);
                newTag->Read(stream);
                Put(newTag);
            }
        }
};