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

#define MIN_STRAIGHT_LENGTH 5
#define MAX_STRAIGHT_LENGTH 14
#define MAX_TRICK 14
#define MAX_TRICKS 650

typedef struct trickhelper {
	int num_cards;
	int high;
	int counts[NUM_VALUES];
	int cards[NUM_VALUES][NUM_SUITS];
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
void print_trick(Trick *trick);
void set_trick(Trick *trick, int type, int length, int num_cards, int high,
	int low, int has_phoenix, Card *cards);
void copy_trick(Trick *dest, Trick *src);

void init_trickset(TrickSet *trickset);
void print_trickset(TrickSet *trickset);
void add_trick(TrickSet *trickset, Trick *trick);
void make_singles(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_single(TrickSet *trickset, Card card);
void make_straights(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_straights(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper);
/* adds all possible straights of a specific length starting at low */
void add_straights_ph(TrickSet *trickset, int low, int length, int val,
	TrickHelper *trickhelper);
void add_straights_r(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper);
int sum_straight(int low, int length, TrickHelper *trickhelper, int *val);
void inc_counters(int *counters, int length, int *limits);

#endif // TRICK_H
