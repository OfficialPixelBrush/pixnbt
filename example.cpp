#include "nbt.h"

int main() {
	// level.dat
	auto root = std::make_shared<CompoundTag>("");
	auto data = std::make_shared<CompoundTag>("Data");
	root->Put(data);

	data->Put(std::make_shared<LongTag>("RandomSeed",8703966663084738725));
	data->Put(std::make_shared<IntTag>("SpawnY", 64));
	data->Put(std::make_shared<IntTag>("rainTime", 87264));
	data->Put(std::make_shared<IntTag>("thunderTime", 26271));
	data->Put(std::make_shared<IntTag>("SpawnZ", -51));
	data->Put(std::make_shared<IntTag>("SpawnX", 63));
	data->Put(std::make_shared<ByteTag>("raining", 0));
	data->Put(std::make_shared<LongTag>("Time", 56719));
	data->Put(std::make_shared<ByteTag>("thundering", 0));
	data->Put(std::make_shared<IntTag>("version", 19132));
	data->Put(std::make_shared<LongTag>("LastPlayed", 1740410572431));
	data->Put(std::make_shared<StringTag>("LevelName", "world"));
	data->Put(std::make_shared<LongTag>("SizeOnDisk", 3956736));

	// Yeet to file
	// Apparently the file itself is terminated with another TAG_END(?)
	NbtWriteToFile("level.dat",root);
	if (root) {
		std::cout << "--- Written ---" << std::endl;
		root->NbtPrintData();
	}

	auto readOwnRoot = NbtReadFromFile("level.dat");
	if (readOwnRoot) {
		std::cout << "--- Read ---" << std::endl;
		readOwnRoot->NbtPrintData();
	}

	return 0;
}
