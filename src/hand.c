#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/card.h"
#include "../inc/hand.h"


Card doubles[NUM_RVALUES][6][2];

int gen_hands_no_lead_no_ph(Card_Count *card_count, Hand_Space *hand_space);
int add_quad(Card_Count *card_count, int p, int c, Hand_Space *hand_space);
int add_triples(Card_Count *card_count, int p, int c, Hand_Space *hand_space);
int add_doubles(Card_Count *card_count, int p, int c, Hand_Space *hand_space);
int add_singles(Card_Count *card_count, int p, int c, Hand_Space *hand_space);


int gen_hands(Card_Count *card_count, Hand_Space *hand_space, Hand *lead_hand)
{
    /*
    There are four cases:
        Case 1: There is not a lead hand and the player does not have the phoenix.
        Case 2: There is a lead hand and the player does not have the phoenix.
        Case 3: There is not lead hand but the player has the phoenix.
        Case 4: There is a lead hand and the player has the phoenix.
    */

    int has_ph;
    
    has_ph = card_count->counts_s[get_value(PHOENIX)];
    
    if (!lead_hand && !has_ph)
        gen_hands_no_lead_no_ph(card_count, hand_space);
    else if (lead_hand && !has_ph)
        ;
    else if (!lead_hand && has_ph)
        ;
    else
        ;

    return 0;
}

int gen_hands_no_lead_no_ph(Card_Count *card_count, Hand_Space *hand_space)
{
    int i, count;

    for (i = 0; i < NUM_VALUES; i++) {
        count = card_count->counts_s[i];
        switch (count) {
        case 4:
            add_quad(card_count, i, count, hand_space);
            add_triples(card_count, i, count, hand_space);
            add_doubles(card_count, i, count, hand_space);
            add_singles(card_count, i, count, hand_space);
			break;
        case 3:
            add_triples(card_count, i, count, hand_space);
            add_doubles(card_count, i, count, hand_space);
            add_singles(card_count, i, count, hand_space);
            break;
        case 2:
            add_doubles(card_count, i, count, hand_space);
            add_singles(card_count, i, count, hand_space);
            break;
		default:
            add_singles(card_count, i, count, hand_space);
            break;
        }    
    }

    return 0;
}

int add_singles(Card_Count *card_count, int p, int c, Hand_Space *hand_space)
{
	int i, j, value;
	Card card;

	for (i = 0; i < c; i++) {
		j = hand_space->num_hands++;
		hand_space->hands[j].type = SINGLE;
		hand_space->hands[j].length = 1;
		card = card_count->singles[p][i];
		value = get_value(card_count->singles[p][i]);
		hand_space->hands[j].high = value;
		hand_space->hands[j].low = value;
		hand_space->hands[j].cards[0] = card;
	}

    return 0;
}   

int add_doubles(Card_Count *card_count, int p, int c, Hand_Space *hand_space)
{
	int i, j;

	for (i = 0; i < c; i++) {
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = card_count->doubles[p][i][0];
		hand_space->hands[j].low = card_count->doubles[p][i][0];
		hand_space->hands[j].cards[0] = card_count->doubles[p][i][0];
		hand_space->hands[j].cards[1] = card_count->doubles[p][i][1];
	}

    return 0;
}   

int add_triples(Card_Count *card_count, int p, int c, Hand_Space *hand_space)
{
	int i, j;

	for (i = 0; i < c; i++) {
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = card_count->triples[p][i][0];
		hand_space->hands[j].low = card_count->triples[p][i][0];
		hand_space->hands[j].cards[0] = card_count->triples[p][i][0];
		hand_space->hands[j].cards[1] = card_count->triples[p][i][1];
		hand_space->hands[j].cards[2] = card_count->triples[p][i][2];
	}

    return 0;
}   

int add_quad(Card_Count *card_count, int p, int c, Hand_Space *hand_space)
{
    /* Create the quad bomb and then add it to the hand space */
	int i;

	i = hand_space->num_hands++;
	hand_space->hands[i].type = BOMB;
	hand_space->hands[i].length = 4;
	hand_space->hands[i].high = card_count->singles[p][0];
	hand_space->hands[i].low = card_count->singles[p][0];
	hand_space->hands[i].cards[0] = card_count->singles[p][0];
	hand_space->hands[i].cards[1] = card_count->singles[p][1];
	hand_space->hands[i].cards[2] = card_count->singles[p][2];
	hand_space->hands[i].cards[3] = card_count->singles[p][3];

    return 0;
}   

int print_hands(Hand_Space *hand_space)
{
	int i;

	printf("Hand Space:\n");
	printf("Number of Hands: %d\n", hand_space->num_hands);

	for (i = 0; i < hand_space->num_hands; i++) {
		printf("%d: ", i);
		print_hand(hand_space->hands + i);
	}
		
	return 0;
}

int print_hand(Hand *hand)
{
	int i;

	switch(hand->type) {
	case SINGLE:
		printf("single ");
		break;
	case DOUBLE:
		printf("double ");
		break;
	case TRIPLE:
		printf("triple ");
		break;
	case FULL:
		printf("full ");
		break;
	case STRAIGHT:
		printf("straight ");
		break;
	case BOMB:
		printf("bomb ");
		break;
	default:
		break;
	}
	printf("len=%d high=%d low=%d ", hand->length, hand->high, hand->low);

	for (i = 0; i < hand->length; i++)
		print_card(hand->cards[i]);

	printf("\n");

	return 0;
}
