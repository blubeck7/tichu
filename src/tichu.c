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

	printf("Welcome to Tichu!\n");

	srand((unsigned) time(NULL));
	rand_hand(cards);
	sort_cards(cards, 14);

	init_card_count(&card_count);
	count_cards(cards, 14, &card_count);
	print_card_count(&card_count);

	//Testing the code to generate hands
	gen_hands(&card_count, &hand_space, NULL);
	print_hands(&hand_space);

	/*int nums[] = {1,2,4,1,2,3};*/
	/*int n, m;*/
	/*int *seqs;*/
	/*int i, j;*/

	/*n = (int) sizeof(nums) / sizeof(int);*/
	/*m = 1;*/
	/*for (i = 0; i < n; i++)*/
		/*m *= nums[i];*/
	/*seqs = malloc(sizeof(int) * m);*/
	/*make_seqs((int) sizeof(nums) / sizeof(int), nums, seqs); */

	/*for (i = 0; i < m; i++) {*/
		/*printf("%d: ", i);*/
		/*for(j = 0; j < n; j++)*/
			/*printf("%d", *(seqs + i*n + j));*/
		/*printf("\n");*/
	/*}*/
/*	
	cards[0] = CARDS[0]; //Dog 
	cards[1] = CARDS[6]; //6c
	cards[2] = CARDS[9]; //7c
	cards[3] = CARDS[11]; //Jc
	cards[4] = CARDS[22]; //9d
	cards[5] = CARDS[24]; //Jd
	cards[6] = CARDS[26]; //Kd
	cards[7] = CARDS[37]; //Jh
	cards[8] = CARDS[38]; //Qh
	cards[9] = CARDS[39]; //Kh
	cards[10] = CARDS[48]; //10s
	cards[11] = CARDS[50]; //Js
	cards[12] = CARDS[53]; //As
	cards[13] = CARDS[14]; //Dragon
	*/

	/*
	init_card_count(&card_count);
	print_card_count(&card_count);
	cards[7] = CARDS[37]; //Jh
	count_cards(cards, 14, &card_count);
	print_card_count(&card_count);
	*/

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
