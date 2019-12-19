#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/cardo.h"
#include "../inc/tricko.h"


char *TRICK_NAMES[] = {"pass", "single", "double", "triple", "full",
	"straight", "dstraight", "bomb"};

void init_trick(Trick *trick)
{
	int i;

	trick->type = PASS;
	trick->length = 0;
	trick->num_cards = 0;
	trick->high = 0;
	trick->low = 0;
	trick->has_phoenix = 0;
	for (i = 0; i < MAX_TRICK; i++)
		trick->cards[i] = 0;
}

void set_trick(Trick *trick, int type, int length, int num_cards, int high,
	int low, int has_phoenix, Card cards[MAX_TRICK])
{
	int i;

	trick->type = type;
	trick->length = length;
	trick->num_cards = num_cards;
	trick->high = high;
	trick->low = low;
	trick->has_phoenix = has_phoenix;
	for (i = 0; i < num_cards; i++)
		trick->cards[i] = cards[i];

	return;
}

void print_trick(Trick *trick)
{
	int i;

	printf("Type=%s, ", TRICK_NAMES[trick->type]);
	printf("Len=%d, Num=%d, High=%d, Low=%d, Has_Phoenix=%d, ",
		trick->length, trick->num_cards, trick->high, hand->low,
		trick->has_phoenix);
	printf("cards=");
	for (i = 0; i < trick->num_cards; i++)
		print_card(trick->cards[i]);
	printf("\n");

	return 0;
}
int is_valid_trick(Trick *trick, Trick *top);

void init_trickset(TrickSet *trickset);
void add_single(TrickSet *trickset, Trick *single);
