#pragma once

#define ON 1
#define OFF 0

#include "MemoryManager.h"
#include "ScriptBot.h"

class SimpleGlow: public ScriptBot{
	struct Glow_Struct;
public:
	SimpleGlow();
	void refresh(MemoryManager* mem);
};