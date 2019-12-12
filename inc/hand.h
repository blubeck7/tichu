#ifndef HAND_H
#define HAND_H

#include "card.h"

#define NONE 0
#define PASS 0
#define SINGLE 1
#define DOUBLE 2
#define TRIPLE 3
#define FULL 4
#define STRAIGHT 5
#define BOMB 6

#define MAX_HAND 14

typedef struct hand_t Hand;
typedef struct hand_space_t Hand_Space;

struct hand_t {
	int type; // pass, single, etc.
	int length; // number of cards 
	int high; // high card
	int low; // low card
	Card cards[MAX_HAND];
};

struct hand_space_t {
    int num_hands;
    Hand hands[270];
};

int gen_hands(Card_Count *card_count, Hand_Space *hand_space, Hand *lead_hand);
int print_hands(Hand_Space *hand_space);
int print_hand(Hand *hand);


#endif // HAND_H
