#tichu

test_card: test/test_card.c
	gcc -std=c11 -o bin/test_card test/test_card.c

#test_deck.o: test/test_deck.c
	#gcc -c test/test_deck.c -o tmp/test_deck.o

#deck.o: src/deck.c
	#gcc -c src/deck.c -o tmp/deck.o

clean:
	rm tmp/*
