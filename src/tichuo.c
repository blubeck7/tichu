#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/cardo.h"
#include "../inc/tricko.h"

int rand_hand(Card cards[]);

int main(int argc, char *argv[])
{
	Card cards[14];
	int n;
	TrickSet trickset;
	//Trick trick;
	//TrickHelper trickhelper;

	n = 14;
	rand_hand(cards);
	sort_cards(cards, n);
	print_cards(cards, n);
	make_straights(&trickset)
	//set_trick(&trick, SINGLE, 1, 1, 16, 16, 0, cards);
	//make_singles(&trickset, &trick, cards, n);
	//print_trickset(&trickset);
	
	//init_trickhelper(&trickhelper);
	//set_trickhelper(&trickhelper, cards, n);
	//print_trickhelper(&trickhelper);




	/*
	sort_cardset();
	print_cardset(&cardset);
	printf("Has dog %d\n", has_dog(&cardset));
	printf("Has one %d\n", has_one(&cardset));
	printf("Has phoenix %d\n", has_phoenix(&cardset));
	printf("Has dragon %d\n", has_dragon(&cardset));
	printf("Has 8c %d\n", has_card(&cardset, 80));
	remove_card(&cardset, PHOENIX);
	remove_card(&cardset, DRAGON);
	remove_card(&cardset, 80);
	remove_card(&cardset, 81);
	print_cardset(&cardset);
	printf("Has dog %d\n", has_dog(&cardset));
	printf("Has one %d\n", has_one(&cardset));
	printf("Has phoenix %d\n", has_phoenix(&cardset));
	printf("Has dragon %d\n", has_dragon(&cardset));
	printf("Has 8c %d\n", has_card(&cardset, 80));
	printf("Count 5's %d\n", count_value(&cardset, 5));
	printf("Count 10's %d\n", count_value(&cardset, 10));
	printf("Count K's %d\n", count_value(&cardset, 13));
*/
	return 0;
}

int rand_hand(Card cards[14])
{
	Card deck[56];
	int n_rem, pos, i, j, n;

	srand(time(NULL));

	for (i = 0; i < 56; i++)
		deck[i] = i;

	n_rem = 56;
	n = 0;
	for (i = 0; i < 14; i++) {
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
