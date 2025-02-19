#include <iostream>
#include "nbt/nbt.h"

int main() {
	auto ctag = std::make_shared<CompoundTag>("Test");
	auto stag = std::make_shared<StringTag>("Name", "PixelBrushArt");
	auto stag2 = std::make_shared<StringTag>("OtherName", "PixelBrushArt2");

	ctag->Put(stag2->GetName(),stag2);
	ctag->Put( stag->GetName(),stag );
	
	std::cout << ctag->GetName() << ": ";
	ctag->PrintData();
	std::cout << std::endl;
	auto allTags = ctag->GetTags();

	for (const auto& t : allTags) {
		std::cout << t.second->GetName() << ": ";
		t.second->PrintData();
		std::cout << std::endl;
	}
	return 0;
}
