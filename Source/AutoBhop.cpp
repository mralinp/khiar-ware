#include "AutoBhop.h"
#include "Offsets.h"

AutoBhop::AutoBhop() {
	enable = false;
}

void AutoBhop::refresh(MemoryManager* mem) {
	if (enable && GetAsyncKeyState(VK_SPACE)){
		this->dwLocalPlayer = mem->read<DWORD>(mem->get_client_base() + signatures::dwLocalPlayer);
		fFlags = mem->read<BYTE>(dwLocalPlayer + netvars::m_fFlags);
		if (fFlags & (1 << 0)) {
			mem->write(mem->get_client_base() + signatures::dwForceJump, 6);
		}
	}
}