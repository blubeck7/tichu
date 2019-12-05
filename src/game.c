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
static int print_hands(Game *game);

int main(int argc, char *argv[])
{
	Game game;

	printf("Welcome!\n\n");
	
	init_game(&game);

	// while (!game.cur_state.is_game_done) {

	deal_eight(&game);
	deal_six(&game);
	game.cur_state.has_top_hand = 0;

	/*
	print_player(&(game.players[0]));
	print_player(&(game.players[1]));
	print_player(&(game.players[2]));
	print_player(&(game.players[3]));
	printf("\n");
	*/

	sort_cards(game.players[0].cards, 14);
	sort_cards(game.players[1].cards, 14);
	sort_cards(game.players[2].cards, 14);
	sort_cards(game.players[3].cards, 14);

	update_count(&(game.players[0]));
	update_count(&(game.players[1]));
	update_count(&(game.players[2]));
	update_count(&(game.players[3]));
	
	print_player(&(game.players[0]));
	print_player(&(game.players[1]));
	print_player(&(game.players[2]));
	print_player(&(game.players[3]));
	printf("\n");

	printf("Hands player 0:\n");
	get_hands(&game, &(game.players[0]));
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

int deal_six(Game *game) {
	int i, j;

	for (i = 0; i < NUM_PLAYERS; i++) {
		for (j = 0; j < 6; j++) {
			copy_card(&(game->players[i].cards[j + 8]),
			&(game->deck.cards[game->deck.order[i * 6 + j + 32]]));
		}
		game->players[i].num_cards = 14;
	}

	return 0;	
}

int get_singles(Game *game, Player *player)
{
	
	int i, j, n;

	for (i = 0; i < player->num_cards; i++) {
		n = game->cur_state.num_hands++;
		game->cur_state.cur_hands[n].type = SINGLE;
		game->cur_state.cur_hands[n].length = 1;
		game->cur_state.cur_hands[n].high = player->cards[i].value;
		game->cur_state.cur_hands[n].low = player->cards[i].value;
		for (j = 0; j < game->cur_state.cur_hands[n].length; j++)
			copy_card(&(game->cur_state.cur_hands[n].cards[j]),
				&(player->cards[i]));
	}
		
	return 0;
}

static int print_hands(Game *game)
{
	int i, j;
	
	printf("Current hands:\n");
	printf("%d\n", game->cur_state.num_hands);
	for (i = 0; i < game->cur_state.num_hands; i++) {
		printf("type: %d, length: %d, high: %d, low: %d ",
				game->cur_state.cur_hands[i].type,
				game->cur_state.cur_hands[i].length,
				game->cur_state.cur_hands[i].high,
				game->cur_state.cur_hands[i].low);
		printf("cards: ");
		for (j = 0; j < game->cur_state.cur_hands[i].length; j++)
			printf("%s ", game->cur_state.cur_hands[i].cards[j].name);
		printf("\n");
	}

	return 0;
}

int get_hands(Game *game, Player *player)
{
	/* Initialize the variables related to the current hands.
	 * There are four cases to deal with:
	 * 	1. no top hand, no phoenix.
	 * 	2. top hand, no phoenix.
	 * 	3. no top hand, phoenix.
	 * 	4 top hand, phoenix.
	 */

	game->cur_state.num_hands = 0;

	if (!game->cur_state.has_top_hand && !player->has[DRAGON + 1]) {
		printf("No top hand, no phoenix\n");
		get_singles(game, player);
	}

	print_hands(game);
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
