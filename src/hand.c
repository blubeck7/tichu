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
int add_fulls(Card_Count *card_count, int triple, int double_,
	Hand_Space *hand_space);
int gen_hands_no_lead_no_ph(Card_Count *card_count, Hand_Space *hand_space);
int gen_hands_lead_no_ph(Card_Count *card_count, Hand_Space *hand_space,
	Hand *lead_hand);
int gen_hands_no_lead_ph(Card_Count *card_count, Hand_Space *hand_space);
int add_flushes(Card_Count *card_count, int val, int len,
    Hand_Space *hand_space);
int add_triples_ph(Card_Count *card_count, int val, Hand_Space *hand_space);
int add_doubles_ph(Card_Count *card_count, int val, Hand_Space *hand_space);
int make_seqs(int len, int *nums, int *seqs);
int add_straights_ph(Card_Count *card_count, int val, int len,
    Hand_Space *hand_space);
int add_dstraights_ph(Card_Count *card_count, int val, int len, int cnt,
    Hand_Space *hand_space);


int init_hand_space(Hand_Space *hand_space)
{
	hand_space->num_hands = 0;

	return 0;
}

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
    
	init_hand_space(hand_space);
    has_ph = card_count->counts_s[get_value(PHOENIX)];
    
    if (!lead_hand && !has_ph)
        gen_hands_no_lead_no_ph(card_count, hand_space);
    else if (lead_hand && !has_ph)
        gen_hands_lead_no_ph(card_count, hand_space, lead_hand);
    else if (!lead_hand && has_ph)
        gen_hands_no_lead_ph(card_count, hand_space);
    else
        ;

    return 0;
}

int gen_hands_no_lead_ph(Card_Count *card_count, Hand_Space *hand_space)
{
    int i, count, j, k, sum;

    for (i = 0; i < NUM_VALUES; i++) {
        count = card_count->counts_s[i];
        switch (count) {
        case 4:
            add_quad(card_count, i, hand_space);
            add_triples_ph(card_count, i, hand_space);
            add_doubles_ph(card_count, i, hand_space);
            add_singles(card_count, i, hand_space);
			break;
        case 3:
            add_triples_ph(card_count, i, hand_space);
            add_doubles_ph(card_count, i, hand_space);
            add_singles(card_count, i, hand_space);
            break;
        case 2:
            add_triples_ph(card_count, i, hand_space);
            add_doubles_ph(card_count, i, hand_space);
            add_singles(card_count, i, hand_space);
            break;
		case 1:
			if (i > 1 && i < 15)
            	add_doubles_ph(card_count, i, hand_space);
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
            if (sum >= i - 1)
                add_straights_ph(card_count, j, i, hand_space);
        }
    }

	// double straights
	for (i = 2; i < (card_count->num_cards / 2) + 1; i++) { //len
		for (j = 2; j < 15 - i + 1; j++) { //low val
            sum = 0;
            for (k = 0; k < i; k++) {
				if (card_count->two_flags[j + k] == 0)
					sum += card_count->one_flags[j + k];
				else
                	sum += 2*card_count->two_flags[j + k];
            }
            if (sum >= 2*i - 1) {
                add_dstraights_ph(card_count, j, i, sum, hand_space);
            }
        }		
	}

	// full houses
/*
	for (i = 0; i < NUM_VALUES; i++) {
		for (j = 0; j < NUM_VALUES; j++) {
			if (i != j && card_count->counts_t[i] > 0 &&
				card_count->counts_d[j] > 0)
				add_fulls(card_count, i, j, hand_space);
		}
	}
*/
    return 0;
}

