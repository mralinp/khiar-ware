#include "ScriptBot.h"

ScriptBot::ScriptBot() {
	enable = false;
	glowIdx = 0x00;
	health = 0x00;
	localPlayerTeamNum = 0x00;
	entity_team_num = 0x00;
	entity = 0x00;
	dwLocalPlayer = 0x00;
	LocalPlayer_inCross = 0x00;
	LocalPlayer_Team = 0x00;
	fFlags = 0x00;
	Trigger_EntityBase = 0x00;
	Trigger_EntityTeam = 0x00;
	Trigger_EntityDormant = 0x00;
	glow_obj = 0x00;
}

void ScriptBot::toggle() {
	this->enable = !this->enable;
}

bool ScriptBot::status() {
	return this->enable;
}