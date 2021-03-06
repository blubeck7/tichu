#tichu make file

#OBJECTS = obj/game.o obj/player.o obj/res.o

#tichu: $(OBJECTS)
	#gcc -Wall -std=c99 -o bin/tichu $(OBJECTS)

#obj/game.o: src/game.c inc/game.h inc/player.h inc/types.h
	#gcc -Wall -std=c99 -c -o obj/game.o src/game.c

#obj/player.o: src/player.c inc/game.h inc/player.h inc/types.h
	#gcc -Wall -std=c99 -c -o obj/player.o src/player.c

#obj/res.o: src/res.c inc/types.h
	#gcc -Wall -std=c99 -c -o obj/res.o src/res.c


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

#tichu: obj/tichu.o obj/card.o obj/hand.o
	#gcc -Wall -std=c99 -O3 -o bin/tichu obj/tichu.o obj/card.o obj/hand.o

#obj/tichu.o: src/tichu.c inc/card.h inc/hand.h
	#gcc -Wall -std=c99 -c -O3 -o obj/tichu.o src/tichu.c

#obj/card.o: src/card.c inc/card.h
	#gcc -Wall -std=c99 -c -O3 -o obj/card.o src/card.c

#obj/hand.o: src/hand.c inc/card.h inc/hand.h
	#gcc -Wall -std=c99 -c -O3 -o obj/hand.o src/hand.c

tichu: obj/tichu.o obj/card.o obj/trick.o obj/game.o obj/player.o
	gcc -Wall -std=c99 -O3 -o bin/tichu obj/tichu.o obj/card.o \
	obj/trick.o obj/game.o obj/player.o

obj/tichu.o: src/tichu.c inc/card.h inc/trick.h inc/player.h inc/game.h \
inc/types.h
	gcc -Wall -std=c99 -c -O3 -o obj/tichu.o src/tichu.c

obj/card.o: src/card.c inc/card.h inc/types.h
	gcc -Wall -std=c99 -c -O3 -o obj/card.o src/card.c

obj/trick.o: src/trick.c inc/card.h inc/trick.h inc/types.h
	gcc -Wall -std=c99 -c -O3 -o obj/trick.o src/trick.c

obj/player.o: src/player.c inc/card.h inc/trick.h inc/types.h inc/player.h
	gcc -Wall -std=c99 -c -O3 -o obj/player.o src/player.c

obj/game.o: src/game.c inc/types.h inc/card.h inc/trick.h inc/game.h inc/player.h
	gcc -Wall -std=c99 -c -O3 -o obj/game.o src/game.c

#test_deck.o: test/test_deck.c
	#gcc -c test/test_deck.c -o obj/test_deck.o

#deck.o: src/deck.c
	#gcc -c src/deck.c -o obj/deck.o

clean:
	rm -f obj/* bin/*
