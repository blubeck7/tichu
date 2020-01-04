#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/card.h"
#include "../inc/trick.h"
#include "../inc/types.h"

char *TRICK_NAMES[] = {"Pass", "Single", "Double", "Triple", "Full",
	"Straight", "Dstraight", "Bomb"};

void init_trickhelper(TrickHelper *trickhelper)
{
	int i, j;

	trickhelper->num_cards = 0;
	trickhelper->high = 0;
	for (i = 0; i < NUM_VALUES; i++) {
		trickhelper->counts[i] = 0; 
		trickhelper->counts_d[i] = 0; 
		trickhelper->counts_t[i] = 0; 
		for (j = 0; j < NUM_SUITS; j++)
			trickhelper->cards[i][j] = BLANK;
		for (j = 0; j < MAX_DOUBLES; j++) {
			trickhelper->doubles[i][j][0] = BLANK;
			trickhelper->doubles[i][j][1] = BLANK;
		}
		for (j = 0; j < MAX_TRIPLES; j++) {
			trickhelper->triples[i][j][0] = BLANK;
			trickhelper->triples[i][j][1] = BLANK;
			trickhelper->triples[i][j][2] = BLANK;
		}
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
	int i, value, pos, has_phoenix, count;

	sort_cards(cards, n);

	trickhelper->num_cards = n;
	trickhelper->high = get_value(cards[n - 1]);
	for (i = 0; i < n; i++) {
		value = get_value(cards[i]);
		pos = trickhelper->counts[value]++;
		trickhelper->cards[value][pos] = cards[i];
	}

	// doubles
	has_phoenix = trickhelper->counts[PHOENIX_VALUE];	
	for (i = ONE_VALUE + 1; i < PHOENIX_VALUE; i++) {
		count = trickhelper->counts[i];
		if (count >= 2)
			set_doubles_r(trickhelper, i, count);
		if (has_phoenix && count)
			set_doubles_ph(trickhelper, i, count);
	}

	// triples
	has_phoenix = trickhelper->counts[PHOENIX_VALUE];	
	for (i = ONE_VALUE + 1; i < PHOENIX_VALUE; i++) {
		count = trickhelper->counts[i];
		if (count >= 3)
			set_triples_r(trickhelper, i, count);
		if (has_phoenix && count >= 2)
			set_triples_ph(trickhelper, i, count);
	}
}

void set_doubles_ph(TrickHelper *trickhelper, int value, int count)
{
	int i, n;

	for (i = 0; i < count; i++) {
		n = trickhelper->counts_d[value]++;
		trickhelper->doubles[value][n][0] = trickhelper->cards[value][i];
		trickhelper->doubles[value][n][1] = PHOENIX;
	}

	return;
}

void set_doubles_r(TrickHelper *trickhelper, int value, int count)
{
	int i, j, n;

	for (i = 0; i < count; i++)
		for (j = i + 1; j < count; j++) {
			n = trickhelper->counts_d[value]++;
			trickhelper->doubles[value][n][0] = trickhelper->cards[value][i];
			trickhelper->doubles[value][n][1] = trickhelper->cards[value][j];
		}

	return;
}

void set_triples_ph(TrickHelper *trickhelper, int value, int count)
{
	int i, j, n;

	for (i = 0; i < count; i++)
		for (j = i + 1; j < count; j++) {
			n = trickhelper->counts_t[value]++;
			trickhelper->triples[value][n][0] = trickhelper->cards[value][i];
			trickhelper->triples[value][n][1] = trickhelper->cards[value][j];
			trickhelper->triples[value][n][2] = PHOENIX;
		}

	return;
}

void set_triples_r(TrickHelper *trickhelper, int value, int count)
{
	int i, j, k, n;

	for (i = 0; i < count; i++)
		for (j = i + 1; j < count; j++)
			for (k = j + 1; k < count; k++) {
				n = trickhelper->counts_t[value]++;
				trickhelper->triples[value][n][0] =
					trickhelper->cards[value][i];
				trickhelper->triples[value][n][1] =
					trickhelper->cards[value][j];
				trickhelper->triples[value][n][2] =
					trickhelper->cards[value][k];
		}

	return;
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

void copy_trick(Trick *dest, Trick *src)
{
	int i;

	dest->type = src->type;
	dest->length = src->length;
	dest->num_cards = src->num_cards;
	dest->high = src->high;
	dest->low = src->low;
	dest->has_phoenix = src->has_phoenix;
	for (i = 0; i < dest->num_cards; i++)
		dest->cards[i] = src->cards[i];

	return;
}

void init_trickset(TrickSet *trickset)
{
	trickset->num_tricks = 0;
}

void print_trickset(TrickSet *trickset)
{
	int i;

	printf("Trick Set: %d tricks\n", trickset->num_tricks);
	for (i = 0; i < trickset->num_tricks; i++) {
		printf("%d: ", i + 1);
		print_trick(&trickset->tricks[i]);
		printf("\n");
	}
}

void add_trick(TrickSet *trickset, Trick *trick)
{
	int i;

	i = trickset->num_tricks++;
	copy_trick(&trickset->tricks[i], trick);

	return;
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

	return;
}

void add_single(TrickSet *trickset, Card card)
{
	int value;
	Trick trick;

	value = get_value(card);
	set_trick(&trick, SINGLE, 1, 1, value, value, is_phoenix(card), &card);
	add_trick(trickset, &trick);

	return;
}

void make_doubles(TrickSet *trickset, Trick *top, Card cards[], int n)
{
	int i, j;
	TrickHelper trickhelper;

	init_trickhelper(&trickhelper);
	set_trickhelper(&trickhelper, cards, n);

	if (top) {
		for (i = top->high + 1; i < PHOENIX_VALUE; i++)	 
			for (j = 0; j < trickhelper.counts_d[i]; j++)	 
				add_double(trickset, trickhelper.doubles[i][j]);
	} else
		for (i = ONE_VALUE + 1; i < PHOENIX_VALUE; i++)	 
			for (j = 0; j < trickhelper.counts_d[i]; j++)	 
				add_double(trickset, trickhelper.doubles[i][j]);

	return;
}

void add_double(TrickSet *trickset, Card cards[])
{
	int value, i;
	Trick trick;

	i = 0;
	if (is_phoenix(cards[0]) || is_phoenix(cards[1]))
		i = 1;
	value = get_value(cards[0]);
	set_trick(&trick, DOUBLE, 1, 2, value, value, i, cards);
	add_trick(trickset, &trick);

	return;
}

void make_triples(TrickSet *trickset, Trick *top, Card cards[], int n)
{
	int i, j;
	TrickHelper trickhelper;

	init_trickhelper(&trickhelper);
	set_trickhelper(&trickhelper, cards, n);

	if (top) {
		for (i = top->high + 1; i < PHOENIX_VALUE; i++)	 
			for (j = 0; j < trickhelper.counts_t[i]; j++)	 
				add_triple(trickset, trickhelper.triples[i][j]);
	} else
		for (i = ONE_VALUE + 1; i < PHOENIX_VALUE; i++)	 
			for (j = 0; j < trickhelper.counts_t[i]; j++)	 
				add_triple(trickset, trickhelper.triples[i][j]);

	return;
}

void add_triple(TrickSet *trickset, Card cards[])
{
	int value, i;
	Trick trick;

	i = 0;
	if (is_phoenix(cards[0]) || is_phoenix(cards[1]) || is_phoenix(cards[2]))
		i = 1;
	value = get_value(cards[0]);
	set_trick(&trick, TRIPLE, 1, 3, value, value, i, cards);
	add_trick(trickset, &trick);

	return;
}

void make_quads(TrickSet *trickset, Trick *top, Card cards[], int n)
{
	int i, start;
	TrickHelper trickhelper;

	init_trickhelper(&trickhelper);
	set_trickhelper(&trickhelper, cards, n);

	start = 0;
	if (top)
		start = top->high + 1;

	for (i = start; i < PHOENIX_VALUE; i++)	 
		if (trickhelper.counts[i] == 4)
			add_quad(trickset, trickhelper.cards[i]);

	return;
}

void add_quad(TrickSet *trickset, Card cards[])
{
	int value;
	Trick trick;

	value = get_value(cards[0]);
	set_trick(&trick, BOMB, 1, 4, value, value, 0, cards);
	add_trick(trickset, &trick);

	return;
}

void make_straights(TrickSet *trickset, Trick *top, Card cards[], int n)
{
	int i, j;
	TrickHelper trickhelper;

	init_trickhelper(&trickhelper);
	set_trickhelper(&trickhelper, cards, n);
	
	if (top) 
		for (j = top->low + 1; j <= PHOENIX_VALUE - top->length; j++)
			add_straights(trickset, j, top->length, &trickhelper);
	else {
		for (i = MIN_STRAIGHT_LENGTH; i <= MAX_STRAIGHT_LENGTH; i++) 
			for (j = ONE_VALUE; j <= PHOENIX_VALUE - i; j++)
				add_straights(trickset, j, i, &trickhelper);
	}
		
	return;
}

void add_straights(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper)
{
	int i, sum, has_phoenix, val;

	val = -1;
	sum = sum_straight(low, length, trickhelper, &val);
	has_phoenix = trickhelper->counts[PHOENIX_VALUE];
	
	if (sum == length - 1 && has_phoenix)
		add_straights_ph(trickset, low, length, val, trickhelper);
	else if (sum == length && has_phoenix) {
		add_straights_r(trickset, low, length, trickhelper);
		for (i = 0; i < length; i++)
			add_straights_ph(trickset, low, length, low + i, trickhelper);
	} else if (sum == length && !has_phoenix)
		add_straights_r(trickset, low, length, trickhelper);

	return;
}

void add_straights_ph(TrickSet *trickset, int low, int length, int val,
	TrickHelper *trickhelper)
{
	int i, sum, counters[MAX_STRAIGHT_LENGTH], limits[MAX_STRAIGHT_LENGTH];
	Card cards[MAX_STRAIGHT_LENGTH];
	Trick trick;

	if (val == ONE_VALUE)
		return;

	for (i = 0; i < length; i++) {
		counters[i] = 0;
		limits[i] = trickhelper->counts[i + low];
	}
	limits[val - low] = 1; // phoenix position

	do {
		for (i = 0; i < length; i++)
			cards[i] = trickhelper->cards[i + low][counters[i]];
		cards[val - low] = PHOENIX;

		set_trick(&trick,
			STRAIGHT, length, length, low + length - 1, low, 1, cards);
		add_trick(trickset, &trick);
		inc_counters(counters, length, limits);
		sum = 0;
		for (i = 0; i < length; i++)
			sum += counters[i];
	} while (sum);

	return;
}

void add_straights_r(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper)
{

	int i, sum, flush, type, counters[MAX_STRAIGHT_LENGTH];
	Card cards[MAX_STRAIGHT_LENGTH];
	Trick trick;

	for (i = 0; i < length; i++)
		counters[i] = 0;

	/* Get the cards in the current straight. Add the straight to the trickset
	 * and then increment the counters. Stop when the counters are all zero
	 * again.
	 */
	do {
		for (i = 0; i < length; i++)
			cards[i] = trickhelper->cards[i + low][counters[i]];

		flush = 1;
		for (i = 1; i < length; i++)
			if (get_suit(cards[0]) == get_suit(cards[i]))
				flush++;

		type = STRAIGHT;
		if (flush == length)
			type = BOMB;

		set_trick(&trick,
			type, length, length, low + length - 1, low, 0, cards);
		add_trick(trickset, &trick);
		inc_counters(counters, length, &trickhelper->counts[low]);
		sum = 0;
		for (i = 0; i < length; i++)
			sum += counters[i];
	} while (sum);

	return;
}

int sum_straight(int low, int length, TrickHelper *trickhelper, int *val)
{
	int i, sum;

	sum = 0;
	for (i = 0; i < length; i++)
		if (trickhelper->counts[i + low])
			sum++;
		else
			*val = i + low;

	return sum;
}

void inc_counters(int *counters, int length, int *limits)
{
	int i, carry;

	(*(counters + length - 1))++;

	carry = 0;
	for (i = length - 1; i >=  0; i--) {
		*(counters + i) += carry;
		if (*(counters + i) == *(limits + i)) {
			*(counters + i) = 0;
			carry = 1;
		} else
			carry = 0;
	}

	return;
}

void make_dstraights(TrickSet *trickset, Trick *top, Card cards[], int n)
{
	int i, j;
	TrickHelper trickhelper;

	init_trickhelper(&trickhelper);
	set_trickhelper(&trickhelper, cards, n);
	
	if (top) 
		for (j = top->low + 1; j <= PHOENIX_VALUE - top->length; j++)
			add_dstraights(trickset, j, top->length, &trickhelper);
	else {
		for (i = MIN_DSTRAIGHT_LENGTH; i <= MAX_DSTRAIGHT_LENGTH; i++) 
			for (j = ONE_VALUE + 1; j <= PHOENIX_VALUE - i; j++)
				add_dstraights(trickset, j, i, &trickhelper);
	}
		
	return;
}

void add_dstraights(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper)
{
	int i, j, sum, has_phoenix, counters[MAX_DSTRAIGHT_LENGTH];
	Card cards[MAX_DSTRAIGHT_CARDS];
	Trick trick;

	sum = sum_dstraight(low, length, trickhelper);
	has_phoenix = trickhelper->counts[PHOENIX_VALUE];
	
	if ((sum == 2 * length) || (sum == 2 * length - 1 && has_phoenix)) {
		for (i = 0; i < length; i++)
			counters[i] = 0;
		do {
			j = 0;
			for (i = 0; i < length; i++) {
				cards[i * 2] =
					trickhelper->doubles[i + low][counters[i]][0];
				cards[i * 2 + 1] =
					trickhelper->doubles[i + low][counters[i]][1];

				if (is_phoenix(cards[i * 2]) ||
					is_phoenix(cards[i * 2 + 1]))
						j++;
			}

			if (j < 2) {
				set_trick(&trick, DSTRAIGHT, length, 2 * length,
					low + length - 1, low, j, cards);
				add_trick(trickset, &trick);
			}
			inc_counters(counters, length, &trickhelper->counts_d[low]);
			sum = 0;
			for (i = 0; i < length; i++)
				sum += counters[i];
		} while (sum);
	}

	return;
}

int sum_dstraight(int low, int length, TrickHelper *trickhelper)
{
	int i, sum;

	sum = 0;
	for (i = 0; i < length; i++) {
		if (trickhelper->counts[i + low] > 1)
			sum += 2;
		else if (trickhelper->counts[i + low] == 1)
			sum++;
	}

	return sum;
}

void make_fulls(TrickSet *trickset, Trick *top, Card cards[], int n)
{
	int i, j, trip;
	TrickHelper trickhelper;

	init_trickhelper(&trickhelper);
	set_trickhelper(&trickhelper, cards, n);
	
	trip = ONE_VALUE + 1;
	if (top) 
		trip = top->high + 1;

	for (i = trip; i < PHOENIX_VALUE; i++)
		for (j = ONE_VALUE + 1; j < PHOENIX_VALUE; j++) {
			if (trickhelper.counts_t[i] && trickhelper.counts_d[j] && i != j) {
				add_fulls(trickset, i, j, &trickhelper);
			}	
		}
	return;
}

void add_fulls(TrickSet *trickset, int trip, int doub,
	TrickHelper *trickhelper)
{
	int i, j, k, sum;
	Card cards[5];
	Trick trick;

	for (i = 0; i < trickhelper->counts_t[trip]; i++) {
		cards[0] = trickhelper->triples[trip][i][0];
		cards[1] = trickhelper->triples[trip][i][1];
		cards[2] = trickhelper->triples[trip][i][2];
		for (j = 0; j < trickhelper->counts_d[doub]; j++) {
			cards[3] = trickhelper->doubles[doub][j][0];
			cards[4] = trickhelper->doubles[doub][j][1];
		
			sum = 0;
			for (k = 0; k < 5; k++)
				if (is_phoenix(cards[k]))
					sum++;

			if (sum < 2) {
				set_trick(&trick, FULL, 5, 5, trip, doub, sum, cards);
				add_trick(trickset, &trick);
			}
		}
	}

	return;
}
