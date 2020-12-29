#include "ScriptBot.h"

ScriptBot::ScriptBot(MemoryManager* memoryManager) : mem{memoryManager} {

	enable = false;
	glowIdx = 0x00;
	health = 0x00;
	localPlayerTeamNum = 0x00;
	entity_team_num = 0x00;
	entity = 0x00;
	localPlayer = 0x00;
	localPlayer_inCross = 0x00;
	localPlayer_team = 0x00;
	fFlags = 0x00;
	glowObj = 0x00;

}

void ScriptBot::toggle() {
	this->enable = !this->enable;
}

bool ScriptBot::status() {
	return this->enable;
}

bool ScriptBot::isDormant(DWORD player) {
	return mem->read<bool>(player + signitures::m_bDormant);
}

DWORD ScriptBot::getTeamNum(DWORD player) {
	return mem->read<DWORD>(player + netvars::m_iTeamNum);
}



DWORD ScriptBot::getLocalPlayer() {
	return mem->read<DWORD>(mem->get_client_base() + signitures::dwLocalPlayer);
}

DWORD ScriptBot::getIcrosshair(DWORD player) {
	return mem->read<DWORD>(localPlayer + netvars::m_iCrosshairId);
}

DWORD ScriptBot::getEntity(DWORD entityNum){
	return mem->read<DWORD>(mem->get_client_base() + signitures::dwEntityList + entityNum * 0x10);
}


DWORD ScriptBot::getHealth(DWORD player) {
	return  mem->read<DWORD>(player + netvars::m_iHealth);
}

DWORD ScriptBot::getFFlags() {
	return mem->read<BYTE>(localPlayer + netvars::m_fFlags);
}
