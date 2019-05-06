/*
 *  *  *  * Include the following lines in your makefile:
 *   *   *   *
 *    *    *    * cardtest1: cardtest1.c dominion.o rngs.o
 *     *     *     *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 *      *      *      */

#include "dominion.h"
#include "dominion_helpers.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

// Inspired by sample cardtest4.c file for Steward

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0;
    int remove1;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
        struct gameState G, testG;
        int k[10] = {6, embargo, 3, minion, mine, cutpurse,
                        sea_hag, tribute, 4, council_room};

// initialize a game state and player cards
int initializeGame(numPlayers, k, seed, &G);
printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
 // ----------- TEST 1: choice1 = 1 = +3 cards --------------
  printf("TEST 1: +3 cards\n");

// copy the game state to a test case
memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(4,  &testG, handpos);

        newCards = 3;
        xtraCoins = 0;
        printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
        printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
        printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
        assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
        assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
        assert(testG.coins == G.coins + xtraCoins);

// ----------- TEST 2: Discard Smithy card --------------
printf("TEST 2: Discard the Smithy card\n");

// cycle through each eligible combination of 2 cards to trash
for (i=1; i<G.handCount[thisPlayer]; i++) {
                for (j=i+1; j<G.handCount[thisPlayer]; j++) {

                        G.hand[thisPlayer][0] = 4;

// copy the game state to a test case
memcpy(&testG, &G, sizeof(struct gameState));

                        printf("starting cards: ");
                        for (m=0; m<testG.handCount[thisPlayer]; m++) {
                                printf("(%d)", testG.hand[thisPlayer][m]);
                        }
                        printf("; ");

                        remove1 = testG.hand[thisPlayer][i];
printf("removed: (%d); ", remove1);
                        printf("ending cards: ");

// tests that the removed smithy card is no longer in the player's hand
for (m=0; m<testG.handCount[thisPlayer]; m++) {
                                printf("(%d)", testG.hand[thisPlayer][m]);
                                assert(testG.hand[thisPlayer][m] != remove1);
                        }
                        printf(", expected: ");
                        for (m=1; m<G.handCount[thisPlayer]; m++) {
                                if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) {
                                        printf("(%d)", G.hand[thisPlayer][m]);
                                }
                        }
                        printf("\n");

// tests for the appropriate number of remaining cards
newCards = 0;
                        xtraCoins = 0;
                        discarded = 1;
                        if (i==1 && j==2) {
                                printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
                                printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
                        }
                        assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
                        assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
                }

        }
 
 printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


        return 0;
}
