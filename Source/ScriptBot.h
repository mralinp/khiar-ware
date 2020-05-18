#pragma once

#include "MemoryManager.h"
#include "Offsets.h"

class ScriptBot{
protected:
	bool enable;
	DWORD glowIdx;
	DWORD health;
	DWORD localPlayerTeamNum;
	DWORD entity_team_num;
	DWORD entity;
	DWORD dwLocalPlayer;
	DWORD LocalPlayer_inCross;
	DWORD LocalPlayer_Team;
	BYTE fFlags;
	DWORD Trigger_EntityBase;
	DWORD Trigger_EntityTeam;
	bool Trigger_EntityDormant;
	DWORD glow_obj;
public:
	ScriptBot();
	virtual void refresh(MemoryManager* mem) = 0;
	bool status();
	void toggle();
};