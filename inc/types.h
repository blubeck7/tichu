#ifndef TYPES_H
#define TYPES_H


#define CARD_NAME_SIZE 8
#define DECK_SIZE 56
#define PLAYER_NAME 8
#define NUM_PLAYERS 4
#define MAX_HAND 14
#define HAND_SPACE 200

#define PASS 0
#define SINGLE 1
#define PAIR 2
#define TRIPLE 3
#define FULL 4
#define STRAIGHT 5
#define BOMB 6

#define TICHU 1
#define GRAND 2

typedef struct card_t Card;
typedef struct deck_t Deck;
typedef struct hand_t Hand;
typedef struct player_t Player;
typedef struct game_t Game;
typedef int (Strat)(Game *game, Hand *hand);

struct card_t {
	int value;
	int suit;
	char name[CARD_NAME_SIZE];
};

struct deck_t {
	int size;
	int order[DECK_SIZE];
	Card cards[DECK_SIZE];
};

struct hand_t {
	int type; // pass, single, etc.
	int length; // number of cards 
	int high; // high card
	int low; // low card
	Card cards[MAX_HAND];
};

struct player_t {
        int num;
        char name[PLAYER_NAME];
        int num_cards;
	Strat *strat;
        Card cards[MAX_HAND];
};

struct game_t {
    Deck deck;
    Player players[NUM_PLAYERS];
    int num_hands; // number of valids hands
    Hand hands[HAND_SPACE];
};


extern Deck START_DECK;


#endif // TYPES_H