#include <stdio.h>
#include <stdlib.h>
#include "../inc/deck.h"


int main(int argc, char *argv[])
{
	Deck *deck;

	deck = create_deck();
	print_deckf(deck);

}
