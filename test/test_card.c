#include <stdio.h>
#include <stdlib.h>
#include "../inc/card.h"


int main(int argc, char *argv[])
{
	FILE *fp;
	int ch, i, j;
	char value[3], suit[2], name[CARD_NAME_SIZE];
	Card *deck[56];

	fp = fopen("res/cards.txt", "r");

	for (i = 0; i < 56; i++) {
		// read in the value of the card
		    j = 0;
		    while ((ch = fgetc(fp)) != ',')
			value[j++] = ch;
		    value[j] = '\0';

		    // read in the suit of the card
		    j = 0;
		    while ((ch = fgetc(fp)) != ',')
			suit[j++] = ch;
		    suit[j] = '\0';

		// read in the name of the card
		j = 0;
		while ((ch = fgetc(fp)) != '\n')
		    name[j++] = ch;
		name[j] = '\0';

		deck[i] = create_card(atoi(value), atoi(suit), name);
	}

	fclose(fp);

	for (i = 0; i < 56; i++) {
		print_cardf(deck[i]);
		putchar('\n');
	}

}
