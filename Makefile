#tichu

test_deck: obj/test_deck.o obj/deck.o
	gcc -std=c99 -o bin/test_deck obj/test_deck.o obj/deck.o

obj/test_deck.o: test/test_deck.c inc/deck.h
	gcc -std=c99 -c -o obj/test_deck.o test/test_deck.c

obj/deck.o: src/deck.c inc/deck.h
	gcc -std=c99 -c -o obj/deck.o src/deck.c

#test_card: obj/test_card.o obj/card.o
	#gcc -std=c99 -o bin/test_card obj/test_card.o obj/card.o

#obj/test_card.o: test/test_card.c inc/card.h
	#gcc -std=c99 -c -o obj/test_card.o test/test_card.c

#obj/card.o: src/card.c inc/card.h
	#gcc -std=c99 -c -o obj/card.o src/card.c

#test_deck.o: test/test_deck.c
	#gcc -c test/test_deck.c -o obj/test_deck.o

#deck.o: src/deck.c
	#gcc -c src/deck.c -o obj/deck.o

clean:
	rm obj/*
