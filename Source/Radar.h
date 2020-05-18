#pragma once
#include "ScriptBot.h"

class Radar :public ScriptBot {
public:
	Radar();
	void refresh(MemoryManager* mem);
};
