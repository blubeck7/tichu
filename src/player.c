#include <stdio.h>
#include <string.h>
#include "../inc/game.h"
#include "../inc/player.h"

int init_player(Player *player, int n)
{
        int i;

        player->num = n;
        strcpy(player->name, "Human");
        player->num_cards = MAX_HAND;
        player->strat = NULL;
        for (i = 0; i < MAX_HAND; i++) {
                player->cards[i].value = -1;
                player->cards[i].suit = -1;
                player->cards[i].name[0] = '\0';
        }
}

int print_player(Player *player)
{
        int i;

        printf("Player %d is %s.\n", player->num, player->name);
        printf("Player %d has %d cards.\n", player->num, player->num_cards);
        for (i = 0; i < player->num_cards; i++)
}