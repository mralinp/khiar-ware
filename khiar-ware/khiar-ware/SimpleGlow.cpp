#include "SimpleGlow.h"
#include <iostream>

struct SimpleGlow::Glow_Struct {
	BYTE base[4];
	float red;
	float green;
	float blue;
	float alpha;
	BYTE buff0[16];
	bool occluded;
	bool unoccluded;
	bool full_bloom;
	BYTE buff1[5];
	int glow_style;
};


void SimpleGlow::refresh() {
	Glow_Struct gst;
	if (this->enable) {
		localPlayer = getLocalPlayer();
		localPlayerTeamNum = getTeamNum(localPlayer);
		glowObj = getGlowObj();
		for (DWORD i = 1; i < 32 ; i++) {
			entity = getEntity(i);
			// This can be 0x00 due to MemoryManager::read function itself!
			if (entity != NULL) {
				glowIdx = getGlowIdx(entity);
				entity_team_num = getTeamNum(entity);
				if (entity_team_num != localPlayerTeamNum && isDormant(entity) == false) {
					gst = mem->read<Glow_Struct>(glowObj + (glowIdx * 0x38));
					health = getHealth(entity);
					gst.blue = 0.0f;
					gst.alpha = 1.0f;
					gst.green = health * 0.01;
					gst.red = health * -0.01 + 1;
					gst.occluded = true;
					gst.unoccluded = false;
					mem->write<Glow_Struct>(glowObj + (glowIdx * 0x38), gst);
				}
			}
		}
	}
}

DWORD SimpleGlow::getGlowObj(){
	return mem->read<DWORD>(mem->getClientBaseAddr() + signitures::dwGlowObjectManager);
}

DWORD SimpleGlow::getGlowIdx(DWORD player) {
	return mem->read<DWORD>(player + netvars::m_iGlowIndex);
}
