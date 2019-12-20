#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/cardo.h"

Card CARDS[NUM_CARDS] = {
	4,  14,
	20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140,
	21, 31, 41, 51, 61, 71, 81, 91, 101, 111, 121, 131, 141,
	22, 32, 42, 52, 62, 72, 82, 92, 102, 112, 122, 132, 142,
	23, 33, 43, 53, 63, 73, 83, 93, 103, 113, 123, 133, 143,
	154, 164};

char *VALUE_NAMES[NUM_VALUES] = {
	"Dog", "One",
	"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A",
	"Phoenix", "Dragon"};

char *SUIT_NAMES[NUM_SUITS + 1] = {"c", "d", "h", "s", ""};

int get_value(Card card)
{
	return card / 10;
}

int get_suit(Card card)
{
	return card % 10;
}

void print_card(Card card)
{
	printf("%s%s", VALUE_NAMES[get_value(card)], SUIT_NAMES[get_suit(card)]);
}

void print_cards(Card cards[], int n)
{
	int i;

	for (i = 0; i < n; i++) {
		print_card(cards[i]);
		if (i < n - 1)
			printf(" ");
	}
	printf("\n");
}

static void swap_cards(Card cards[], int i, int j)
{
	Card card;

	card = cards[i];
	cards[i] = cards[j];
	cards[j] = card;

	return;
}

void sort_cards(Card cards[], int n)
{
	int i, done;

	done = 0;
	while (!done) {
		done = 1;
		for (i = 0; i < n - 1; i++) {
			if (cards[i + 1] < cards[i]) {
				swap_cards(cards, i, i + 1);
				done = 0;
			}
		}
	}
}

void add_card(Card cards[], int *n, Card card)
{
	cards[(*n)++] = card;
}

static int search_card(Card cards[], int n, Card card, int *p)
{
	int i;

	for (i = 0; i < n; i++)
		if (cards[i] == card) {
			*p = i;
			return 1;
		}

	return 0;
}

void remove_card(Card cards[], int *n, Card card)
{
	int i, p;

	if (!search_card(cards, *n, card, &p))
		return;

	(*n)--;
	for (i = p; i < *n; i++) 
		cards[i] = cards[i + 1];
	cards[i] = 0;
}

int has_card(Card cards[], int n, Card card)
{
	int p;

	return search_card(cards, n, card, &p);
}

int has_dog(Card cards[], int n)
{
	return has_card(cards, n, DOG);
}

int has_one(Card cards[], int n)
{
	return has_card(cards, n, ONE);
}

int has_phoenix(Card cards[], int n)
{
	return has_card(cards, n, PHOENIX);
}

int has_dragon(Card cards[], int n)
{
	return has_card(cards, n, DRAGON);
}

/*
int count_value(CardSet *cardset, int value)
{
	int i, count;

	count = 0;

	switch (value) {
	case DOG_VALUE:
		count = has_dog(cardset);
		break;
	case ONE_VALUE:
		count = has_one(cardset);
		break;
	case PHOENIX_VALUE:
		count = has_phoenix(cardset);
		break;
	case DRAGON_VALUE:
		count = has_dragon(cardset);
		break;
	default:
		for (i = 0; i < NUM_SUITS; i++)
			count += has_card(cardset, value * 10 + i);
		break;		
	}	

	return count;
}

int get_num_cards(CardSet *cardset)
{
	return cardset->num_cards;
}
*/