#ifndef TYPES_H
#define TYPES_H


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


#endif // TYPES_H
