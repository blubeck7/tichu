#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/card.h"
#include "../inc/hand.h"


int gen_hands_no_lead_no_ph(Card_Count *card_count, Hand_Space *hand_space);
int add_quad(Card_Count *card_count, int val, Hand_Space *hand_space);
int add_triples(Card_Count *card_count, int val, Hand_Space *hand_space);
int add_doubles(Card_Count *card_count, int val, Hand_Space *hand_space);
int add_singles(Card_Count *card_count, int val, Hand_Space *hand_space);
int add_straights(Card_Count *card_count, int val, int len,
    Hand_Space *hand_space);
int add_dstraights(Card_Count *card_count, int val, int len,
    Hand_Space *hand_space);


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
    int i, j, k, sum, count;

    for (i = 0; i < NUM_VALUES; i++) {
        count = card_count->counts_s[i];
        switch (count) {
        case 4:
            add_quad(card_count, i, hand_space);
            add_triples(card_count, i, hand_space);
            add_doubles(card_count, i, hand_space);
            add_singles(card_count, i, hand_space);
			break;
        case 3:
            add_triples(card_count, i, hand_space);
            add_doubles(card_count, i, hand_space);
            add_singles(card_count, i, hand_space);
            break;
        case 2:
            add_doubles(card_count, i, hand_space);
            add_singles(card_count, i, hand_space);
            break;
		default:
            add_singles(card_count, i, hand_space);
            break;
        }
    }

    // straights and straight flushes
    for (i = 5; i < card_count->num_cards + 1; i++) {
        for (j = 1; j < 15 - i + 1; j++) {
            sum = 0;
            for (k = 0; k < i; k++) {
                sum += card_count->one_flags[j + k];
            }
            if (sum == i) {
                add_straights(card_count, j, i, hand_space);
            }
        }
    }

	// double straights
	for (i = 2; i < (card_count->num_cards / 2) + 1; i++) { //len
		for (j = 2; j < 15 - i + 1; j++) { //low val
            sum = 0;
            for (k = 0; k < i; k++) {
                sum += card_count->two_flags[j + k];
            }
            if (sum == i) {
                add_dstraights(card_count, j, i, hand_space);
            }
        }		
	}

	// full houses
	for (i = 0; i < NUM_VALUES; i++) {
		for (j = 0; j < NUM_VALUES; j++) {
			if (i != j && card_count->counts_t[i] > 0 &&
			card_count->counts_d[j] > 0)
		}
	}

    return 0;
}

int add_dstraights(Card_Count *card_count, int val, int len,
    Hand_Space *hand_space)
{
	int i, j, k, n;
    int nums[MAX_HAND];
    int *strs, num_strs;

    num_strs = 1;
    for (i = 0; i < len; i++) {
        nums[i] = card_count->counts_d[i + val];
        num_strs *= nums[i];
    }

    strs = malloc(sizeof(int) * len * num_strs);
	make_seqs(len, nums, strs);

    for (i = 0; i < num_strs; i++) {
        n = hand_space->num_hands++;
		hand_space->hands[n].type = DSTRAIGHT;     
        hand_space->hands[n].length = len * 2; 
        hand_space->hands[n].high = val + len - 1;                        hand_space->hands[n].low = val;
		//printf("Seq: %d ",i);
    	for (j = 0; j < len; j++) {
    		k = *(strs + i * len + j);
			//printf("%d", k);
    		hand_space->hands[n].cards[2*j] =
				card_count->doubles[j+val][k][0];
			hand_space->hands[n].cards[2*j+1] =
				card_count->doubles[j+val][k][1];
		}
	}

	return 0;	
}

