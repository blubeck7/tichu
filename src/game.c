#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../inc/game.h"


typedef struct game_t {
	Deck deck;
	Player players[4];
} Card;
