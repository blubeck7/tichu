#include <stdio.h>
#include <string.h>
#include "../inc/card.h"
#include "../inc/trick.h"
#include "../inc/player.h"
#include "../inc/types.h"

int init_player(Player *player, int n, char name[PLAYER_NAME], Strat *strat)
{	
		int i;

        player->num = n;
        strcpy(player->name, name);
        player->num_cards = 0;

		for (i = 0; i < MAX_HAND; i++)
			player->cards[i] = BLANK;

        player->num_captured_cards = 0;
		for (i = 0; i < NUM_CARDS; i++)
			player->captured_cards[i] = BLANK;

		player->strat = strat;

        return 0;
}

int print_player(Player *player)
{
        printf("Player %d is %s.\n", player->num, player->name);
        printf("Strategy: %p\n", player->strat);
        printf("Number of Cards: %d\n", player->num_cards);
		print_cards(player->cards, player->num_cards);
		//printf("\n");
        printf("Number of Captured Cards: %d\n", player->num_captured_cards);
		print_cards(player->captured_cards, player->num_captured_cards);
		
        return 0;
}
