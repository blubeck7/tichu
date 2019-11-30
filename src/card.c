#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/card.h"


int print_card(Card *card)
{
	printf("%s", card->name);

	return 0;
};

int print_cardf_all(Card *card)
{
	printf("%d %d %s", card->value, card->suit, card->name);

	return 0;
};
