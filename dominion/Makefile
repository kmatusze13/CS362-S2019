CFLAGS= -Wall -fpic -coverage -lm -std=c99

default: tests.out

unittests.out: unittest1.c unittest2.c unittest3.c unittest4.c

        echo "Result for running BST tests:" > tests.out
        echo "unittest1.c:" >> tests.out
        gcc -o unittest1  unittest1.c $(CFLAGS)
        ./unittest1 >> tests.out
        gcov bst.c >> tests.out

        echo "unittest2.c:" >> tests.out
        gcc -o unittest2  unittest2.c $(CFLAGS)
        ./unittest2 >> tests.out
        gcov bst.c >> tests.out

        echo "unittest3.c:" >> tests.out
        gcc -o unittest3  unittest3.c $(CFLAGS)
        ./unittest3 >> tests.out
        gcov bst.c >> tests.out

        echo "unittest4.c:" >> tests.out
        gcc -o unittest4 unittest4.c $(CFLAGS)
        ./unittest4 >> tests.out
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
        rm tests.out unittest1 unittest2 unittest3 unittest4  -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
                                  
