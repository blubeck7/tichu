#ifndef TYPES_H
#define TYPES_H


#define CARD_NAME_SIZE 8
#define DECK_SIZE 56
#define PLAYER_NAME 8
#define NUM_PLAYERS 4
#define MAX_HAND 14

#define PASS 0
#define SINGLE 1
#define PAIR 2
#define TRIPLE 3
#define FULL 4
#define STRAIGHT 5
#define BOMB 6


typedef struct card_t {
	int value;
	int suit;
	char name[CARD_NAME_SIZE];
} Card;

typedef struct deck_t {
	int size;
	int order[DECK_SIZE];
	Card cards[DECK_SIZE];
} Deck;

typedef struct hand_t {
	int type;
	int length; // number of cards 
	int high; // high card
	int low; // low card
	Card cards[MAX_HAND];
} Hand;

typedef struct player_t {
        int num;
        char name[PLAYER_NAME];
        int num_cards;
        Card cards[MAX_HAND];
	int (* strat)(Game *game, Hand *hand);
} Player;

typedef struct game_t {
    Deck deck;
    Player players[NUM_PLAYERS];
} Game;


extern Deck START_DECK;


#endif // TYPES_H