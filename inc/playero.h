#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "trick.h"

int init_player(Player *player, int n, char name[PLAYER_NAME], Strat *strat);
int print_player(Player *player);
//int update_count(Player *player);

#endif //PLAYER_H
