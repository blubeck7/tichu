#ifndef DECK_H
#define DECK_H

typedef struct deck_t Deck;

extern Deck deck;

//int init_deck(void);
//int destroy_deck(Deck *deck);
int print_deck(void);
int print_deck_all(void);
int shuffle_deck(void);

#endif // DECK_H
