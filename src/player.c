#include <stdio.h>
#include <string.h>
#include "../inc/game.h"
#include "../inc/player.h"
#include "../inc/types.h"

int init_player(Player *player, int n, char name[PLAYER_NAME], Strat *strat)
{	
		int i;

        player->num = n;
        strcpy(player->name, name);
        player->num_cards = 0;

		for (i = 0; i < MAX_HAND; i++) {
			player->cards[i].value = 0;
			player->cards[i].suit = 0;
			strcpy(player->cards[i].name, "");
		}

        player->num_captured_cards = 0;
		for (i = 0; i < DECK_SIZE; i++) {
			player->captured_cards[i].value = 0;
			player->captured_cards[i].suit = 0;
			strcpy(player->captured_cards[i].name, "");
		}

		player->has_one = 0;
		player->has_dog = 0;
		player->has_phoenix = 0;
		player->has_dragon = 0;

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
