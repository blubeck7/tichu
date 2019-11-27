#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_t Player;

extern Deck deck;

//int init_deck(void);
//int destroy_deck(Deck *deck);
int print_deck(void);
int print_deck_all(void);
int shuffle_deck(void);

#endif // DECK_H
