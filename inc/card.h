#ifndef CARD_H
#define CARD_H

#include "types.h"
 
int get_value(Card card);
int get_suit(Card card);
void print_card(Card card);
int is_phoenix(Card card);
int is_special(Card card);

void print_cards(Card cards[], int n);
void sort_cards(Card cards[], int n);
void add_card(Card cards[], int *n, Card card);
void remove_card(Card cards[], int *n, Card card);
void shuffle_cards(Card cards[], int n);
int has_card(Card cards[], int n, Card card);
int has_dog(Card cards[], int n);
int has_one(Card cards[], int n);
int has_phoenix(Card cards[], int n);
int has_dragon(Card cards[], int n);

#endif // CARD_H
