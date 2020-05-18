#include <random>
#include <time.h>
#include <atlstr.h>
#include "Logger.h"
#include "SimpleGlow.h"
#include "MemoryManager.h"
#include "TriggerBot.h"
#include "AutoBhop.h"
#include "Radar.h"

const int max_length = 50;

std::string get_random_name() {
	std::string name = "";
	int name_length = rand() % max_length;
	for (int i = 0; i < name_length; i++) {
		int tmp = (char)rand() % 26;
		tmp = (tmp < 0) ? tmp + 26 : tmp;
		name += (char)((rand() % 2 == 0) ? 'a' + tmp : 'A' + tmp);
	}
	return name;
}

void set_random_name() {
	TCHAR c_name[max_length];
	std::string sc_name = get_random_name();
	_tcscpy_s(c_name, CA2T(sc_name.c_str()));
	SetConsoleTitle(c_name);
}

int get_key() {
	for (int vkey = 8; vkey < 255; vkey++) {
		if (GetAsyncKeyState(vkey)) {
			return vkey;
		}
	}
	return -1;
}

int main() {
	
	srand(time(NULL));
	set_random_name();
	
	Logger* logger = new Logger();
	MemoryManager* mem = new MemoryManager(logger);

	mem->read<DWORD>(mem->get_client_base());
	SimpleGlow* glow = new SimpleGlow();
	TriggerBot* trigger_bot = new TriggerBot();
	AutoBhop* auto_bhop = new AutoBhop();
	Radar* radar = new Radar();

	logger->log(WARN, "Ready!");
	logger->log(INFO, "These are toggle keys:");
	logger->log(INFO, "\tWallHack: INSERT");
	logger->log(INFO, "\tTriggerBot: HOME");
	logger->log(INFO, "\tAutoBhop: PAGEUp");
	logger->log(INFO, "\tRadarHack: PAGEDOWN");
	logger->log(INFO, "\tExit: DELETE");

	bool is_running = true;
	int refresh_interval;
	while (is_running) {
		refresh_interval = rand()%10;
		refresh_interval = (refresh_interval < 0) ? refresh_interval + 10: refresh_interval;
		Sleep(refresh_interval);
		glow->refresh(mem);
		//Jump while Space key is pressed
		auto_bhop->refresh(mem);
		//It shoots when ALT key is DOWN
		trigger_bot->refresh(mem);
		//Refresh RadarHack
		radar->refresh(mem);
		switch (get_key()) {
			// Exit when DEL pressed
			case VK_DELETE: {
				logger->log(WARN, "DELETE pressed");
				is_running = false;
				Sleep(150);
				break;
			}
			// Toggle wall-hack with Insert key
			case VK_INSERT: {
				glow->toggle();
				logger->log(WARN, "WallHack status: " + std::to_string(glow->status()));
				Sleep(150);
				break;
			}
			//Toggle TriggerBot with Home key
			case VK_HOME: {
				trigger_bot->toggle();
				logger->log(WARN, "Trigger status: " + std::to_string(trigger_bot->status()));
				Sleep(150);
				break;
			}
			//Toggle AutoBhop with PageUp key
			case VK_PRIOR: {
				auto_bhop->toggle();
				logger->log(WARN, "Bhop Status: " + std::to_string(auto_bhop->status()));
				Sleep(150);
				break;
			}
			//Toggle Radar with PageDown key
			case VK_NEXT: {
				radar->toggle();
				logger->log(WARN, "Radar Status: " + std::to_string(radar->status()));
				Sleep(150);
				break;
			}
			default: {
				break;
			}
		}
	}

	logger->log(INFO, "Go learn how to play idiot!");

	return 0;
}

