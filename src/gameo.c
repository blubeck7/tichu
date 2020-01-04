#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/cardo.h"
#include "../inc/tricko.h"
#include "../inc/gameo.h"


int init_game(Game *game, char names[NUM_PLAYERS][PLAYER_NAME],
	Strat *strats[NUM_PLAYERS])
{
	int i, j;

	for (i = 0; i < NUM_CARDS; i++)
		game->deck[i] = CARDS[i];
	shuffle_cards(game->deck, NUM_CARDS);
	
	for (i = 0; i < NUM_PLAYERS; i++) {
		game->players[i].num = i;
		strcpy(game->players[i].name, names[i]);
		game->players[i].num_cards = MAX_HAND;
		for (j = 0; j < MAX_HAND; j++)
			game->players[i].cards[j] = BLANK;
		game->players[i].num_captured_cards = 0;
		for (j = 0; j < NUM_CARDS; j++)
			game->players[i].captured_cards[j] = BLANK;
		game->players[i].strat = strats[i];
	}

	init_trickset(&(game->trickset));

	return 0;
}

