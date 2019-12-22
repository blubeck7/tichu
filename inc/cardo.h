#ifndef CARD_H
#define CARD_H

#define NUM_CARDS 56
#define NUM_VALUES 17
#define NUM_RVALUES 13
#define NUM_SUITS 4 

#define BLANK 0
#define DOG 4
#define DOG_VALUE 0
#define ONE 14
#define ONE_VALUE 1
#define PHOENIX 154
#define PHOENIX_VALUE 15
#define DRAGON 164
#define DRAGON_VALUE 16

typedef int Card;

extern Card CARDS[NUM_CARDS];

int get_value(Card card);
int get_suit(Card card);
void print_card(Card card);
int is_phoenix(Card card);
int is_special(Card card);

void print_cards(Card cards[], int n);
void sort_cards(Card cards[], int n);
void add_card(Card cards[], int *n, Card card);
void remove_card(Card cards[], int *n, Card card);
int has_card(Card cards[], int n, Card card);
int has_dog(Card cards[], int n);
int has_one(Card cards[], int n);
int has_phoenix(Card cards[], int n);
int has_dragon(Card cards[], int n);




//void make_doubles(Card cards[], int n, Card doubles[], int d);
/* Takes a set of cards of size n and makes all combinations of 2 elements */

//int count_value(CardSet *cardset, int value);
//int get_num_cards(CardSet *cardset);

#endif // CARD_H
