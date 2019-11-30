#ifndef DECK_H
#define DECK_H


#include "../inc/card.h"


#define DECK_SIZE 56


typedef struct deck_t {
	int size;
	int order[DECK_SIZE];
	Card cards[DECK_SIZE];
} Deck;

int init_deck(Deck *deck);
int print_deck(Deck *deck);
int print_deck_all(Deck *deck);
int shuffle_deck(Deck *deck);




#define CARD_NAME_SIZE 8
#define DECK_SIZE 56
#define MAX_ROUNDS 65
#define MAX_TURNS 26
#define MAX_HAND 14


typedef struct deck_t {
	int size;
	int order[DECK_SIZE];
	Card cards[DECK_SIZE];
} Deck;

typedef struct hand_t

typedef struct turn_t {
	int num; // turn number
	int player; // player whose turn it is
	int grand; // grand tichu call
	int tichu; // tichu call
	int pass_left; // card passed to the player's left
	int pass_right; // card passed to the player's right
	int pass_across; // card passed across the player
	int hand; // type of hand played, single, pair, triple, etc.
	int size; // number of cards in the hand played
	int cards[MAX_HAND]; // cards played
	int out; // if the player went out
} Turn;

typedef struct round_t {
	int num;
	Turn turns[MAX_TURNS];
} Round;

typedef struct history_t {
	int num_turns;
	int cur_turn;
	int cur_round;
	Round rounds[MAX_ROUNDS];
	int grand[4]; // grand tichu calls
};
#endif // DECK_H
