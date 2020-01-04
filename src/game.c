#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../inc/types.h"
#include "../inc/card.h"
#include "../inc/trick.h"
#include "../inc/game.h"
#include "../inc/player.h"


int init_game(Game *game, char names[NUM_PLAYERS][PLAYER_NAME],
	Strat *strats[NUM_PLAYERS])
{
	int i;

	for (i = 0; i < NUM_CARDS; i++)
		game->deck[i] = CARDS[i];
	
	for (i = 0; i < NUM_PLAYERS; i++)
		init_player(game->players + i, i, names[i], strats[i]);

	init_trickset(&game->cur_state.cur_tricks);
	game->cur_state.is_game_done = 0;
	for (i = 0; i < NUM_TEAMS; i++)
		game->cur_state.team_points[i] = 0;

	return 0;
}

void print_game(Game *game)
{
	int i;

	printf("Game %d\n", game->cur_state.is_game_done);
	for (i = 0; i < NUM_PLAYERS; i++)
		print_player(game->players + i);

	for (i = 0; i < NUM_TEAMS; i++)
		printf("Team %d has %d points.\n", i, game->cur_state.team_points[i]);

	return;
}