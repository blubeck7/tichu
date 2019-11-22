#ifndef DECK_H
#define DECK_H

typedef struct deck_t Deck;

Deck *create_deck(void);
int destroy_deck(Deck *deck);
int add_card(Deck *deck, Card *card)
int remove_card(Deck *deck, Card *card)
int print_deck(Deck *deck);
int shuffle_deck(Deck *deck);

#endif // DECK_H
