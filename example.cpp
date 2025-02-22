#include "nbt.h"

int main() {
	// player.nbt
	auto root = std::make_shared<CompoundTag>("");

	auto motionList = std::make_shared<ListTag>("Motion");
	root->Put(motionList);
	motionList->Put(std::make_shared<DoubleTag>("x",0.0));
	motionList->Put(std::make_shared<DoubleTag>("y",-0.0784000015258789));
	motionList->Put(std::make_shared<DoubleTag>("z",0.0));

	root->Put(std::make_shared<ShortTag>("SleepTimer", 0));
	root->Put(std::make_shared<ShortTag>("Health",20));
	root->Put(std::make_shared<ShortTag>("Air",300));
	root->Put(std::make_shared<ByteTag>("OnGround",1));
	root->Put(std::make_shared<IntTag>("Dimension",1));

	auto rotationList = std::make_shared<ListTag>("Rotation");
	rotationList->Put(std::make_shared<FloatTag>("Yaw",53.862545013427734));
	rotationList->Put(std::make_shared<FloatTag>("Pitch",8.399049758911133));
	root->Put(rotationList);
	
	root->Put(std::make_shared<FloatTag>("FallDistance", 0.0));
	root->Put(std::make_shared<ByteTag>("Sleeping", 0));

	auto posList = std::make_shared<ListTag>("Pos");
	posList->Put(std::make_shared<DoubleTag>("x",20.494944679930093));
	posList->Put(std::make_shared<DoubleTag>("y",71.0));
	posList->Put(std::make_shared<DoubleTag>("z",-9.79636710766522));
	root->Put(posList);

	root->Put(std::make_shared<ShortTag>("DeathTime",0));
	root->Put(std::make_shared<ShortTag>("Fire",-20));
	root->Put(std::make_shared<ShortTag>("HurtTime",0));
	root->Put(std::make_shared<ShortTag>("AttackTime",0));

	auto inventory = std::make_shared<ListTag>("Inventory");
	root->Put(inventory);

	inventory->Put(NbtItem(0,17,64,0));
	inventory->Put(NbtItem(1, 7,64,0));

	// Yeet to file
	WriteToFile("player.dat",root);
	std::cout << "--- Written ---" << std::endl;
	root->PrintData();

	auto readRoot = ReadFromFile("player.dat");
	std::cout << "--- Read ---" << std::endl;
	readRoot->PrintData();

	return 0;
}
