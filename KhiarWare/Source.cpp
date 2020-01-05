#include "MemoryManager.h"
#include <string>
using namespace std;

const char logo[][51] = {
	"  _  ___     _          __        __    ___",
	" | |/ / |__ (_) __ _ _ _\\ \\      / /_ _|  _ \\ ___ ",
	" | ' /| '_ \\| |/ _` | '__\\ \\ /\\ / / _` | |_) / _ \\",
	" | . \\| | | | | (_| | |   \\ V  V / (_| |  _ <  __/",
	" |_|\\_\\_| |_|_|\\__,_|_|    \\_/\\_/ \\__,_|_| \\_\\___|"
};

void printLogo() {
	for (int i = 0; i < 5; i++) {
		printf("\t%s\n", logo[i]);
	}
}

int main() {
	printLogo();
	memory_manager mem;
	return 0;
}