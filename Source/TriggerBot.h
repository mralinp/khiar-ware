#pragma once
#include "MemoryManager.h"
#include "ScriptBot.h"

class TriggerBot:public ScriptBot{

public:
	TriggerBot();
	void refresh(MemoryManager* mem);
};

