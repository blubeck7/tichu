#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/card.h"

typedef struct card_t {
	int value;
	int suit;
	char name[CARD_NAME_SIZE];
} Card;


Card *create_card(int value, int suit, char name[CARD_NAME_SIZE])
{
	Card *card;

	card = malloc(sizeof(Card));

	card->value = value;
	card->suit = suit;
	strcpy(card->name, name);

	return card;
}

int destroy_card(Card *card)
{
	free(card);

	return 0;
}

int print_card(Card *card)
{
	printf("%s", card->name);

	return 0;
}

int print_cardf(Card *card)
{
	printf("%-2d %d %s", card->value, card->suit, card->name);

	return 0;
}
