#ifndef SIMPLE_GLOW_H
#define SIMPLE_GLOW

#include "ScriptBot.h"

class SimpleGlow: public ScriptBot{

	struct Glow_Struct;
	DWORD getGlowObjManager();
	DWORD getGlowIdx(DWORD player);

public:
	void refresh();

};

#endif