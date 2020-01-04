#ifndef GAME_H
#define GAME_H

#include "cardo.h"
#include "tricko.h"

#define NUM_PLAYERS 4
#define NUM_TEAMS 2
#define MAX_HAND 14
#define HAND_SPACE 260
#define MAX_TURNS 25
#define MAX_ROUNDS 60
#define MAX_MATCHES 2


typedef struct game Game;

struct game {
	Card deck[NUM_CARDS];
	Player players[NUM_PLAYERS];
	TrickSet trickset;
};


int init_game(Game *game, char names[NUM_PLAYERS][PLAYER_NAME],
	Strat *strats[NUM_PLAYERS]);
int deal_eight(Game *game);
int deal_six(Game *game);

#endif // GAME_H
