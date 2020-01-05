#include "MemoryManager.h"
#include <string>
#include <iostream>
#include <ctime>
#include <thread>
memory_manager* mem;


#define m_dwLocalPlayer 0xD28B1C
#define m_iTeamNum 0xF4
#define m_iCrossHairID 0xB3D4
#define m_dwEntityList 0x4D3C68C



const char logo[][51] = {
	"  _  ___     _          __        __    ___",
	" | |/ / |__ (_) __ _ _ _\\ \\      / /_ _|  _ \\ ___ ",
	" | ' /| '_ \\| |/ _` | '__\\ \\ /\\ / / _` | |_) / _ \\",
	" | . \\| | | | | (_| | |   \\ V  V / (_| |  _ <  __/",
	" |_|\\_\\_| |_|_|\\__,_|_|    \\_/\\_/ \\__,_|_| \\_\\___|"
};

void printLogo() {
	for (int i = 0; i < 5; i++) {
		printf("\t%s\n", logo[i]);
	}
}




int main()
{
    mem = new memory_manager(); 
	while (true) {
	DWORD dwLocalPlayer = 0;
	dwLocalPlayer = mem->Read<DWORD>(mem->ClientDLL_Base + m_dwLocalPlayer);
	BYTE fFlags = 0; 
	fFlags = mem->Read<BYTE>(dwLocalPlayer + 0x104);
	
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (fFlags & (1 << 0))
			{
				mem->Write(mem->ClientDLL_Base + 0x51DFEAC, 6);
			}
			printf("hello, world!");
		}
		Sleep(20);
	}
	delete mem; 
	return 0;
}