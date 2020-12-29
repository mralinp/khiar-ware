#pragma once

#define ON 1
#define OFF 0

#include "ScriptBot.h"

class SimpleGlow: public ScriptBot{
	struct Glow_Struct;
	DWORD getGlowObj();
	DWORD getGlowIdx(DWORD player);
public:
	SimpleGlow(MemoryManager* memoryManager);
	void refresh();
};
