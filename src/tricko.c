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

	trickhelper->has_phoenix = 0;
	for (i = 0; i < NUM_RVALUES; i++) {
		trickhelper->reg_counts[i] = 0; 
		for (j = 0; j < NUM_SUITS; j++) {
			trickhelper->reg_cards[i][j] = BLANK;
		}
	}
}

void print_trickhelper(TrickHelper *trickhelper)
{
	int i, j, k;

	printf("TrickHelper\n");
	printf("Has phoenix %d\n", trickhelper->has_phoenix);
	printf("Reg counts\n");
	for (i = 0; i < NUM_RVALUES; i++) {
		k = trickhelper->reg_counts[i];
		printf("%d %d ", i + 2, k); 
		for (j = 0; j < k; j++) {
			if (j < k - 1) {
				print_card(trickhelper->reg_cards[i][j]);
				printf(" ");
			} else
				print_card(trickhelper->reg_cards[i][j]);
		}
		printf("\n");	
	}
}

void set_trickhelper(TrickHelper *trickhelper, Card cards[], int n)
{
	int i, j, k;
	Card card;

	for (i = 0; i < n; i++) {
		card = cards[i];
		if (card == PHOENIX)
			trickhelper->has_phoenix = 1;
		if (card > ONE && card < PHOENIX) {
			j = get_value(card) - 2;
			k = trickhelper->reg_counts[j]++;
			trickhelper->reg_cards[j][k] = card;
		}
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

void print_trickset(TrickSet *trickset)
{
	int i;

	printf("TrickSet\n");
	for (i = 0; i < trickset->num_tricks; i++) {
		print_trick(&trickset->tricks[i]);
		printf("\n");
	}
}

void make_singles(TrickSet *trickset, Card cards[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		add_single(trickset, cards[i]);
}

void add_single(TrickSet *trickset, Card card)
{
	int i;

	i = trickset->num_tricks++;
	trickset->tricks[i].type = SINGLE;
	trickset->tricks[i].length = 1;
	trickset->tricks[i].num_cards = 1;
	trickset->tricks[i].high = get_value(card);
	trickset->tricks[i].low = trickset->tricks[i].high;
	trickset->tricks[i].has_phoenix = is_phoenix(card);
	trickset->tricks[i].cards[0] = card;
}

/*
int is_valid_trick(Trick *trick, Trick *top);

void init_trickset(TrickSet *trickset);
void add_single(TrickSet *trickset, Trick *single);
*/