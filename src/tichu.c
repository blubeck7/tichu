#include <stdio.h>
#include "../inc/game.h"


int main(int argc, char *argv[])
{

	printf("Welcome to Tichu!\n");
	print_deck_all();
	shuffle_deck();
	print_deck_all();

	return 0;
}
