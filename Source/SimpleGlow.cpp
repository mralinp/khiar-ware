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

SimpleGlow::SimpleGlow(MemoryManager* memoryManager) : ScriptBot(memoryManager){
	enable = false;
}

void SimpleGlow::refresh() {
	Glow_Struct gst;
	if (this->enable == ON) {
		localPlayer = getLocalPlayer();
		localPlayerTeamNum = getTeamNum(localPlayer);
		glowObj = getGlowObj();
		// Assume that at must we have 64 players, loop over all and 64 is not a such thing that cause extra complexity for our code
		for (DWORD i = 0; i < 33 ; i++) {
			entity = getEntity(i);
			// This can be 0x00 due to MemoryManager::read function itself!
			// we are always counting 0 to 64 so if the server has 24 client at most, the values of 24, 25, ..., 64 will be null or 0x00 
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
	return mem->read<DWORD>(mem->get_client_base() + signatures::dwGlowObjectManager);
}

DWORD SimpleGlow::getGlowIdx(DWORD player) {
	return mem->read<DWORD>(player + netvars::m_iGlowIndex);
}
