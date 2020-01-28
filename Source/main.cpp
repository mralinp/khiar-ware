#include <iostream>
#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include <tlhelp32.h>
#include <psapi.h>
#include "MemoryManager.h"
#include "Offset.h"
#include "script.h"

using namespace std;

const char logo[][51] = {
	"  _  ___     _          __        __    ___",
	" | |/ / |__ (_) __ _ _ _\\ \\      / /_ _|  _ \\ ___ ",
	" | ' /| '_ \\| |/ _` | '__\\ \\ /\\ / / _` | |_) / _ \\",
	" | . \\| | | | | (_| | |   \\ V  V / (_| |  _ <  __/",
	" |_|\\_\\_| |_|_|\\__,_|_|    \\_/\\_/ \\__,_|_| \\_\\___|"
};

int main() {
	const TCHAR console_name[20] = TEXT("Khiar-Ware");
	SetConsoleTitle(console_name);

	for (int i = 0; i < 5; i++) {
		printf_s("%s\n", logo[i]);
	}

	MemoryManager* mem = new MemoryManager();
	Script script(mem);
	int key;
	bool is_running = true;
	bool wall_en = false;
	bool bhop_en = false;
	bool trigger_en = false;
	
	do {
		Sleep(20);
		for (key = 8; key < 255; key++) {
			if (is_running == false) {
				break;
			}
			if (GetAsyncKeyState(key) & 0x8000) {
				switch (key) {
					case VK_INSERT: {
						wall_en = !wall_en;
						Sleep(300);
						printf_s("Wallhack: %d \n", wall_en); // Wall hack Trigger INSERT
						break;
					}
					case VK_HOME: {
						bhop_en = !bhop_en;
						Sleep(300);
						printf_s("Bhop: %d \n", bhop_en); // Bhop Trigger Home
						break;
					}
					case VK_DELETE: {
						is_running = false; // quit the game with F1
						printf_s("Goodbye :)\n");
						Sleep(300);
						break;
					}
					case VK_PRIOR: {
						trigger_en = !trigger_en;
						printf_s("Trigger bot: %d \n", trigger_en);
						Sleep(300);
						break;
					}
					default: {
						break;
					}
				}
			}
			if (GetKeyState(VK_SPACE) & 0x8000) {
				if (bhop_en) {
					script.Bhop(mem);
				}
			}
			if (GetKeyState(VK_LMENU) & 0x8000) {
				if (trigger_en) {
					script.triggerBot(mem);
				}
			}
			if (wall_en) {
				script.wall_hack(mem);
			}
		}
	} while (is_running);
	return 0;
}