int add_dstraights_ph(Card_Count *card_count, int val, int len, int cnt,
    Hand_Space *hand_space)
{
	int i, j, k, n;
    int nums[MAX_HAND];
    int *strs, num_strs;

	if (cnt == 2 * len - 1) {
		// The phoenix is needed
		ph_pos = 0;
    	for (i = 0; i < len; i++) {
			if (!card_count->two_flags[i + val]) {
				ph_pos = i;
				break;
			}
		}

    	num_strs = 1;
    	for (i = 0; i < len; i++) {
        	nums[i] = card_count->counts_d[i + val];
			if (i == ph_pos)
				nums[i]++;
        	num_strs *= nums[i];
    	}
    	strs = malloc(sizeof(int) * len * num_strs);
		make_seqs(len, nums, strs);

    	for (i = 0; i < num_strs; i++) {
        	n = hand_space->num_hands++;
			hand_space->hands[n].type = DSTRAIGHT;     
        	hand_space->hands[n].length = len * 2; 
        	hand_space->hands[n].high = val + len - 1;
			hand_space->hands[n].low = val;
    		hand_space->hands[n].has_ph = 1;
    		for (j = 0; j < len; j++) {
    			k = *(strs + i * len + j);
    			hand_space->hands[n].cards[2*j] =
				card_count->doubles[j+val][k][0];
				hand_space->hands[n].cards[2*j+1] =
				card_count->doubles[j+val][k][1];
		}
	}

	free(strs);






    	for (k = 0; k < num_strs; k++) {
        	n = hand_space->num_hands++;
        	hand_space->hands[n].length = len;
        	hand_space->hands[n].high = val + len - 1;
			hand_space->hands[n].low = val;
    		hand_space->hands[n].has_ph = 1;
    		for (h = 0; h < len; h++) {
    			m = *(strs + k * len + h);
				if (h == ph_pos) // phoenix
    				hand_space->hands[n].cards[h] = PHOENIX;
				else 
    				hand_space->hands[n].cards[h] =
					card_count->singles[h + val][m];
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

		}
		free(strs);
		

		


	return 0;	
}

int add_straights_ph(Card_Count *card_count, int val, int len,
    Hand_Space *hand_space)
{
    int i, j, k, n, h, m, flush, all, ph_pos;
    int nums[MAX_HAND];
    int *strs, num_strs;

	// Get regular card counts
    for (i = 0; i < len; i++)
        nums[i] = card_count->counts_s[i + val];

	// Is the phoenix needed and if so where?
	all = 1;
	ph_pos = 0;
    for (i = 0; i < len; i++) {
		if (nums[i] == 0) {
			all = 0;
			ph_pos = i;
			break;
		}
	}

	if (all) {
		/* Phoenix is an extra card. Call add_straight to get regular
		 * straights. Then loop through each position with the phoenix as the
		 * only card in that position and the remaining cards in the other
		 * positions.
		 */
		add_straights(card_count, val, len, hand_space);
		// straights with the phoenix in each position
    	for (i = 0; i < len; i++) {
    		num_strs = 1;
			for (j = 0; j < len; j++) {
				if (i == j)
					nums[j] = 1;
				else	
        			nums[j] = card_count->counts_s[j + val];
				num_strs *= nums[j];
			}

    		strs = malloc(sizeof(int) * len * num_strs);
			make_seqs(len, nums, strs);
    
    		// add the straights to the hand space
    		for (k = 0; k < num_strs; k++) {
        		n = hand_space->num_hands++;
        		hand_space->hands[n].length = len;
        		hand_space->hands[n].high = val + len - 1;
				hand_space->hands[n].low = val;
    			for (h = 0; h < len; h++) {
    				m = *(strs + k * len + h);
					if (h == i) { // phoenix
    					hand_space->hands[n].has_ph = 1;
    					hand_space->hands[n].cards[h] = PHOENIX;
					} else 
    					hand_space->hands[n].cards[h] =
						card_count->singles[h + val][m];
				}
			}
			free(strs);
    	}
	} else {
		// phoenix fills in a specific missing card
    	num_strs = 1;
		for (j = 0; j < len; j++) {
			if (ph_pos == j)
				nums[j] = 1;
			num_strs = num_strs * nums[j];
		}
    	strs = malloc(sizeof(int) * len * num_strs);
		make_seqs(len, nums, strs);

    	for (k = 0; k < num_strs; k++) {
        	n = hand_space->num_hands++;
        	hand_space->hands[n].length = len;
        	hand_space->hands[n].high = val + len - 1;
			hand_space->hands[n].low = val;
    		hand_space->hands[n].has_ph = 1;
    		for (h = 0; h < len; h++) {
    			m = *(strs + k * len + h);
				if (h == ph_pos) // phoenix
    				hand_space->hands[n].cards[h] = PHOENIX;
				else 
    				hand_space->hands[n].cards[h] =
					card_count->singles[h + val][m];
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

		}
		free(strs);
	}
    return 0;
}

int add_triples_ph(Card_Count *card_count, int val, Hand_Space *hand_space)
{
	int j;  
	// at least two regular cards plus the phoenix
	switch (card_count->counts_s[val]) {
	case 2:
		// 3 choose 3 is 1
		// 1st combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][1];
		hand_space->hands[j].cards[2] = PHOENIX;

		break;
	case 3:
		// 4 choose 3 is 4
		// 1st combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][1];
		hand_space->hands[j].cards[2] = card_count->singles[val][2];

		// 2nd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][1];
		hand_space->hands[j].cards[2] = PHOENIX;

		// 3rd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][2];
		hand_space->hands[j].cards[2] = PHOENIX;

		// 4th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][1];
		hand_space->hands[j].cards[1] = card_count->singles[val][2];
		hand_space->hands[j].cards[2] = PHOENIX;

		break;

	case 4:
		// 5 choose 3 is 10
		// 1st combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][1];
		hand_space->hands[j].cards[2] = card_count->singles[val][2];

		// 2nd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][1];
		hand_space->hands[j].cards[2] = card_count->singles[val][3];

		// 3rd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][2];
		hand_space->hands[j].cards[2] = card_count->singles[val][3];

		// 4th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][1];
		hand_space->hands[j].cards[1] = card_count->singles[val][2];
		hand_space->hands[j].cards[2] = card_count->singles[val][3];

		// 5th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][0];
		hand_space->hands[j].cards[2] = card_count->singles[val][1];

		// 6th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][0];
		hand_space->hands[j].cards[2] = card_count->singles[val][2];

		// 7th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][0];
		hand_space->hands[j].cards[2] = card_count->singles[val][3];

		// 8th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][1];
		hand_space->hands[j].cards[2] = card_count->singles[val][2];

		// 9th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][1];
		hand_space->hands[j].cards[2] = card_count->singles[val][3];

		// 10th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = TRIPLE;
		hand_space->hands[j].length = 3;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][2];
		hand_space->hands[j].cards[2] = card_count->singles[val][3];

		break;

	default:
		break;
	}

    return 0;
}   

int add_doubles_ph(Card_Count *card_count, int val, Hand_Space *hand_space)
{
	int j;  
	// at least one regular card plus the phoenix
	switch (card_count->counts_s[val]) {
	case 1:
		// 2 choose 2 is 1
		// 1st combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = PHOENIX;

		break;
	case 2:
		// 3 choose 2 is 3
		// 1st combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][1];

		// 2nd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = PHOENIX;

		// 3rd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][1];
		hand_space->hands[j].cards[1] = PHOENIX;

		break;

	case 3:
		// 4 choose 2 is 6
		// 1st combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][1];

		// 2nd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][2];

		// 3rd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][1];
		hand_space->hands[j].cards[1] = card_count->singles[val][2];

		// 4th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = PHOENIX;

		// 5th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][1];
		hand_space->hands[j].cards[1] = PHOENIX;

		// 6th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = card_count->singles[val][2];
		hand_space->hands[j].cards[1] = PHOENIX;

		break;

	case 4:
		// 5 choose 2 is 10
		// 1st combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][1];

		// 2nd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][2];

		// 3rd combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][0];
		hand_space->hands[j].cards[1] = card_count->singles[val][3];

		// 4th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][1];
		hand_space->hands[j].cards[1] = card_count->singles[val][2];

		// 5th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][1];
		hand_space->hands[j].cards[1] = card_count->singles[val][3];

		// 6th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 0;
		hand_space->hands[j].cards[0] = card_count->singles[val][2];
		hand_space->hands[j].cards[1] = card_count->singles[val][3];

		// 7th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][0];

		// 8th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][1];

		// 9th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][2];

		// 10th combination
		j = hand_space->num_hands++;
		hand_space->hands[j].type = DOUBLE;
		hand_space->hands[j].length = 2;
		hand_space->hands[j].high = hand_space->hands[j].low = val;
		hand_space->hands[j].has_ph = 1;
		hand_space->hands[j].cards[0] = PHOENIX; 
		hand_space->hands[j].cards[1] = card_count->singles[val][3];

		break;

	default:
		break;
	}

    return 0;
}   

int gen_hands_lead_no_ph(Card_Count *card_count, Hand_Space *hand_space,
	Hand *lead_hand)
{
    int i, j, sum;

	switch (lead_hand->type) {
	case SINGLE:
    	for (i = lead_hand->high + 1; i < NUM_VALUES; i++)
            add_singles(card_count, i, hand_space);
		break;
	case DOUBLE:
    	for (i = lead_hand->high + 1; i < NUM_VALUES; i++)
        	if (card_count->counts_s[i] > 1)
            	add_doubles(card_count, i, hand_space);
		break;
	case TRIPLE:
    	for (i = lead_hand->high + 1; i < NUM_VALUES; i++)
        	if (card_count->counts_s[i] > 2)
            	add_triples(card_count, i, hand_space);
		break;
	case FULL:
		for (i = 0; i < NUM_VALUES; i++) {
			for (j = 0; j < NUM_VALUES; j++) {
				if (i != j &&
					card_count->counts_t[i] > 0 &&
					card_count->counts_d[j] > 0 &&
					((i >= lead_hand->high && j > lead_hand->low) ||
					 (i > lead_hand->high)))
					add_fulls(card_count, i, j, hand_space);
			}
		}
		break;
	case STRAIGHT:
		if (card_count->num_cards < lead_hand->length)
			break;

		for (i = lead_hand->low + 1; i < 15 - lead_hand->length + 1; i++) {
			sum = 0;
            for (j = 0; j < lead_hand->length; j++) {
				sum += card_count->one_flags[i + j];
            }
            if (sum == lead_hand->length) {
                add_straights(card_count, i, lead_hand->length, hand_space);
            }
        }
		break;
	case DSTRAIGHT:
		if (card_count->num_cards < lead_hand->length)
			break;

		for (i = lead_hand->low + 1; i < 15 - lead_hand->length / 2 + 1; i++) {
			sum = 0;
            for (j = 0; j < lead_hand->length / 2; j++) {
				sum += card_count->two_flags[i + j];
            }
            if (sum == lead_hand->length / 2)
				add_dstraights(card_count, i, lead_hand->length / 2, hand_space);
        }
		break;
	case BOMB:
		if (card_count->num_cards < lead_hand->length)
			break;
		// quad bomb	
		if (lead_hand->length == 4) {
    		for (i = lead_hand->high + 1; i < NUM_VALUES; i++)
				if (card_count->counts_s[i] == 4)
            		add_quad(card_count, i, hand_space);
		} else { //straight flush
			for (i = lead_hand->low + 1; i < 15 - lead_hand->length + 1; i++) {
				sum = 0;
            	for (j = 0; j < lead_hand->length; j++) {
					sum += card_count->one_flags[i + j];
            	}
            	if (sum == lead_hand->length) {
                	add_flushes(card_count, i, lead_hand->length, hand_space);
            	}
        	}
		}

		break;
	}

	return 0;
}

int add_flushes(Card_Count *card_count, int val, int len,
    Hand_Space *hand_space)
{
    int i, j, k, n, flush;
    int nums[MAX_HAND];
    int *strs, num_strs;
	Hand temp_hand;

	init_hand(&temp_hand);

    num_strs = 1;
    for (i = 0; i < len; i++) {
        nums[i] = card_count->counts_s[i + val];
        num_strs *= nums[i];
    }

	//printf("num_strs=%d\n", num_strs);
    strs = malloc(sizeof(int) * len * num_strs);
	make_seqs(len, nums, strs);
    
    for (i = 0; i < num_strs; i++) {
        temp_hand.length = len;
        temp_hand.high = val + len - 1;
		temp_hand.low = val;
    	for (j = 0; j < len; j++) {
    		k = *(strs + i * len + j);
    		temp_hand.cards[j] = card_count->singles[j + val][k];

		}

		flush = 1;
		for (j = 1; j < len; j++) {
			if (get_suit(temp_hand.cards[j]) !=
				get_suit(temp_hand.cards[j - 1])) {
				flush = 0;
				break;
			}
		}
		if (flush) {
        	n = hand_space->num_hands++;
        	hand_space->hands[n].type = BOMB;
        	hand_space->hands[n].length = temp_hand.length;
        	hand_space->hands[n].high = temp_hand.high;
        	hand_space->hands[n].low = temp_hand.low;
			for (i = 0; i < temp_hand.length; i++)
        		hand_space->hands[n].cards[i] = temp_hand.cards[i];
    	}
	}

	free(strs);

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
				add_fulls(card_count, i, j, hand_space);
		}
	}

    return 0;
}

