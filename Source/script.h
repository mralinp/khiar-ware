#pragma once
#ifndef OFFSET_H
#define OFFSET_H
#endif

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H
#endif

class Script {

	DWORD i;
	DWORD glowIdx;
	DWORD health;
	DWORD localPlayerTeamNum;
	DWORD entity_team_num;
	DWORD entity;
	DWORD dwLocalPlayer = 0;
	DWORD LocalPlayer_inCross;
	DWORD LocalPlayer_Team;
	BYTE fFlags = 0;	
	DWORD Trigger_EntityBase;
	DWORD Trigger_EntityTeam;
	bool Trigger_EntityDormant;
	DWORD glow_obj;

	struct glow_struct {
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

	glow_struct gst;

public:
	
	Script(MemoryManager* mem) {
		this->dwLocalPlayer = mem->read<DWORD>(mem->get_client_base() + offset::signature::dwLocalPlayer);
		this->LocalPlayer_inCross = mem->read<DWORD>(dwLocalPlayer + offset::netvar::m_iCrosshairId);
		this->LocalPlayer_Team = mem->read<DWORD>(dwLocalPlayer + offset::netvar::m_iTeamNum);
	}

	void Bhop(MemoryManager* mem) {
		this->dwLocalPlayer = mem->read<DWORD>(mem->get_client_base() + offset::signature::dwLocalPlayer);
		fFlags = mem->read<BYTE>(dwLocalPlayer + offset::netvar::m_fFlags);
		if (fFlags & (1 << 0)) {
			mem->write(mem->get_client_base() + offset::signature::dwForceJump, 6);
		}
	}

	void triggerBot(MemoryManager* mem) {
		dwLocalPlayer = mem->read<DWORD>(mem->get_client_base() + offset::signature::dwLocalPlayer);
		LocalPlayer_inCross = mem->read<DWORD>(dwLocalPlayer + offset::netvar::m_iCrosshairId);
		LocalPlayer_Team = mem->read<DWORD>(dwLocalPlayer + offset::netvar::m_iTeamNum);
		DWORD Trigger_EntityBase = mem->read<DWORD>(mem->get_client_base() + offset::signature::dwEntityList + ((LocalPlayer_inCross - 1) * 0x10));
		DWORD Trigger_EntityTeam = mem->read<DWORD>(Trigger_EntityBase + offset::netvar::m_iTeamNum);
		bool Trigger_EntityDormant = mem->read<bool>(Trigger_EntityBase + offset::signature::m_bDormant);
		if ((LocalPlayer_inCross > 0 && LocalPlayer_inCross <= 64) && (Trigger_EntityBase != NULL) && (Trigger_EntityTeam != LocalPlayer_Team) && (!Trigger_EntityDormant)){
			Sleep(10);
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			Sleep(10);
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			Sleep(10);
		}
	}

	void wall_hack(MemoryManager* mem) {
		dwLocalPlayer = mem->read<DWORD>(mem->get_client_base() + offset::signature::dwLocalPlayer);
		localPlayerTeamNum = mem->read<DWORD>(dwLocalPlayer + offset::netvar::m_iTeamNum);
		glow_obj = mem->read<DWORD>(mem->get_client_base() + offset::signature::dwGlowObjectManager);
		for (i = 0; i < 64; i++) {
			entity = mem->read<DWORD>(mem->get_client_base() + offset::signature::dwEntityList + i * 0x10);
			if (entity != 0x0) {
				glowIdx = mem->read<DWORD>(entity + offset::netvar::m_iGlowIndex);
				entity_team_num = mem->read<DWORD>(entity + offset::netvar::m_iTeamNum);
				if (entity_team_num != localPlayerTeamNum) {
					gst = mem->read<glow_struct>(glow_obj + (glowIdx * 0x38));
					health = mem->read<DWORD>(entity + offset::netvar::m_iHealth);
					gst.blue = 0.0f;
					gst.alpha = 1.0f;
					gst.green = health* 0.01;
					gst.red = health*-0.01 + 1;
					gst.occluded = true;
					gst.unoccluded = false;
					mem->write<glow_struct>(glow_obj + (glowIdx * 0x38), gst);
				}
				
			}
		}
	}

};
