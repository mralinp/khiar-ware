#include "AutoBhop.h"

AutoBhop::AutoBhop(MemoryManager* memoryManager): ScriptBot(memoryManager) {
	enable = false;
}

void AutoBhop::refresh() {
	
	if (enable && GetAsyncKeyState(VK_SPACE)){
		localPlayer = getLocalPlayer();
		fFlags = getFFlags();
		if (fFlags & (1 << 0)) {
			forceJump();
		}
	}
}

void AutoBhop::forceJump() {
	mem->write(mem->get_client_base() + signatures::dwForceJump, 6);
}