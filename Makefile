#tichu make file

game: obj/game.o obj/res.o
	gcc -Wall -std=c99 -o bin/game obj/game.o obj/res.o

obj/game.o: src/game.c inc/game.h
	gcc -Wall -std=c99 -c -o obj/game.o src/game.c

obj/res.o: src/res.c inc/game.h
	gcc -Wall -std=c99 -c -o obj/res.o src/res.c

#tichu: obj/tichu.o obj/deck.o
	#gcc -std=c99 -o bin/tichu obj/tichu.o obj/deck.o

#test_deck: obj/test_deck.o obj/deck.o
	#gcc -std=c99 -o bin/test_deck obj/test_deck.o obj/deck.o

#obj/tichu.o: src/tichu.c inc/deck.h
	#gcc -std=c99 -c -o obj/tichu.o src/tichu.c

#obj/test_deck.o: test/test_deck.c inc/deck.h
	#gcc -std=c99 -c -o obj/test_deck.o test/test_deck.c

#obj/deck.o: src/deck.c inc/deck.h
	#gcc -std=c99 -c -o obj/deck.o src/deck.c

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
	rm -f obj/* bin/*
