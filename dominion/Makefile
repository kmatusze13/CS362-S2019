CFLAGS= -Wall -fpic -coverage -lm -std=c99

default: tests.out

randomtests.out: randomtestcard1.c	randomtestcard2.c	randomtestadventurer.c

        echo "Result for running random tests:" > tests.out
        echo "randomtestcard1.c:" >> tests.out
        gcc -o randomtestcard1  randomtestcard1.c $(CFLAGS)
        ./randomtestcard1 >> tests.out
        gcov bst.c >> tests.out

        echo "randomtestcard2.c:" >> tests.out
        gcc -o randomtestcard2  randomtestcard2.c $(CFLAGS)
        ./randomtestcard2 >> tests.out
        gcov bst.c >> tests.out

        echo "randomtestadventurer.c:" >> tests.out
        gcc -o unittest3  unittest3.c $(CFLAGS)
        ./unittest3 >> tests.out
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
        ./testDrawCard &> unittestresult.out
        gcov dominion1.c >> unittestresult.out
        cat dominion1.c.gcov >> unittestresult.out


player: player.c interface.o
        gcc -o player player.c -g  dominion1.o rngs.o interface.o $(CFLAGS)

all: playdom player


clean:
        rm tests.out randomtestcard1 randomtestcard2 randomtestadventurer  -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
                                  
