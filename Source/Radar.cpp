#include "Radar.h"
#include <iostream>
Radar::Radar(MemoryManager* memoryManager):ScriptBot(memoryManager) {
	this->enable = false;
}

void Radar::refresh() {
	if (this->enable) {
		for (int i = 0; i < 65; i++) {
			DWORD entity = getEntity(i);
			if (entity != NULL && isDormant(entity) == false) {
				setSpotted(entity);
			}
		}
	}
}
void Radar::setSpotted(DWORD player) {
	mem->write<bool>(player + netvars::m_bSpotted, true);
}