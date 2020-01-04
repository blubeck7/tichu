#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/cardo.h"
#include "../inc/tricko.h"
#include "../inc/gameo.h"


Game game;
char names[NUM_PLAYERS][PLAYER_NAME] = {"Human", "Human", "Human", "Human"};
Strat *strats[NUM_PLAYERS] = {NULL, NULL, NULL, NULL};

int main(int argc, char *argv[])
{
	init_game(&game, names, strats);
	print_cards(game.deck, NUM_CARDS);

	return 0;
}