int add_fulls(Card_Count *card_count, int triple, int double_,
	Hand_Space *hand_space)
{
	int i, j, k, m, n, *seqs, nums[2];

	m = nums[0] = card_count->counts_t[triple];
	n = nums[1] = card_count->counts_d[double_];

    seqs = malloc(sizeof(int) * m * n * 2);
	make_seqs(2, nums, seqs);

    for (i = 0; i < m * n; i++) {
        k = hand_space->num_hands++;
		hand_space->hands[k].type = FULL;
        hand_space->hands[k].length = 5; 
        hand_space->hands[k].high = triple;
		hand_space->hands[k].low = double_;
    	j = *(seqs + i * 2);
    	hand_space->hands[k].cards[0] = card_count->triples[triple][j][0];
    	hand_space->hands[k].cards[1] = card_count->triples[triple][j][1];
    	hand_space->hands[k].cards[2] = card_count->triples[triple][j][2];
    	j = *(seqs + i * 2 + 1);
    	hand_space->hands[k].cards[3] = card_count->doubles[double_][j][0];
    	hand_space->hands[k].cards[4] = card_count->doubles[double_][j][1];
	}

	free(seqs);

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
        hand_space->hands[n].high = val + len - 1;
		hand_space->hands[n].low = val;
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

	free(strs);

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
        hand_space->hands[n].high = val + len - 1;
		hand_space->hands[n].low = val;
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
		if (card == PHOENIX)
			hand_space->hands[j].has_ph = 1;
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
	hand_space->hands[i].high = val;
	hand_space->hands[i].low = val;
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

	printf("type=");
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

	printf("len=%d high=%d low=%d has_ph=%d ",
			hand->length, hand->high, hand->low, hand->has_ph);

	printf("cards=");
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

int init_hand(Hand *hand)
{
	int i;

	hand->type = NONE;
	hand->length = 0;
	hand->high = 0;
	hand->low = 0;
	hand->has_ph = 0;
	for (i = 0; i < MAX_HAND; i++)
		hand->cards[i] = 0;

	return 0;
}

