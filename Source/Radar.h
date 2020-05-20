#pragma once
#include "ScriptBot.h"

class Radar :public ScriptBot {
private: 
	void setSpotted(DWORD player);
public:
	Radar(MemoryManager* memoryManager);
	void refresh();
};
