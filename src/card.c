#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/card.h"

#define NUM_CARDS 56
#define NUM_VALUES 17
#define NUM_RVALUES 13
#define NUM_SUITS 5 
#define NUM_RSUITS 4

#define DOG 0
#define ONE 10
#define DRAGON 150
#define PHOENIX 160

#define get_value(card) (card / 10)
#define get_suit(card) (card % 10)

//extern Card CARDS[NUM_CARDS];

Card CARDS[NUM_CARDS] = {
	0, 10,
	21, 31, 41, 51, 61, 71, 81, 91, 101, 111, 121, 131, 141,
	22, 32, 42, 52, 62, 72, 82, 92, 102, 112, 122, 132, 142,
	23, 33, 43, 53, 63, 73, 83, 93, 103, 113, 123, 133, 143,
	24, 34, 44, 54, 64, 74, 84, 94, 104, 114, 124, 134, 144,
	150, 160
};

char *VALUE_NAMES[NUM_VALUES] = {
	"Dog", "One",
	"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A",
	"Dragon", "Phoenix"
};

char *SUIT_NAMES[NUM_SUITS] = {"\0", "c", "d", "h", "s"};

int print_card(Card card)
{
	int value, suit;

	value = get_value(card);
	suit = get_suit(card);

	printf("%s%s", VALUE_NAMES[value], SUIT_NAMES[suit]);

	return 0;
};

int init_card_count(Card_Count *card_count)
{
	int i, j;

	card_count->num_cards = 0;

	for (i = 0; i < NUM_VALUES; i++) {
		card_count->counts[i] = 0;
		card_count->one_flags[i] = 0;
		card_count->two_flags[i] = 0;
	}

	for (i = 0; i < NUM_VALUES - 4; i++)
		for (j = 0; j < NUM_SUITS - 1; j++)
			card_count->cards[i][j] = 0;

	return 0;
}

int count_cards(Card cards[], int num_cards, Card_Count *card_count)
{
	int i;
	int value, suit;
	Card card;

	card_count->num_cards = num_cards;

	for (i = 0; i < num_cards; i++) {
		card = cards[i];
		value = get_value(card);
		suit = get_suit(card);
		card_count->counts[value]++;
		card_count->cards[value - 2][suit - 1] = card;
	}

	for (i = 0; i < num_cards; i++) {
		if (card_count->counts[i] == 1)
			card_count->one_flags[i] = 1;
		else if (card_count->counts[i] == 2)
			card_count->one_flags[i] = 1;
	}

	return 0;
}

int print_card_count(Card_Count *card_count)
{
	int i, j;

	printf("Number of cards: %d\n", card_count->num_cards);

	printf("Value: ");
	for (i = 0; i < NUM_VALUES - 1; i++)
		printf("%3d ", i);
	printf("%3d\n", i);

	printf("Count: ");
	for (i = 0; i < NUM_VALUES - 1; i++)
		printf("%3d ", card_count->counts[i]);
	printf("%3d\n", card_count->counts[i]);

	printf("OneFl: ");
	for (i = 0; i < NUM_VALUES - 1; i++)
		printf("%3d ", card_count->one_flags[i]);
	printf("%3d\n", card_count->one_flags[i]);

	printf("TwoFl: ");
	for (i = 0; i < NUM_VALUES - 1; i++)
		printf("%3d ", card_count->two_flags[i]);
	printf("%3d\n", card_count->two_flags[i]);

	for (i = 0; i < NUM_RSUITS; i++) {
		if (i == 0)
			printf("Cards: ");
		else
			printf("       ");

		for (j = 0; j < NUM_RVALUES; j++)
			if (card_count->cards[i][j])
				printf("%3s ", print_card(card_count->cards[i][j]));
			else
				printf("    ");
		if (card_count->cards[i][j])
			printf("%3s\n", print_card(card_count->cards[i][j]));
		else
			printf("    \n");
	}

	return 0;
}

int sort_cards(Card cards[], int num_cards)
{
	int i, done;
	Card card;

	done = 0;
	while (!done) {
		done = 1;
		for (i = 0; i < num_cards - 1; i++) {
			if (cards[i + 1] < cards[i]) {
				card = cards[i];
				cards[i] = cards[i + 1];
				cards[i + 1] = card;

				done = 0;
			}
		}
	}

	return 0;
}
