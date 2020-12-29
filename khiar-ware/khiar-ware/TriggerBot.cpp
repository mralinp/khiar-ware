#include "TriggerBot.h"

TriggerBot::TriggerBot(MemoryManager* memoryManager) : ScriptBot(memoryManager){
	enable = false;
}

void TriggerBot::refresh() {
	if (this->enable && GetAsyncKeyState(VK_MENU)) {
		localPlayer = getLocalPlayer();
		localPlayer_inCross = getIcrosshair(localPlayer);
		localPlayer_team = getTeamNum(localPlayer);
		entity = getEntity(localPlayer_inCross-1);
		entity_team_num = getTeamNum(entity);

		//Send an external click to shoot the target
		// We don't want to shoot a person behind the wall. Use dormant!
		if ((localPlayer_inCross > 0 && localPlayer_inCross < 65) && (entity != NULL) && (entity_team_num != localPlayer_team)) {
			Shoot();
		}
	}
}

void TriggerBot::Shoot() {
	//Generating random numbers
	int delay[3] = { rand() % 15, rand() % 15, rand() % 15 };
	for (int i = 0; i < 3; i++) {
		delay[i] = (delay[i] < 0) ? delay[i] + 15 : delay[i];
	}

	Sleep(delay[0]);
	mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
	Sleep(delay[1]);
	mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
	Sleep(delay[2]);
}
