#ifndef CARD_H
#define CARD_H

#define NUM_CARDS 56
#define NUM_VALUES 17
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
typedef struct cardset {
	int num_cards;
	Card cards[NUM_CARDS];
} CardSet;

extern Card CARDS[NUM_CARDS];

int get_value(Card card);
int get_suit(Card card);
void print_card(Card card);

void init_cardset(CardSet *cardset);
void print_cardset(CardSet *cardset);
void add_card(CardSet *cardset, Card card);
void remove_card(CardSet *cardset, Card card);
void sort_cardset(CardSet *cardset);
int has_dog(CardSet *cardset);
int has_one(CardSet *cardset);
int has_phoenix(CardSet *cardset);
int has_dragon(CardSet *cardset);
int has_card(CardSet *cardset, Card card);
int count_value(CardSet *cardset, int value);
int get_num_cards(CardSet *cardset);

#endif // CARD_H
