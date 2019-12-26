#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/cardo.h"
#include "../inc/tricko.h"

int rand_hand(Card cards[], int num_cards);

TrickSet trickset;

int main(int argc, char *argv[])
{
	Card cards[MAX_TRICK];
	int n;
	Trick trick;

	n = 14;
	rand_hand(cards, n);
	/*
	cards[0] = ONE;
	cards[1] = 20;
	cards[2] = 31;
	cards[3] = 40;
	cards[4] = 41;
	cards[5] = 102;
	cards[6] = 130;
	cards[7] = 141;
	cards[8] = 142;
	cards[9] = PHOENIX;
	cards[10] = 123;
	cards[11] = 132;
	cards[12] = 140;
	cards[13] = PHOENIX;
	*/
	sort_cards(cards, n);
	print_cards(cards, n);
	//init_trickset(&trickset);
	//set_trick(&trick, STRAIGHT, 5, 5, 11, 7, 0, cards);
	//get_value(card), get_value(card), 0, &card);
	make_singles(&trickset, NULL, cards, n);
	make_doubles(&trickset, NULL, cards, n);
	make_triples(&trickset, NULL, cards, n);
	make_quads(&trickset, NULL, cards, n);
	//print_trickset(&trickset);
	//make_singles(&trickset, &trick, cards, n);
	//print_trickset(&trickset);
	//make_straights(&trickset, &trick, cards, n);
	print_trickset(&trickset);


	return 0;
}

int rand_hand(Card cards[], int num_cards)
{
	Card deck[56];
	int n_rem, pos, i, j, n;

	srand(time(NULL));

	for (i = 0; i < 56; i++)
		deck[i] = i;

	n_rem = 56;
	n = 0;
	for (i = 0; i < num_cards; i++) {
		/* Randomly choose an unshuffled card. Then add it to the
		 * shuffled array. Shift the unshuffled cards down.
		 */
		pos = rand() % n_rem;
		add_card(cards, &n, CARDS[deck[pos]]);
		for (j = pos + 1; j < n_rem; j++)
			deck[j - 1] = deck[j];
		n_rem--;
	}

	return 0;
}
