#include <iostream>
#include "nbt/nbt.h"

int main() {
	auto ctag = std::make_shared<CompoundTag>("Test");
	auto stag = std::make_shared<StringTag>("Name", "PixelBrushArt");
	auto stag2 = std::make_shared<StringTag>("OtherName", "PixelBrushArt2");
	auto btag = std::make_shared<ByteTag>("Byte", 55);

	ctag->Put(stag2->GetName(),stag2);
	ctag->Put( btag->GetName(),btag );
	ctag->Put( stag->GetName(),stag );
	
	ctag->PrintData();
	auto allTags = ctag->GetTags();

	for (const auto& t : allTags) {
		t.second->PrintData();
	}
	return 0;
}
