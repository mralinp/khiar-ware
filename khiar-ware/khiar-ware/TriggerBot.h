#pragma once

#include <random>
#include <time.h>
#include "ScriptBot.h"


class TriggerBot:public ScriptBot{
	void Shoot();
public:
	TriggerBot(MemoryManager* memoryManager);
	void refresh();
};

