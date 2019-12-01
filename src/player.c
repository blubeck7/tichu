#include <stdio.h>
#include <string.h>
#include "../inc/game.h"
#include "../inc/player.h"
#include "../inc/types.h"

int init_player(Player *player, int n, char name[PLAYER_NAME], Strat *strat)
{
        player->num = n;
        strcpy(player->name, name);
        player->num_cards = 0;
        player->strat = strat;

        return 0;
}

int print_player(Player *player)
{
        int i;

        printf("Player %d is %s.\n", player->num, player->name);
        printf("Player %d has %d cards.\n", player->num, player->num_cards);
        for (i = 0; i < player->num_cards; i++)
                if (i < player->num_cards - 1)
                        printf("%s ", player->cards[i].name);
                else
                        printf("%s\n", player->cards[i].name);
                
        return 0;
}