#include <iostream>
#include "nbt/nbt.h"

int main() {
	auto ctag = new CompoundTag("Test");
	auto stag = new StringTag("Name", "PixelBrushArt");
	auto stag2 = new StringTag("OtherName", "PixelBrushArt2");

	ctag->PutString(stag2->GetName(),stag2);
	ctag->PutString(stag->GetName(),stag);
	
	std::cout << ctag->GetName() << std::endl;
	auto allTags = ctag->GetTags();

	for (auto t : allTags) {
		std::cout << t.second->GetName() << std::endl;
	}
	delete ctag;
	delete stag;
	delete stag2;
	return 0;
}
