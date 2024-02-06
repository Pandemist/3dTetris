#include "Game.h"
#include "View.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
	srand(time(NULL));
	Game tetris = Game();
	initView(&tetris,  argc, argv);
	return 0;
}
