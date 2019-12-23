#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/cardo.h"
#include "../inc/tricko.h"

char *TRICK_NAMES[] = {"Pass", "Single", "Double", "Triple", "Full",
	"Straight", "Dstraight", "Bomb"};

void init_trickhelper(TrickHelper *trickhelper)
{
	int i, j;

	trickhelper->num_cards = 0;
	trickhelper->high = 0;
	for (i = 0; i < NUM_VALUES; i++) {
		trickhelper->counts[i] = 0; 
		for (j = 0; j < NUM_SUITS; j++)
			trickhelper->cards[i][j] = BLANK;
	}
}

void print_trickhelper(TrickHelper *trickhelper)
{
	int i, j, k;

	printf("Trick Helper: %d cards %d high\n",
		trickhelper->num_cards, trickhelper->high);
	printf("Counts\n");
	for (i = 0; i < NUM_VALUES; i++) {
		k = trickhelper->counts[i];
		printf("%d %d ", i, k); 
		for (j = 0; j < k; j++) {
			if (j < k - 1) {
				print_card(trickhelper->cards[i][j]);
				printf(" ");
			} else
				print_card(trickhelper->cards[i][j]);
		}
		printf("\n");
	}
}

void set_trickhelper(TrickHelper *trickhelper, Card cards[], int n)
{
	int i, value, pos;

	sort_cards(cards, n);

	trickhelper->num_cards = n;
	trickhelper->high = get_value(cards[n - 1]);
	for (i = 0; i < n; i++) {
		value = get_value(cards[i]);
		pos = trickhelper->counts[value]++;
		trickhelper->cards[value][pos] = cards[i];
	}
}

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

void print_trick(Trick *trick)
{
	int i;

	printf("Type=%s, ", TRICK_NAMES[trick->type]);
	printf("Len=%d, Num=%d, High=%d, Low=%d, Has_Phoenix=%d, ",
		trick->length, trick->num_cards, trick->high, trick->low,
		trick->has_phoenix);
	printf("Cards=");
	for (i = 0; i < trick->num_cards; i++)
		print_card(trick->cards[i]);
}

void set_trick(Trick *trick, int type, int length, int num_cards, int high,
	int low, int has_phoenix, Card *cards)
{
	int i;

	trick->type = type;
	trick->length = length;
	trick->num_cards = num_cards;
	trick->high = high;
	trick->low = low;
	trick->has_phoenix = has_phoenix;
	for (i = 0; i < num_cards; i++)
		trick->cards[i] = *(cards + i);

	return;
}

void init_trickset(TrickSet *trickset)
{
	trickset->num_tricks = 0;
}

void print_trickset(TrickSet *trickset)
{
	int i;

	printf("Trick Set\n");
	printf("%d tricks\n", trickset->num_tricks);
	for (i = 0; i < trickset->num_tricks; i++) {
		print_trick(&trickset->tricks[i]);
		printf("\n");
	}
}

void make_singles(TrickSet *trickset, Trick *top, Card cards[], int n)
{
	int i;

	if (top) {
		for (i = 0; i < n; i++)	 
			if (get_value(cards[i]) > top->high)
				add_single(trickset, cards[i]);
	} else
		for (i = 0; i < n; i++)
			add_single(trickset, cards[i]);
}

void add_single(TrickSet *trickset, Card card)
{
	int value;
	Trick *trick;

	trick = trickset->tricks + trickset->num_tricks++;
	value = get_value(card);
	set_trick(trick, SINGLE, 1, 1, value, value, is_phoenix(card), &card);
}

void make_straights(TrickSet *trickset, Trick *top, Card cards[], int n)
{
	TrickHelper trickhelper;

	init_trickhelper(&trickhelper);
	set_trickhelper(&trickhelper, cards, n);
	
	if (top) 
		add_straights(trickset, top->low + 1, top->length, &trickhelper);

	return;
}

void add_straights(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper)
{
	int i, sum, has_phoenix, pos;

	sum = sum_straight(low, length, trickhelper, &pos);
	has_phoenix = trickhelper->counts[PHOENIX_VALUE];
	
	if (sum == length - 1 && has_phoenix)
		add_straights_ph(trickset, low, length, pos, trickhelper);
	else if (sum == length && has_phoenix) {
		add_straights_r(trickset, low, length, trickhelper);
		for (i = 0; i < length; i++)
			add_straights_ph(trickset, low, length, pos, trickhelper);
	} else if (sum == length && !has_phoenix)
		add_straights_r(trickset, low, length, trickhelper);

	return;
}

int sum_straight(int low, int length, TrickHelper *trickhelper, int *pos)
{
	int i, sum;

	sum = 0;
	for (i = 0; i < length; i++)
		if (trickhelper->counts[i + low])
			sum++;
		else
			*pos = i;

	return sum;
}













