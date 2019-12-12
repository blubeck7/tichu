#ifndef CARD_H
#define CARD_H

#define NUM_CARDS 56
#define NUM_VALUES 17
#define NUM_RVALUES 13
#define NUM_SUITS 5 
#define NUM_RSUITS 4

#define DOG 0
#define ONE 10
#define DRAGON 150
#define PHOENIX 160

#define get_value(card) (card / 10)
#define get_suit(card) (card % 10)

typedef int Card;
typedef struct card_count_t Card_Count;

struct card_count_t {
	int num_cards;
	int one_flags[NUM_VALUES];
	int two_flags[NUM_VALUES];
	int counts_s[NUM_VALUES];
	Card singles[NUM_VALUES][4];
	int counts_d[NUM_VALUES];
	Card doubles[NUM_VALUES][6][2];
	int counts_t[NUM_VALUES];
	Card triples[NUM_VALUES][4][3];
};

extern Card CARDS[NUM_CARDS];

int print_card(Card card);
int init_card_count(Card_Count *card_count);
int count_cards(Card cards[], int num_cards, Card_Count *card_count);
int print_card_count(Card_Count *card_count);
int sort_cards(Card cards[], int num_cards);

#endif // CARD_H
