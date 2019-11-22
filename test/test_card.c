#include <locale.h>
#include <stdio.h>
#include "../src/card.c"


int main(int argc, char *argv[])
{
	Card *card;

	setlocale(LC_ALL, "en_US.utf8");
	card = create_card(2, 0, L"2\u2618");

	print_card(card);

	return 0;
}
