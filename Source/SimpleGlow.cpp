#include "SimpleGlow.h"

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

SimpleGlow::SimpleGlow() {
	this->enable = false;
}

void SimpleGlow::refresh(MemoryManager* mem) {
	Glow_Struct gst;
	if (this->enable == ON) {
		dwLocalPlayer = mem->read<DWORD>(mem->get_client_base() + signatures::dwLocalPlayer);
		localPlayerTeamNum = mem->read<DWORD>(dwLocalPlayer + netvars::m_iTeamNum);
		glow_obj = mem->read<DWORD>(mem->get_client_base() + signatures::dwGlowObjectManager);
		for (DWORD i = 0; i < 64; i++) {
			entity = mem->read<DWORD>(mem->get_client_base() + signatures::dwEntityList + i * 0x10);
			if (entity != 0x0) {
				glowIdx = mem->read<DWORD>(entity + netvars::m_iGlowIndex);
				entity_team_num = mem->read<DWORD>(entity + netvars::m_iTeamNum);
				if (entity_team_num != localPlayerTeamNum) {
					gst = mem->read<Glow_Struct>(glow_obj + (glowIdx * 0x38));
					health = mem->read<DWORD>(entity + netvars::m_iHealth);
					gst.blue = 0.0f;
					gst.alpha = 1.0f;
					gst.green = health * 0.01;
					gst.red = health * -0.01 + 1;
					gst.occluded = true;
					gst.unoccluded = false;
					mem->write<Glow_Struct>(glow_obj + (glowIdx * 0x38), gst);
				}
			}
		}
	}
}