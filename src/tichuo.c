#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/cardo.h"

int rand_hand(CardSet *cardset);

int main(int argc, char *argv[])
{
	CardSet cardset;

	init_cardset(&cardset);
	rand_hand(&cardset);
	sort_cardset(&cardset);
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

	return 0;
}

int rand_hand(CardSet *cardset)
{
	Card deck[56];
	int n_rem, pos, i, j;

	srand(time(NULL));

	for (i = 0; i < 56; i++)
		deck[i] = i;

	n_rem = 56;
	for (i = 0; i < 14; i++) {
		/* Randomly choose an unshuffled card. Then add it to the
		 * shuffled array. Shift the unshuffled cards down.
		 */
		pos = rand() % n_rem;
		add_card(cardset, CARDS[deck[pos]]);
		for (j = pos + 1; j < n_rem; j++)
			deck[j - 1] = deck[j];
		n_rem--;
	}

	return 0;
}
