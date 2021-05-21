#include "ScriptBot.h"

class Radar :public ScriptBot {
private: 
	void setSpotted(DWORD player);
public:
	void refresh();
};
