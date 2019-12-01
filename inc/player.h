#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

int init_player(Player *player, int n, char name[PLAYER_NAME], Strat *strat);
int print_player(Player *player);

#endif //PLAYER_H