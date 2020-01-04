#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "trick.h"
#include "types.h"


int init_game(Game *game, char names[NUM_PLAYERS][PLAYER_NAME],
	Strat *strats[NUM_PLAYERS]);
void print_game(Game *game);
int deal_eight(Game *game);
int deal_six(Game *game);

#endif // GAME_H
