#include "Radar.h"
#include <iostream>

void Radar::refresh() {
	if (this->enable) {
		for (int i = 0; i < 32; i++) {
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
