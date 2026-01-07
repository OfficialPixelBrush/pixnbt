#define NBT_IMPLEMENTATION
#include "nbt.h"

int32_t main() {
	auto root = std::make_shared<CompoundNbtTag>("");

	auto test = std::make_shared<StringNbtTag>("LevelName", "world");

	root->Put(std::make_shared<LongNbtTag>("RandomSeed",8703966663084738725));
	root->Put(std::make_shared<IntNbtTag>("SpawnY", 64));
	root->Put(std::make_shared<StringNbtTag>("LevelName", "world"));
	root->Put(std::make_shared<ByteNbtTag>("thunderTime", 26271));
	std::vector<uint8_t> data = {0,1,2,3,4,5,6,8,7};
	root->Put(std::make_shared<ByteArrayNbtTag>("binData",data));


	// Yeet to file
	// Apparently the file itself is terminated with another TAG_END(?)
	std::ofstream writeFile("file.dat", std::ios::binary);
	NbtWrite(writeFile,root,NBT_GZIP);
	writeFile.close();
	if (root) {
		std::cout << "--- Written ---" << "\n";
		std::cout << *root << "\n";
	}

	std::ifstream readFile("file.dat", std::ios::binary);
	auto readOwnRoot = NbtRead(readFile,NBT_GZIP);
	readFile.close();
	if (readOwnRoot) {
		std::cout << "--- Read ---" << "\n";
		std::cout << *readOwnRoot << "\n";
	}

	return 0;
}
