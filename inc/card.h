#ifndef CARD_H
#define CARD_H

#define CARD_NAME_SIZE 13

typedef struct card_t Card;

Card *create_card(int value, int suit, wchar_t name[CARD_NAME_SIZE]);
int destroy_card(Card *card);
int print_card(Card *card);

#endif // CARD_H
