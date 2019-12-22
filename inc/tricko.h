#ifndef TRICK_H
#define TRICK_H

#include "card.h"

#define PASS 0
#define SINGLE 1
#define DOUBLE 2
#define TRIPLE 3
#define FULL 4
#define STRAIGHT 5
#define DSTRAIGHT 6
#define BOMB 7
#define MAX_TRICK 14
#define MAX_TRICKS 500

typedef struct trickhelper {
    int has_phoenix;
	int reg_counts[NUM_RVALUES];
	int reg_cards[NUM_RVALUES][NUM_SUITS];
} TrickHelper;

typedef struct trick {
	int type;
	int length; 
	int num_cards;
	int high;
	int low;
	int has_phoenix;
	Card cards[MAX_TRICK];
} Trick;

typedef struct trickset {
    int num_tricks;
    Trick tricks[MAX_TRICKS];
} TrickSet;


void init_trickhelper(TrickHelper *trickhelper);
void print_trickhelper(TrickHelper *trickhelper);
void set_trickhelper(TrickHelper *trickhelper, Card cards[], int n);

void init_trick(Trick *trick);
void set_trick(Trick *trick, int type, int length, int num_cards, int high,
	int low, int has_phoenix, Card *cards);
void print_trick(Trick *trick);

void print_trickset(TrickSet *trickset);
void make_singles(TrickSet *trickset, Card cards[], int n);
void add_single(TrickSet *trickset, Card card);
/*
int is_valid_trick(Trick *trick, Trick *top);

void init_trickset(TrickSet *trickset);

*/

#endif // TRICK_H
