#include "SimpleGlow.h"
#include <iostream>

struct SimpleGlow::Glow_Struct {
	int32_t m_nNextFreeSlot; //0x0000
	uint32_t pEntity; //0x0004
	float R; //0x0008
	float G; //0x000C
	float B; //0x0010
	float A; //0x0014
	char pad_0018[4]; //0x0018
	float flUnk; //0x001C
	float flBloom; //0x0020
	float localplayeriszeropoint3; //0x0024
	bool m_bRenderWhenOccluded; //0x0028
	bool m_bRenderWhenUnoccluded; //0x0029
	bool m_bFullBloomRender; //0x002A
	char pad_002B[1]; //0x002B
	int32_t m_nFullBloomStencilTestValue; //0x002C
	int32_t iUnk; //0x0030
	int32_t m_nSplitScreenSlot; //0x0034
}; //Size: 0x0038


void SimpleGlow::refresh() {
	Glow_Struct gst;
	if (this->enable) {
		localPlayer = getLocalPlayer();
		localPlayerTeamNum = getTeamNum(localPlayer);
		glowObj = getGlowObjManager();
		for (DWORD i = 1; i < 64 ; i++) {
			entity = getEntity(i);
			if (entity != NULL) {
				glowIdx = getGlowIdx(entity);
				entity_team_num = getTeamNum(entity);
				if (entity_team_num != localPlayerTeamNum && isDormant(entity) == false) {
					gst = mem->read<Glow_Struct>(glowObj + (glowIdx * 0x38));
					health = getHealth(entity);
					gst.B = 0.0f;
					gst.A = 1.0f;
					gst.G = health * 0.01;
					gst.R = health * -0.01 + 1;
					gst.m_bRenderWhenOccluded = true;
					gst.m_bRenderWhenUnoccluded = false;
					gst.m_bFullBloomRender = false;
					mem->write<Glow_Struct>(glowObj + (glowIdx * 0x38), gst);
				}
			}
		}
	}
}

DWORD SimpleGlow::getGlowObjManager(){
	return mem->read<DWORD>(mem->getClientBaseAddr() + signitures::dwGlowObjectManager);
}

DWORD SimpleGlow::getGlowIdx(DWORD player) {
	return mem->read<DWORD>(player + netvars::m_iGlowIndex);
}
