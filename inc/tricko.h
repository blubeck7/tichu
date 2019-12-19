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
#define MAX_SINGLES 14
//#define MAX_TRICKS 360

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
	Trick singles[MAX_SINGLES];
    //Trick tricks[MAX_TRICKS];
} TrickSet;

void init_trick(Trick *trick);
void set_trick(Trick *trick, int type, int length, int num_cards, int high,
	int low, int has_phoenix, Card cards[MAX_TRICK]);
void print_trick(Trick *trick);
int is_valid_trick(Trick *trick, Trick *top);

void init_trickset(TrickSet *trickset);
void add_single(TrickSet *trickset, Trick *single);
#endif // TRICK_H
