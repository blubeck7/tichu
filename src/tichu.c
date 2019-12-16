#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/card.h"
#include "../inc/hand.h"

int rand_hand(Card cards[14]);

int main(int argc, char *argv[])
{
	// Random testing of card counts
	Card cards[14];
	Card_Count card_count;
	Hand_Space hand_space;
	Hand lead_hand;
	int i;

	printf("Welcome to Tichu!\n");

	srand((unsigned) time(NULL));
	rand_hand(cards);
	sort_cards(cards, 14);

	init_card_count(&card_count);
	count_cards(cards, 14, &card_count);
	print_card_count(&card_count);

	init_hand_space(&hand_space);
	// Testing the code to generate hands
	// Case 1: no lead hand, no phoenix
	gen_hands(&card_count, &hand_space, NULL);
	printf("No lead, No Phoenix\n");
	print_hands(&hand_space);

	// Case 2: lead hand, no phoenix
	lead_hand.type = SINGLE;
	lead_hand.length = 1;
	lead_hand.high = 10;
	lead_hand.low = 10;
	lead_hand.cards[0] = 102;
	gen_hands(&card_count, &hand_space, &lead_hand);
	printf("Single Lead ");
	print_card(lead_hand.cards[0]);
	printf(", No Phoenix\n");
	print_hands(&hand_space);

	lead_hand.type = DOUBLE;
	lead_hand.length = 2;
	lead_hand.high = 4;
	lead_hand.low = 4;
	lead_hand.cards[0] = 91;
	lead_hand.cards[1] = 94;
	gen_hands(&card_count, &hand_space, &lead_hand);
	printf("Double Lead ");
	for (i = 0; i < 2; i++)
		print_card(lead_hand.cards[i]);
	printf(", No Phoenix\n");
	print_hands(&hand_space);

	lead_hand.type = TRIPLE;
	lead_hand.length = 3;
	lead_hand.high = 8;
	lead_hand.low = 8;
	lead_hand.cards[0] = 81;
	lead_hand.cards[1] = 82;
	lead_hand.cards[2] = 84;
	gen_hands(&card_count, &hand_space, &lead_hand);
	printf("Triple Lead ");
	for (i = 0; i < 3; i++)
		print_card(lead_hand.cards[i]);
	printf(", No Phoenix\n");
	print_hands(&hand_space);

	lead_hand.type = FULL;
	lead_hand.length = 5;
	lead_hand.high = 6;
	lead_hand.low = 3;
	lead_hand.cards[0] = 61;
	lead_hand.cards[1] = 62;
	lead_hand.cards[2] = 64;
	lead_hand.cards[3] = 22;
	lead_hand.cards[4] = 23;
	gen_hands(&card_count, &hand_space, &lead_hand);
	printf("Full Lead ");
	for (i = 0; i < lead_hand.length; i++)
		print_card(lead_hand.cards[i]);
	printf(", No Phoenix\n");
	print_hands(&hand_space);

	lead_hand.type = STRAIGHT;
	lead_hand.length = 5;
	lead_hand.high = 9;
	lead_hand.low = 5;
	lead_hand.cards[0] = 51;
	lead_hand.cards[1] = 62;
	lead_hand.cards[2] = 74;
	lead_hand.cards[3] = 82;
	lead_hand.cards[4] = 93;
	gen_hands(&card_count, &hand_space, &lead_hand);
	printf("Straight Lead ");
	for (i = 0; i < lead_hand.length; i++)
		print_card(lead_hand.cards[i]);
	printf(", No Phoenix\n");
	print_hands(&hand_space);

	lead_hand.type = DSTRAIGHT;
	lead_hand.length = 4;
	lead_hand.high = 6;
	lead_hand.low = 5;
	lead_hand.cards[0] = 51;
	lead_hand.cards[1] = 52;
	lead_hand.cards[2] = 62;
	lead_hand.cards[3] = 64;
	gen_hands(&card_count, &hand_space, &lead_hand);
	printf("DStraight Lead ");
	for (i = 0; i < lead_hand.length; i++)
		print_card(lead_hand.cards[i]);
	printf(", No Phoenix\n");
	print_hands(&hand_space);

	cards[0] = 62; 
	cards[1] = 72;
	cards[2] = 82;
	cards[3] = 92;
	cards[4] = 102;
	cards[5] = 112;
	cards[6] = 122;
	cards[7] = 104;
	cards[8] = 10;
	cards[9] = 101;
	cards[10] = 103;
	cards[11] = 91;
	cards[12] = 93;
	cards[13] = 143;
	init_card_count(&card_count);
	count_cards(cards, 14, &card_count);
	print_card_count(&card_count);

	lead_hand.type = BOMB;
	lead_hand.length = 4;
	lead_hand.high = 9;
	lead_hand.low = 9;
	lead_hand.cards[0] = 91;
	lead_hand.cards[1] = 92;
	lead_hand.cards[2] = 93;
	lead_hand.cards[3] = 94;
	gen_hands(&card_count, &hand_space, &lead_hand);
	printf("Bomb Lead ");
	for (i = 0; i < lead_hand.length; i++)
		print_card(lead_hand.cards[i]);
	printf(", No Phoenix\n");
	print_hands(&hand_space);

	return 0;
}

int rand_hand(Card cards[14])
{
	Card deck[56];
	int n_rem, pos, i, j;

	for (i = 0; i < 56; i++)
		deck[i] = i;

	n_rem = 56;
	for (i = 0; i < 14; i++) {
		/* Randomly choose an unshuffled card. Then add it to the
		 * shuffled array. Shift the unshuffled cards down.
		 */
		pos = rand() % n_rem;
		cards[i] = CARDS[deck[pos]];
		for (j = pos + 1; j < n_rem; j++)
			deck[j - 1] = deck[j];
		n_rem--;
	}

	return 0;
}
