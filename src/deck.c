#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "../inc/card.h"

#define MAX_DECK_SIZE 56

typedef struct deck_t {
	int size;
	Card *cards[MAX_DECK_SIZE];
} Deck;


Deck *create_deck(void);
{
	Deck *deck;

	deck = malloc(sizeof(Deck));
	if (deck == NULL)
		exit(EXIT_FAILURE);

	deck->deck_size = 0;

	return deck;
}

int destroy_deck(Deck *deck)
{
	free(deck);

	return 0;
}

int add_card(Deck *deck, Card *card)
{
	if (deck->size < MAX_DECK_SIZE) {
		cards[deck->size] = card;
		deck->size++;

		return 0;
	}

	return 1;
}

int remove_card(Deck *deck, Card *card) {
	if (deck->size == 0)
		return 1;

	deck->size--;
	
	return 0;
}

int print_deck(Deck *deck)
{
	int i;

	for (i = 0; i < deck->size; i++) {


int shuffle_deck(Deck *deck);

/*
Deck *create_deck(void);
{
	Queue *queue;
	int i;

	if (max_size < 1)
		return NULL;

	if ((queue = (Queue *) malloc(sizeof(Queue))) == NULL)
		return NULL;

	queue->max_size = max_size;
	queue->size = queue->front = queue->back = 0;
	if ((queue->items = malloc(sizeof(void *) * max_size)) == NULL)
		return NULL;

	for (i = 0; i < max_size; i++)
		*(queue->items + i) = NULL;

	return queue;
}

int destroy_deck(Deck *deck)
{
	free(queue->items);
	free(queue);

	return 0;
}

int print_deck(Deck *deck);
{
	if (queue->size == queue->max_size)
		return -1;

	*(queue->items + queue->back) = item;
	queue->back = (queue->back + 1) % queue->max_size;
	queue->size++;

	return 0;
}*/
