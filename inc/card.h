#ifndef CARD_H
#define CARD_H

#define CARD_NAME_SIZE 11

typedef struct card_t Card;

Card *create_card(int value, int suit, char name[CARD_NAME_SIZE]);
int destroy_card(Card *card);
int print_card(Card *card);
int print_cardf(Card *card);

#endif // CARD_H
