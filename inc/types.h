#ifndef TYPES_H
#define TYPES_H

#define NUM_CARDS 56
#define NUM_VALUES 17
#define NUM_RVALUES 13
#define NUM_SUITS 4 

#define BLANK 0
#define DOG 4
#define DOG_VALUE 0
#define ONE 14
#define ONE_VALUE 1
#define PHOENIX 154
#define PHOENIX_VALUE 15
#define DRAGON 164
#define DRAGON_VALUE 16

#define PASS 0
#define SINGLE 1
#define DOUBLE 2
#define TRIPLE 3
#define FULL 4
#define STRAIGHT 5
#define DSTRAIGHT 6
#define BOMB 7

#define MAX_DOUBLES 10
#define MAX_TRIPLES 10
#define MIN_STRAIGHT_LENGTH 5
#define MAX_STRAIGHT_LENGTH 14
#define MIN_DSTRAIGHT_LENGTH 2
#define MAX_DSTRAIGHT_LENGTH 7
#define MAX_DSTRAIGHT_CARDS 28
#define MAX_TRICK 14
#define MAX_TRICKS 1100

#define PLAYER_NAME 8
#define NUM_PLAYERS 4
#define MAX_HAND 14

typedef int Card;
typedef struct trickhelper TrickHelper;
typedef struct trick Trick;
typedef struct trickset TrickSet;
typedef struct turn Turn;
typedef struct round Round;
typedef struct match Match; 
typedef struct game Game;
typedef struct player Player;
//typedef struct cur_state_t Cur_State;
//typedef struct count_t Count;
typedef int (Strat)(Game *game, Trick *trick);

extern Card CARDS[NUM_CARDS];

struct trickhelper {
	int num_cards;
	int high;
	int counts[NUM_VALUES];
	int cards[NUM_VALUES][NUM_SUITS];
	int counts_d[NUM_VALUES];
	int doubles[NUM_VALUES][MAX_DOUBLES][2];
	int counts_t[NUM_VALUES];
	int triples[NUM_VALUES][MAX_TRIPLES][3];
};

struct trick {
	int type;
	int length; 
	int num_cards;
	int high;
	int low;
	int has_phoenix;
	Card cards[MAX_TRICK];
};

struct trickset {
    int num_tricks;
    Trick tricks[MAX_TRICKS];
};

typedef int (Strat)(Game *game, Trick *trick);

typedef struct player {
	int num;
	char name[PLAYER_NAME];
	int num_cards;
	Card cards[MAX_HAND];
	int num_captured_cards;
	Card captured_cards[NUM_CARDS];
	Strat *strat;
} Player;



















/*
#define CARD_NAME_SIZE 8
#define DECK_SIZE 56
#define PLAYER_NAME 8
#define NUM_PLAYERS 4
#define NUM_TEAMS 2
#define MAX_HAND 14
#define HAND_SPACE 260
#define MAX_TURNS 25
#define MAX_ROUNDS 60
#define MAX_MATCHES 2

#define NONE 0
#define PASS 0
#define SINGLE 1
#define PAIR 2
#define TRIPLE 3
#define FULL 4
#define STRAIGHT 5
#define BOMB 6

#define TICHU 1
#define GRAND 2

#define DRAGON 15
#define PHOENIX 16

typedef struct card_t Card;
typedef struct deck_t Deck;
typedef struct hand_t Hand;
typedef struct player_t Player;
typedef struct turn_t Turn;
typedef struct round_t Round;
typedef struct game_t Game;
typedef struct match_t Match; 
typedef struct cur_state_t Cur_State;
typedef struct count_t Count;
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

struct count_t {
	int count;
	Card cards[4];
};

struct player_t {
	int num;
	char name[PLAYER_NAME];
	int num_cards;
	Card cards[MAX_HAND];
	int num_captured_cards;
	Card captured_cards[DECK_SIZE];
	Strat *strat;
	Count counts[17]; //count of card values: dog, phoenix, one, dragon
	int has[17]; //card indicators.
};

struct turn_t {
	int num;
	Hand hand;
	int tichu;
	Card call;
	Card passed[NUM_PLAYERS];
};

struct round_t {
	int num;
	Turn turns[MAX_TURNS];
};

struct match_t {
	int num;
	int order[NUM_PLAYERS];
	int player_points[NUM_PLAYERS];
	int team_points[NUM_TEAMS];
	Round rounds[MAX_ROUNDS];
};

struct cur_state_t {
	int is_game_done;
	int is_match_done;
	int is_round_done;
	int cur_match;
	int cur_round;
	int cur_turn;
	int cur_player;
	int num_passes;
	int has_call_card;
	Card called_card;
	int has_top_hand;
	int num_hands; // number of valids hands
	Hand top_hand;
	Hand cur_hands[HAND_SPACE];
	int team_points[NUM_TEAMS];
};

struct game_t {
	Deck deck;
	Player players[NUM_PLAYERS];
	Match matches[MAX_MATCHES];
	Cur_State cur_state;
};


extern Deck START_DECK;

*/
#endif // TYPES_H
