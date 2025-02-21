#include <iostream>
#include <vector>
#include "nbt/nbt.h"

int main() {
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
	return 0;
}
