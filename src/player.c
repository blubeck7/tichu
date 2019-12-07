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

		for (i = 0; i < 17; i++) {
			player->counts[i].count = 0;
		   	player->has[i] = 0;
		}

		player->strat = strat;

        return 0;
}

int print_player(Player *player)
{
        int i, j;

        printf("Player %d is %s.\n", player->num, player->name);
        printf("\tStrategy: %p\n", player->strat);
        printf("\tNumber of Cards: %d\n", player->num_cards);

        for (i = 0; i < 17; i++) {
        	if (player->counts[i].count > 0) {
				//printf("\t%d %d\n", i, player->counts[i].count);
				for (j = 0; j < player->counts[i].count; j++) {
            		printf("%s\n", player->counts[i].cards[j].name);
				}
			}
		}

		printf("\tcount: ");
        for (i = 0; i < 16; i++)
			printf("%d ", player->counts[i].count);
		printf("%d\n", player->counts[i].count);
		printf("\thas:   ");
        for (i = 0; i < 16; i++)
			printf("%d ", player->has[i]);
		printf("%d\n", player->has[i]);

        printf("\tcaptured: %d\n", player->num_captured_cards);
		if (player->num_captured_cards > 0)
			printf("\t");
        for (i = 0; i < player->num_captured_cards; i++)
                if (i < player->num_captured_cards - 1)
                        printf("%s ", player->captured_cards[i].name);
                else
                        printf("%s\n", player->captured_cards[i].name);
		
        return 0;
}

int update_count(Player *player)
{
	int i, n;

	// count of cards
	for (i = 0; i < player->num_cards; i++) {
		n = ++player->counts[player->cards[i].value].count;
		player->counts[player->cards[i].value].cards[n].value =
			player->cards[i].value;
		player->counts[player->cards[i].value].cards[n].suit =
			player->cards[i].suit;
		strcpy(player->counts[player->cards[i].value].cards[n].name,
			player->cards[i].name);

		player->has[player->cards[i].value] = 1;
	};

	return 0;
		
}
