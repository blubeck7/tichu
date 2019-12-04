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

		for (i = 0; i < 17; i++)
			player->count[i] = player->has[i] = 0;

		player->strat = strat;

        return 0;
}

int print_player(Player *player)
{
        int i;

        printf("Player %d is %s.\n", player->num, player->name);
        printf("\tstrategy: %p\n", player->strat);
        printf("\tcards: %d\n", player->num_cards);
		printf("\t");
        for (i = 0; i < player->num_cards; i++)
                if (i < player->num_cards - 1)
                        printf("%s ", player->cards[i].name);
                else
                        printf("%s\n", player->cards[i].name);
        printf("\tcaptured: %d\n", player->num_captured_cards);
		if (player->num_captured_cards > 0)
			printf("\t");
        for (i = 0; i < player->num_captured_cards; i++)
                if (i < player->num_captured_cards - 1)
                        printf("%s ", player->captured_cards[i].name);
                else
                        printf("%s\n", player->captured_cards[i].name);
		printf("\tcount: ");
        for (i = 0; i < 16; i++)
			printf("%d ", player->count[i]);
		printf("%d\n", player->count[i]);
		printf("\thas:   ");
        for (i = 0; i < 16; i++)
			printf("%d ", player->has[i]);
		printf("%d\n", player->has[i]);
		
        return 0;
}

int update_count(Player *player)
{
	int i;

	// count of cards
        for (i = 0; i < player->num_cards; i++) {
		if (player->cards[i].value == PHOENIX) {
			player->count[DRAGON + 1]++;
			player->has[DRAGON + 1] = 1;
		} else {
			player->count[player->cards[i].value]++;
			player->has[player->cards[i].value] = 1;
		};
	}

	return 0;
		
}
