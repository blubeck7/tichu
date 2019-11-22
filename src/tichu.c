#include <stdio.h>
#include "../inc/card.h"
#include "../inc/deck.h"


Deck *load_deck(void);


int main(int argc, char *argv[])
{
	Deck *deck;

	/* create tichu deck */
	deck = load_deck();
