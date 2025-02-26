#include "nbt.h"

int main() {
	auto root = std::make_shared<CompoundTag>("");

	auto test = std::make_shared<StringTag>("LevelName", "world");

	root->Put(std::make_shared<LongTag>("RandomSeed",8703966663084738725));
	root->Put(std::make_shared<IntTag>("SpawnY", 64));
	root->Put(std::make_shared<StringTag>("LevelName", "world"));
	root->Put(std::make_shared<ByteTag>("thunderTime", 26271));
	std::vector<int8_t> data = {0,1,2,3,4,5,6,8,7};
	root->Put(std::make_shared<ByteArrayTag>("binData",data));


	// Yeet to file
	// Apparently the file itself is terminated with another TAG_END(?)
	NbtWriteToFile("file.dat",root);
	if (root) {
		std::cout << "--- Written ---" << std::endl;
		root->NbtPrintData();
	}

	auto readOwnRoot = NbtReadFromFile("file.dat");
	if (readOwnRoot) {
		std::cout << "--- Read ---" << std::endl;
		readOwnRoot->NbtPrintData();
	}

	return 0;
}
