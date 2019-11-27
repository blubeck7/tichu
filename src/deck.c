#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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
	int order[DECK_SIZE];
	Card cards[DECK_SIZE];
} Deck;

// Deck is initialized at compile-time.
Deck deck =
{
	DECK_SIZE,
	{0}, {
		{2, 1, "2c"},
		{3, 1, "3c"},
		{4, 1, "4c"},
		{5, 1, "5c"},
		{6, 1, "6c"},
		{7, 1, "7c"},
		{8, 1, "8c"},
		{9, 1, "9c"},
		{10, 1, "10c"},
		{11, 1, "Jc"},
		{12, 1, "Qc"},
		{13, 1, "Kc"},
		{14, 1, "Ac"},
		{2, 2, "2d"},
		{3, 2, "3d"},
		{4, 2, "4d"},
		{5, 2, "5d"},
		{6, 2, "6d"},
		{7, 2, "7d"},
		{8, 2, "8d"},
		{9, 2, "9d"},
		{10, 2, "10d"},
		{11, 2, "Jd"},
		{12, 2, "Qd"},
		{13, 2, "Kd"},
		{14, 2, "Ad"},
		{2, 3, "2h"},
		{3, 3, "3h"},
		{4, 3, "4h"},
		{5, 3, "5h"},
		{6, 3, "6h"},
		{7, 3, "7h"},
		{8, 3, "8h"},
		{9, 3, "9h"},
		{10, 3, "10h"},
		{11, 3, "Jh"},
		{12, 3, "Qh"},
		{13, 3, "Kh"},
		{14, 3, "Ah"},
		{2, 4, "2s"},
		{3, 4, "3s"},
		{4, 4, "4s"},
		{5, 4, "5s"},
		{6, 4, "6s"},
		{7, 4, "7s"},
		{8, 4, "8s"},
		{9, 4, "9s"},
		{10, 4, "10s"},
		{11, 4, "Js"},
		{12, 4, "Qs"},
		{13, 4, "Ks"},
		{14, 4, "As"},
		{0, 0, "Dog"},
		{1, 0, "One"},
		{-1, 0, "Phoenix"},
		{15, 0, "Dragon"}
	}
}; 

int print_deck(void)
{
	int i;

	for (i = 0; i < deck.size; i++)
		printf("%s\n", deck.cards[i].name);

	return 0;
}

int print_deck_all(void)
{
	int i;

	for (i = 0; i < deck.size; i++)
		printf("%d ", deck.order[i]);
	printf("\n");

	for (i = 0; i < deck.size; i++)
		printf("%-2d %d %s\n",
		deck.cards[i].value,
		deck.cards[i].suit,
		deck.cards[i].name);

	return 0;
}

int shuffle_deck(void)
{
	int cards[DECK_SIZE], n_rem, pos, i, j;

	for (i = 0; i < DECK_SIZE; i++)
		cards[i] = i;

	/* TODO: implement with a better random generator */
	srand((unsigned int) time(NULL));

	n_rem = DECK_SIZE;
	for (i = 0; i < DECK_SIZE; i++) {
		/* Randomly choose an unshuffled card. Then add it to the
		 * shuffled array. Shift the unshuffled cards down.
		 */
		/* TODO: Eliminate tail numbers */
		pos = rand() % n_rem;
		deck.order[i] = cards[pos];
		for (j = pos + 1; j < n_rem; j++)
			cards[j - 1] = cards[j];
		n_rem--;
	}

	return 0;
}

