#pragma once

#include <random>
#include <time.h>
#include "ScriptBot.h"


class TriggerBot:public ScriptBot{

public:
	TriggerBot();
	void refresh(MemoryManager* mem);
};

