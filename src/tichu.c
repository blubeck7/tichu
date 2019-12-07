#include <stdio.h>
#include "../inc/card.h"


int main(int argc, char *argv[])
{
	Card cards[14];
	Card_Count card_count;

	printf("Welcome to Tichu!\n");
	init_card_count(&card_count);
	print_card_count(&card_count);

	cards[0] = CARDS[0]; //Dog 
	cards[1] = CARDS[6]; //6c
	cards[2] = CARDS[7]; //7c
	cards[3] = CARDS[11]; //Jc
	cards[4] = CARDS[22]; //9d
	cards[5] = CARDS[24]; //Jd
	cards[6] = CARDS[26]; //Kd
	cards[7] = CARDS[31]; //5h
	cards[8] = CARDS[38]; //Qs
	cards[9] = CARDS[39]; //Kh
	cards[10] = CARDS[49]; //10s
	cards[11] = CARDS[50]; //Js
	cards[12] = CARDS[53]; //As
	cards[13] = CARDS[55]; //Phoenix
	count_cards(cards, 14, &card_count);
	print_card_count(&card_count);

	return 0;
}
