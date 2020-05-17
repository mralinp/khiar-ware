#include "TriggerBot.h"
#include "Offsets.h"
#include <random>
#include <time.h>

TriggerBot::TriggerBot(){
	enable = false;
}

void TriggerBot::refresh(MemoryManager* mem) {
	if (enable && GetAsyncKeyState(VK_MENU)) {
		dwLocalPlayer = mem->read<DWORD>(mem->get_client_base() + signatures::dwLocalPlayer);
		LocalPlayer_inCross = mem->read<DWORD>(dwLocalPlayer + netvars::m_iCrosshairId);
		LocalPlayer_Team = mem->read<DWORD>(dwLocalPlayer + netvars::m_iTeamNum);
		DWORD Trigger_EntityBase = mem->read<DWORD>(mem->get_client_base() + signatures::dwEntityList + ((LocalPlayer_inCross - 1) * 0x10));
		DWORD Trigger_EntityTeam = mem->read<DWORD>(Trigger_EntityBase + netvars::m_iTeamNum);
		bool Trigger_EntityDormant = mem->read<bool>(Trigger_EntityBase + signatures::m_bDormant);

		//Generating random numbers
		int delay[3] = { rand() % 15, rand() % 15, rand() % 15 };
		for (int i = 0; i < 3; i++) {
			delay[i] = (delay[i] < 0) ? delay[i] + 15 : delay[i];
		}

		//Send an external click to shoot the target
		if ((LocalPlayer_inCross > 0 && LocalPlayer_inCross <= 64) && (Trigger_EntityBase != NULL) && (Trigger_EntityTeam != LocalPlayer_Team) && (!Trigger_EntityDormant)) {
			Sleep(delay[0]);
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			Sleep(delay[1]);
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			Sleep(delay[2]);
		}
	}
}