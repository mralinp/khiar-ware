#include <random>
#include <time.h>
#include <atlstr.h>
#include "Logger.h"
#include "SimpleGlow.h"
#include "MemoryManager.h"
#include "TriggerBot.h"
#include "AutoBhop.h"
#include "Radar.h"

const int max_length = 10;

std::string getRandomName() {
	std::string name = "";
	int name_length = rand() % max_length;
	for (int i = 0; i < name_length; i++) {
		int tmp = (char)rand() % 26;
		tmp = (tmp < 0) ? tmp + 26 : tmp;
		name += (char)((rand() % 2 == 0) ? 'a' + tmp : 'A' + tmp);
	}
	return name;
}

void setRandomName() {
	TCHAR c_name[max_length];
	std::string sc_name = getRandomName();
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
	setRandomName();

	std::cout << "	 _   ___     _            _    _\n";
	std::cout << "	| | / / |   (_)          | |  | |               \n";
	std::cout << "	| |/ /| |__  _  __ _ _ __| |  | | __ _ _ __ ___ \n";
	std::cout << "	|    \\| '_ \\| |/ _` | '__| |/\\| |/ _` | '__/ _ \\\n";
	std::cout << "	| |\\  \\ | | | | (_| | |  \\  /\\  / (_| | | |  __/\n";
	std::cout << "	\\_| \\_/_| |_|_|\\__,_|_|   \\/  \\/ \\__,_|_|  \\___|\n\n";

	std::cout << "For public servers and match macking only. (not working in dangerzone)" << std::endl;
	std::cout << "KEY BINDS:\n\n\tWALL HACK: INSERT\n\tTRIGGER BOT: HOME\n\tBHOP: PAGEUP\n" << std::endl;

	SimpleGlow glow;
	TriggerBot trigger;
	AutoBhop bhop;
	Radar radar;
	radar.toggle();
	std::cout << "Radar is On." << std::endl;	                                         
	
	while (true) {
		glow.refresh();
		radar.refresh();
		bhop.refresh();
		trigger.refresh();
		int key = get_key();
		if (key == VK_INSERT)
		{
			glow.toggle();
			std::cout << "glow is: " << glow.status() << std::endl;
			Sleep(200);
		}
		else if (key == VK_HOME)
		{
			trigger.toggle();
			std::cout << "trigger is: " << trigger.status() << std::endl;
			Sleep(200);
		}
		else if (key == VK_PRIOR)
		{
			bhop.toggle();
			std::cout << "bhop is: " << bhop.status() << std::endl;
			Sleep(200);
		}
		else if (key == VK_DELETE)
		{
			std::cout << "Go learn how to play idiot!" << std::endl;
			Sleep(3000);
			break;
		}
		Sleep(1);
	}
	return 0;
	
}

