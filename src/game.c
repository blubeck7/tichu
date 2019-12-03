#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../inc/game.h"
#include "../inc/player.h"
#include "../inc/types.h"

static int init_deck(Deck *deck);
static int print_deck_all(Deck *deck);
static int shuffle_deck(Deck *deck);
static int copy_card(Card *dest, Card *src);
static int get_singles(Game *game, Player *player);

int main(int argc, char *argv[])
{
	Game game;

	printf("Welcome!\n");
	
	init_game(&game);

	print_player(&(game.players[0]));
	print_player(&(game.players[1]));
	print_player(&(game.players[2]));
	print_player(&(game.players[3]));

	while (!game.cur_state.is_game_done) {

	deal_eight(&game);

	print_player(&(game.players[0]));
	print_player(&(game.players[1]));
	print_player(&(game.players[2]));
	print_player(&(game.players[3]));

	sort_cards(game.players[0].cards, 8);
	sort_cards(game.players[1].cards, 8);
	sort_cards(game.players[2].cards, 8);
	sort_cards(game.players[3].cards, 8);

	print_player(&(game.players[0]));
	print_player(&(game.players[1]));
	print_player(&(game.players[2]));
	print_player(&(game.players[3]));

	// printf("Press q to quit at anytime.")

	return 0;
}


int init_game(Game *game)
{
	int i;

	/* TODO: implement with a better random generator */
	srand((unsigned int) time(NULL));

	init_deck(&(game->deck));

	init_player(&(game->players[0]), 0, "Human", NULL);
	init_player(&(game->players[1]), 1, "Human", NULL);
	init_player(&(game->players[2]), 2, "Human", NULL);
	init_player(&(game->players[3]), 3, "Human", NULL);

	game->cur_state.is_game_done = 0;
	for (i = 0; i < NUM_TEAMS; i++)
		game->cur_state.team_points[i] = 0;

	return 0;
}

int deal_eight(Game *game) {
	int i, j;

	for (i = 0; i < NUM_PLAYERS; i++) {
		for (j = 0; j < 8; j++) {
			copy_card(&(game->players[i].cards[j]),
			&(game->deck.cards[game->deck.order[i * 8 + j]]));
		}
		game->players[i].num_cards = 8;
	}

	return 0;	
}

static int get_singles(Game *game, Player *player)
{
	/*
	int i;

	if (!game->has_top_hand) {
		for (i = 0; player->num_cards
		
	*/
	return 0;
}

int get_hands(Game *game, Player *player)
{
		/*
	int i;

	game->num_hands = 0;

	if (!game->has_top_hand) {
		get_singles(game, player);
		for (i = 0; i < MAX_HAND / 2; i ++)
			get_doubles(Game *game, Player *player, i + 1);
		get_triples(Game *game, Player *player);
		get_full(Game *game, Player *player);
		for (i = 5; i <= MAX_HAND; i ++)
			get_straight(Game *game, Player *player);
		for (i = 4; i <= MAX_HAND; i ++)
			get_bomb(Game *game, Player *player, i);
	}		
		*/
	return 0;
}

int sort_cards(Card cards[MAX_HAND], int num_cards)
{
	int i, key1, key2, done;
	Card card;

	done = 0;
	while (!done) {
		done = 1;
		for (i = 0; i < num_cards - 1; i++) {
			key1 = cards[i].value * 10 + cards[i].suit;
			key2 = cards[i + 1].value * 10 + cards[i + 1].suit;
			if (key2 < key1) {
				card.value = cards[i].value;
				card.suit = cards[i].suit;
				strcpy(card.name, cards[i].name);
				
				cards[i].value = cards[i + 1].value;
				cards[i].suit = cards[i + 1].suit;
				strcpy(cards[i].name, cards[i + 1].name);
				
				cards[i + 1].value = card.value;
				cards[i + 1].suit = card.suit;
				strcpy(cards[i + 1].name, card.name);

				done = 0;
			}
		}
	}

	return 0;
}

static int init_deck(Deck *deck)
{
	int i;

	deck->size = START_DECK.size;
	for (i = 0; i < DECK_SIZE; i++)
		deck->order[i] = START_DECK.order[i];

	for (i = 0; i < DECK_SIZE; i++) {
		deck->cards[i].value = START_DECK.cards[i].value;
		deck->cards[i].suit = START_DECK.cards[i].suit;
		strcpy(deck->cards[i].name, START_DECK.cards[i].name);
	}

	shuffle_deck(deck);

	return 0;
}

static int print_deck_all(Deck *deck)
{
	int i;

	for (i = 0; i < deck->size; i++)
		printf("%d ", deck->order[i]);
	printf("\n");

	for (i = 0; i < deck->size; i++)
		printf("%-2d %d %s\n",
		deck->cards[i].value,
		deck->cards[i].suit,
		deck->cards[i].name);

	return 0;
}


static int shuffle_deck(Deck *deck)
{
	int cards[DECK_SIZE], n_rem, pos, i, j;

	for (i = 0; i < DECK_SIZE; i++)
		cards[i] = i;

	n_rem = DECK_SIZE;
	for (i = 0; i < DECK_SIZE; i++) {
		/* Randomly choose an unshuffled card. Then add it to the
		 * shuffled array. Shift the unshuffled cards down.
		 */
		/* TODO: Eliminate tail numbers */
		pos = rand() % n_rem;
		deck->order[i] = cards[pos];
		for (j = pos + 1; j < n_rem; j++)
			cards[j - 1] = cards[j];
		n_rem--;
	}

	return 0;
}

static int copy_card(Card *dest, Card *src) {
	dest->value = src->value;
	dest->suit = src->suit;
	strcpy(dest->name, src->name);

	return 0;
}
