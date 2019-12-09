#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/card.h"
#include "../inc/hand.h"


Card doubles[NUM_RVALUES][6][2];

int gen_hands_no_lead_no_ph(Card_Count *card_count, Hand_Space *hand_space);
int add_quad(Card quad[4], Hand_Space *hand_space);


int gen_hands(Card_Count *card_count, Hand_Space *hand_space, Hand *lead_hand)
{
    /*
    There are four cases:
        Case 1: There is not a lead hand and the player does not have the phoenix.
        Case 2: There is a lead hand and the player does not have the phoenix.
        Case 3: There is not lead hand but the player has the phoenix.
        Case 4: There is a lead hand and the player has the phoenix.
    */

    int has_phoenix;
    
    has_phoenix = card_count->counts[get_value(PHOENIX)];
    
    if (!lead_hand && !has_phoenix)
        gen_hands_no_lead_no_ph(card_count, hand_space);
    else if (lead_hand && !has_phoenix)
        ;
    else if (!lead_hand && has_phoenix)
        ;
    else
        ;

    return 0;
}

int gen_hands_no_lead_no_ph(Card_Count *card_count, Hand_Space *hand_space)
{
    int value, count;

    for (value = 0; value < NUM_VALUES; value++) {
        count = card_count->counts[value];
        switch (count) {
        case 4:
            add_quad(card_count->rcards[value], hand_space);
        case 3:
            break;
        case 2:
            break;
        case 1:
            break;
        default:
            return 1;
        }    
    }

    return 0;
}

int add_quad(Card quad[4], Hand_Space *hand_space)
{
    /* Create the quad bomb and then add it to the hand space */

    printf("Herfge\n");

    return 0;
}   