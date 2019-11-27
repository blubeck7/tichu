#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/deck.h"

#define CARD_NAME_SIZE 10
#define DECK_SIZE 56


typedef struct card_t {
	int value;
	int suit;
	char name[CARD_NAME_SIZE];
} Card;

typedef struct deck_t {
	int size;
	Card cards[DECK_SIZE];
} Deck;


Deck *create_deck(void)
{
	Deck *deck;

	deck = malloc(sizeof(Deck));

	deck->size = DECK_SIZE;
	load_deck("res/cards.txt", deck);

	return deck;
}

int load_deck(char *file, Deck *deck)
{
	FILE *fp;
	int ch, i, j;
	char value[3], suit[2], name[CARD_NAME_SIZE];

	fp = fopen(file, "r");

	for (i = 0; i < DECK_SIZE; i++) {
		// read in the value of the card
		j = 0;
		while ((ch = fgetc(fp)) != ',')
			value[j++] = ch;
		value[j] = '\0';
		
		deck->cards[i].value = atoi(value);

		// read in the suit of the card
		j = 0;
		while ((ch = fgetc(fp)) != ',')
			suit[j++] = ch;
		suit[j] = '\0';

		deck->cards[i].suit = atoi(suit);

		// read in the name of the card
		j = 0;
		while ((ch = fgetc(fp)) != '\n')
		    name[j++] = ch;
		name[j] = '\0';

		strcpy(deck->cards[i].name, name);

	}

	fclose(fp);

	return 0;
}

int destroy_deck(Deck *deck)
{
	free(deck);

	return 0;
}

int print_deck(Deck *deck)
{
	int i;

	for (i = 0; i < deck->size; i++)
		printf("%s\n", deck->cards[i].name);

	return 0;
}

int print_deckf(Deck *deck)
{
	int i;

	for (i = 0; i < deck->size; i++)
		printf("%-2d %d %s\n",
		deck->cards[i].value,
		deck->cards[i].suit,
		deck->cards[i].name);

	return 0;
}
