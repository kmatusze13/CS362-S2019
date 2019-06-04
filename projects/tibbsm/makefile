FLAGS= -Wall -fpic -coverage -lm -std=c99

default: tests.out

tests.out: cardtest1.c cardtest2.c cardtest3.c cardtest4.c
        
        echo "Result for running BST tests:" > tests.out
        echo "cardtest1.c:" >> tests.out
        gcc -o cardtest1  cardtest1.c $(CFLAGS)
        ./cardtest1 >> tests.out
        gcov bst.c >> tests.out
        
        echo "cardtest2.c:" >> tests.out
        gcc -o cardtest2  cardtest2.c $(CFLAGS)
        ./cardtest2 >> tests.out
        gcov bst.c >> tests.out
        
        echo "cardtest3.c:" >> tests.out
        gcc -o cardtest3  cardtest3.c $(CFLAGS)
        ./cardtest3 >> tests.out
        gcov bst.c >> tests.out
        
        echo "cardtest4.c:" >> tests.out
        gcc -o cardtest4 unittest4.c $(CFLAGS)
        ./cardtest4 >> tests.out
        gcov bst.c >> tests.out

rngs.o: rngs.h rngs.c
        gcc -c rngs.c -g  $(CFLAGS)

dominion1.o: dominion.h dominion1.c rngs.o
        gcc -c dominion1.c -g  $(CFLAGS)

playdom: dominion1.o playdom.c
        gcc -o playdom playdom.c -g dominion1.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion1.o rngs.o
        gcc  -o testDrawCard -g  testDrawCard.c dominion1.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion1.o rngs.o
        gcc -o badTestDrawCard -g  badTestDrawCard.c dominion1.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion1.o rngs.o
        gcc -o testDrawCard -g  testDrawCard.c dominion1.o rngs.o $(CFLAGS)
        
        testAll: dominion1.o testSuite.c
        gcc -o testSuite testSuite.c -g  dominion1.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
        gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
        ./testDrawCard >> tests.out
        gcov dominion1.c >> tests.out
        cat dominion1.c.gcov >> tests.out

player: player.c interface.o
        gcc -o player player.c -g  dominion1.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:  
        rm tests.out cardtest1 cardtest2 cardtest3 cardtest4 -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
