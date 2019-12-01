#ifndef GAME_H
#define GAME_H


#include "types.h"


int init_game(Game *game);
int deal_eight(Game *game);
int deal_six(Game *game);
int valid_hand(Game *game, Hand *hand);
int get_hands(Game *game, Player *player);
int sort_cards(Card cards[MAX_HAND], int num_cards);


#endif // GAME_H
