#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/card.h"

typedef struct card_t {
	int value;
	int suit;
	wchar_t name[CARD_NAME_SIZE];
} Card;


Card *create_card(int value, int suit, wchar_t name[CARD_NAME_SIZE])
{
	Card *card;

	card = malloc(sizeof(Card));
	if (card == NULL)
		exit(EXIT_FAILURE);

	card->value = value;
	card->suit = suit;
	wcscpy(card->name, name);

	return card;
}

int destroy_card(Card *card)
{
	free(card);

	return 0;
}

int print_card(Card *card)
{
	wprintf(L"%ls", card->name);

	return 0;
}
