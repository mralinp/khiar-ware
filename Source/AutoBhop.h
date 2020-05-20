#pragma once
#include "ScriptBot.h"

class AutoBhop :public ScriptBot {
	void forceJump();
public:
	AutoBhop(MemoryManager* memoryManger);
	void refresh();
};