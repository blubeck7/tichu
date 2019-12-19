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

static int search_card(CardSet *cardset, Card card)
{
	int low, high, mid;

	sort_cardset(cardset);

	low = 0;
	high = cardset->num_cards - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (card == cardset->cards[mid])
			return mid;
		else if (card > cardset->cards[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}

static void swap_cards(CardSet *cardset, int i, int j)
{
	Card card;

	card = cardset->cards[i];
	cardset->cards[i] = cardset->cards[j];
	cardset->cards[j] = card;

	return;
}

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

void init_cardset(CardSet *cardset)
{
	int i;

	cardset->num_cards = 0;
	for (i = 0; i < NUM_CARDS; i++)
		cardset->cards[i] = BLANK;
}

void print_cardset(CardSet *cardset)
{
	int i;

	printf("Number of Cards: %d\n", cardset->num_cards);
	if (!cardset->num_cards)
	   return;

	for (i = 0; i < cardset->num_cards; i++) {
		print_card(cardset->cards[i]);
		printf(" ");
	}
	printf("\n");
}

void add_card(CardSet *cardset, Card card)
{
	cardset->cards[cardset->num_cards++] = card;
}

void remove_card(CardSet *cardset, Card card)
{
	int i, pos;

	if ((pos = search_card(cardset, card)) < 0)
		return;

	cardset->num_cards--;
	for (i = pos; i < cardset->num_cards; i++) 
		cardset->cards[i] = cardset->cards[i + 1];
	cardset->cards[i] = 0;
}

void sort_cardset(CardSet *cardset)
{
	int i, done;

	done = 0;
	while (!done) {
		done = 1;
		for (i = 0; i < cardset->num_cards - 1; i++) {
			if (cardset->cards[i + 1] < cardset->cards[i]) {
				swap_cards(cardset, i, i + 1);
				done = 0;
			}
		}
	}
}

int has_dog(CardSet *cardset)
{
	return has_card(cardset, DOG);
}

int has_one(CardSet *cardset)
{
	return has_card(cardset, ONE);
}

int has_phoenix(CardSet *cardset)
{
	return has_card(cardset, PHOENIX);
}

int has_dragon(CardSet *cardset)
{
	return has_card(cardset, DRAGON);
}

int has_card(CardSet *cardset, Card card)
{
	if (search_card(cardset, card) >= 0)
		return 1;

	return 0;
}

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
