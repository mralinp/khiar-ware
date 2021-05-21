#include "AutoBhop.h"

void AutoBhop::refresh() {
	
	if (enable && GetAsyncKeyState(VK_SPACE)){
		localPlayer = getLocalPlayer();
		fFlags = getFFlags();
		if (fFlags & 1) {
			forceJump();
		}
	}
}

void AutoBhop::forceJump() {
	mem->write(mem->getClientBaseAddr() + signitures::dwForceJump, 6);
}
