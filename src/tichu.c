#include <stdio.h>
#include "../inc/card.h"


int main(int argc, char *argv[])
{
	Card_Count card_count;

	printf("Welcome to Tichu!\n");
	init_card_count(&card_count);
	print_card_count(&card_count);


	return 0;
}
