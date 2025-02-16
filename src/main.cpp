#include <iostream>
#include "nbt/nbt.h"

int main() {
	auto ctag = new CompoundTag("Test");
	auto stag = new StringTag("Name", "PixelBrushArt");
	ctag->PutString(stag->GetName(),stag);
	std::cout << ctag->GetName() << std::endl;
	delete ctag;
	return 0;
}
