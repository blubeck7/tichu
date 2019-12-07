#ifndef CARD_H
#define CARD_H

typedef int Card;
typedef struct card_count_t Card_Count;

struct card_count_t {
	int num_cards;
	int counts[NUM_VALUES];
	int one_flags[NUM_VALUES];
	int two_flags[NUM_VALUES];
	Card cards[NUM_VALUES - 4][NUM_SUITS - 1];
};

int print_card(Card card);
int init_card_count(Card_Count *card_count);
int count_cards(Card cards[], int num_cards, Card_Count *card_count);
int print_card_count(Card_Count *card_count);
int sort_cards(Card cards[], int num_cards);

#endif // CARD_H
