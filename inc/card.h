#ifndef CARD_H
#define CARD_H

#define CARD_NAME_SIZE 8

typedef struct card_t {
	int value;
	int suit;
	char name[CARD_NAME_SIZE];
} Card;

int print_card(Card *card);
int print_card_all(Card *card);

#endif // CARD_H
