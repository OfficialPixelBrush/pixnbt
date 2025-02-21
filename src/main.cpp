#include "nbt/nbt.h"

int main() {
	/*
	auto root = std::make_shared<CompoundTag>("ROOT");
	auto ctag = std::make_shared<CompoundTag>("Test");
	auto stag = std::make_shared<StringTag>("Name", "PixelBrushArt");
	auto stag2 = std::make_shared<StringTag>("OtherName", "PixelBrushArt2");
	auto btag = std::make_shared<ByteTag>("Age", 55);
	auto stag3 = std::make_shared<ShortTag>("Height", 1263);
	auto itag = std::make_shared<IntTag>("Fucks I give", 6324345);
	auto ltag = std::make_shared<LongTag>("Time", 5234753452421);
	auto ftag = std::make_shared<FloatTag>("x", 0.12152);
	auto dtag = std::make_shared<DoubleTag>("y", 15125.043532432334);

	std::vector<int8_t> bytes = { 0, 1, 2, 6, 123, 5, -56 };
	auto batag = std::make_shared<ByteArrayTag>("Bytezzz", bytes);

	ctag->Put(stag );
	ctag->Put(stag2);
	ctag->Put(btag );
	ctag->Put(stag3);
	ctag->Put(itag );
	ctag->Put(ltag );
	root->Put(ctag );
	ctag->Put(ftag );
	root->Put(dtag );
	root->Put(batag);
	
	root->PrintData();
	//auto allRootTags = root->GetTags();
	auto allTags = ctag->GetTags();
	*/

	// player.nbt
	auto root = std::make_shared<CompoundTag>("");
	auto motionList = std::make_shared<ListTag>("Motion");
	auto motionX = std::make_shared<DoubleTag>("x",0.0);
	auto motionY = std::make_shared<DoubleTag>("y",-0.0784000015258789);
	auto motionZ = std::make_shared<DoubleTag>("z",0.0);
	motionList->Put(motionX);
	motionList->Put(motionY);
	motionList->Put(motionZ);
	root->Put(motionList);

	auto sleepTimer = std::make_shared<ShortTag>("SleepTimer",0);
	root->Put(sleepTimer);

	auto health = std::make_shared<ShortTag>("Health",20);
	root->Put(health);

	auto air = std::make_shared<ShortTag>("Air",300);
	root->Put(air);

	auto onGround = std::make_shared<ByteTag>("OnGround",1);
	root->Put(onGround);

	auto dimension = std::make_shared<IntTag>("Dimension",1);
	root->Put(dimension);

	auto rotationList = std::make_shared<ListTag>("Rotation");
	auto rotationYaw = std::make_shared<FloatTag>("Yaw",53.862545013427734);
	auto rotationPitch = std::make_shared<FloatTag>("Pitch",8.399049758911133);
	rotationList->Put(rotationYaw);
	rotationList->Put(rotationPitch);
	root->Put(rotationList);

	auto fallDistance = std::make_shared<FloatTag>("FallDistance", 0.0);
	root->Put(fallDistance);

	auto sleeping = std::make_shared<ByteTag>("Sleeping", 0);
	root->Put(sleeping);

	auto posList = std::make_shared<ListTag>("Pos");
	auto posX = std::make_shared<DoubleTag>("x",20.494944679930093);
	auto posY = std::make_shared<DoubleTag>("y",71.0);
	auto posZ = std::make_shared<DoubleTag>("z",-9.79636710766522);
	posList->Put(posX);
	posList->Put(posY);
	posList->Put(posZ);
	root->Put(posList);

	auto deathTime = std::make_shared<ShortTag>("DeathTime",0);
	root->Put(deathTime);

	auto fire = std::make_shared<ShortTag>("Fire",-20);
	root->Put(fire);

	auto hurtTime = std::make_shared<ShortTag>("HurtTime",0);
	root->Put(hurtTime);

	auto attackTime = std::make_shared<ShortTag>("AttackTime",0);
	root->Put(attackTime);

	auto inventory = std::make_shared<ListTag>("Inventory");

	auto slot0 = std::make_shared<CompoundTag>("0");
	auto slot0Slot = std::make_shared<ByteTag>("Slot", 0);
	auto slot0Id = std::make_shared<ShortTag>("id",17);
	auto slot0Count = std::make_shared<ByteTag>("Count", 64);
	auto slot0Damage = std::make_shared<ShortTag>("Damage", 0);
	slot0->Put(slot0Slot);
	slot0->Put(slot0Id);
	slot0->Put(slot0Count);
	slot0->Put(slot0Damage);
	inventory->Put(slot0);

	auto slot1 = std::make_shared<CompoundTag>("1");
	auto slot1Slot = std::make_shared<ByteTag>("Slot", 1);
	auto slot1Id = std::make_shared<ShortTag>("id",7);
	auto slot1Count = std::make_shared<ByteTag>("Count", 64);
	auto slot1Damage = std::make_shared<ShortTag>("Damage", 0);
	slot1->Put(slot1Slot);
	slot1->Put(slot1Id);
	slot1->Put(slot1Count);
	slot1->Put(slot1Damage);
	inventory->Put(slot1);
	root->Put(inventory);

	root->PrintData();

    std::ofstream file ("file.nbt");
	root->Write(file,true);
	file.close();

	return 0;
}
