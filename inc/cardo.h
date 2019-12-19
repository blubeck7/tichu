#ifndef CARD_H
#define CARD_H

typedef struct card Card;
typedef struct card CardSet;

Card *create_card(int value; int suit; char *name);
int destroy_card(Card *card);
int get_value(Card *card);
int get_suit(Card *card);
char *get_name(Card *card);
int set_value(Card *card, int value);
int set_suit(Card *card, int suit);
char *set_name(Card *card, char *name);
int compare(Card *card1, Card *card2);
int copy(Card *card1, Card *card2);
int print_card(Card *card);

CardSet *create_cardset(int num_cards);
int destroy_cardset(CardSet *cardset);