int add_straights(Card_Count *card_count, int val, int len,
    Hand_Space *hand_space)
{
    int i, j, k, n, flush;
    int nums[MAX_HAND];
    int *strs, num_strs;

    num_strs = 1;
    for (i = 0; i < len; i++) {
        nums[i] = card_count->counts_s[i + val];
        num_strs *= nums[i];
    }

	//printf("num_strs=%d\n", num_strs);
    strs = malloc(sizeof(int) * len * num_strs);
	make_seqs(len, nums, strs);
    
    // add the straights to the hand space
	//printf("Number of Strings: %d\n", num_strs);
	//printf("Length: %d\n", len);
	
    for (i = 0; i < num_strs; i++) {
        n = hand_space->num_hands++;
        hand_space->hands[n].length = len;
        hand_space->hands[n].high = val + len - 1;                        hand_space->hands[n].low = val;
		//printf("Seq: %d ",i);
    	for (j = 0; j < len; j++) {
    		k = *(strs + i * len + j);
			//printf("%d", k);
    		hand_space->hands[n].cards[j] = card_count->singles[j + val][k];

		}

		flush = 1;
		for (j = 1; j < len; j++) {
			if (get_suit(hand_space->hands[n].cards[j]) !=
				get_suit(hand_space->hands[n].cards[j - 1])) {
				flush = 0;
				break;
			}
		}
		if (!flush)
			hand_space->hands[n].type = STRAIGHT;
		else
			hand_space->hands[n].type = BOMB;
		//printf("\n");
    }

	free(strs);

    return 0;
}

int add_singles(Card_Count *card_count, int val, Hand_Space *hand_space)
{
	int i, j, value;
	Card card;

	for (i = 0; i < card_count->counts_s[val]; i++) {
		j = hand_space->num_hands++;
		hand_space->hands[j].type = SINGLE;
		hand_space->hands[j].length = 1;
		card = card_count->singles[val][i];
		value = get_value(card_count->singles[val][i]);
		hand_space->hands[j].high = value;
		hand_space->hands[j].low = value;
		hand_space->hands[j].cards[0] = card;
	}

    return 0;
}   

int add_doubles(Card_Count *card_count, int val, Hand_Space *hand_space)
{
	int i, j, value;

	for (i = 0; i < card_count->counts_d[val]; i++) {
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		value = get_value(card_count->doubles[val][i][0]);
		hand_space->hands[j].high = value;
		hand_space->hands[j].low = value;
		hand_space->hands[j].cards[0] = card_count->doubles[val][i][0];
		hand_space->hands[j].cards[1] = card_count->doubles[val][i][1];
	}

    return 0;
}   

int add_triples(Card_Count *card_count, int val, Hand_Space *hand_space)
{
	int i, j, value;

	for (i = 0; i < card_count->counts_t[val]; i++) {
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		value = get_value(card_count->triples[val][i][0]);
		hand_space->hands[j].high = value;
		hand_space->hands[j].low = value;
		hand_space->hands[j].cards[0] = card_count->triples[val][i][0];
		hand_space->hands[j].cards[1] = card_count->triples[val][i][1];
		hand_space->hands[j].cards[2] = card_count->triples[val][i][2];
	}

    return 0;
}   

int add_quad(Card_Count *card_count, int val, Hand_Space *hand_space)
{
	int i;

	i = hand_space->num_hands++;
	hand_space->hands[i].type = BOMB;
	hand_space->hands[i].length = 4;
	hand_space->hands[i].high = card_count->singles[val][0];
	hand_space->hands[i].low = card_count->singles[val][0];
	hand_space->hands[i].cards[0] = card_count->singles[val][0];
	hand_space->hands[i].cards[1] = card_count->singles[val][1];
	hand_space->hands[i].cards[2] = card_count->singles[val][2];
	hand_space->hands[i].cards[3] = card_count->singles[val][3];

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
	case DSTRAIGHT:
		printf("dstraight ");
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

int make_seqs(int len, int *nums, int *seqs)
{
	int i, j, k, n, m;
	int num_elems, num_reps, num_cycs, num_seqs;

	if (len < 1) {
		seqs = NULL;
		return 0;
	}
//printf("len=%d\n", len);

	num_seqs = *nums;
	for (i = 1; i < len; i++)
		num_seqs *= *(nums + i);

	num_elems = *nums;
	num_cycs = 1;
	num_reps = num_seqs / num_elems;
	for (n = 0; n < len; n++) {
		if (n > 0) {
			num_cycs *= num_elems; 
			num_elems = *(nums + n);
			num_reps = num_reps / num_elems;
		}
//printf("n=%d\n", n);
//printf("num_cyc=%d, num_elem=%d, num_rep=%d\n\n",
//num_cycs, num_elems, num_reps);

		m = 0;
		for (i = 0; i < num_cycs; i++) {
			for (j = 0; j < num_elems; j++) {
				for (k = 0; k < num_reps; k++) {
					*(seqs + m*len + n) = j;
//printf("m=%d, n=%d, cyc=%d, elem=%d, rep=%d\n", m, n, i, j, k);
					m++;
				}
			}
		}
	}	

	return 0;
}