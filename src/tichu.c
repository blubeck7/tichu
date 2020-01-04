#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/card.h"
#include "../inc/trick.h"
#include "../inc/player.h"
#include "../inc/game.h"
#include "../inc/types.h"


int main(int argc, char *argv[])
{
	Game *game;
	char names[NUM_PLAYERS][PLAYER_NAME] = {"Human","Human","Human","Human"};
	Strat *strats[NUM_PLAYERS] = {NULL, NULL, NULL, NULL};
	
	game = malloc(sizeof(Game));

	init_game(game, names, strats);
	print_game(game);

	return 0;
}
