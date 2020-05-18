#include "Radar.h"

Radar::Radar() {
	enable = false;
}

void Radar::refresh(MemoryManager* mem) {
	if (enable) {

		for (int i = 0; i < 64; i++) {
			DWORD entity = mem->read<DWORD>(mem->get_client_base() + signatures::dwEntityList + i * 0x10);
			if (entity != NULL) {
				mem->write<bool>(entity + netvars::m_bSpotted, true);
			}
		}
	}
}