/*
 *  *  *  * Include the following lines in your makefile:
 *   *   *   *
 *    *    *    * unittest3: unittest3.c dominion.o rngs.o
 *     *     *     *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 *      *      *      */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

// inspired by cardtest4.c for Steward

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
        struct gameState G, testG;
        int k[10] = {adventurer, embargo, great_hall, minion, mine, cutpurse,
                        sea_hag, tribute, smithy, council_room};

// initialize a game state and player cards

initializeGame(numPlayers, k, seed, &G);

        printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

        // ----------- TEST 1: choice1 = 1 = +1 cards --------------
        printf("TEST 1: +1 cards\n");

// copy the game state to a test case
memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(great_hall,  &testG, handpos, &bonus);

        newCards = 1;
        xtraCoins = 0;
        printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
        printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
        printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
        assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
        assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);

// ----------- TEST 2: Discard Great Hall card --------------
printf("TEST 2: Discard the Great Hall card\n");

// cycle through each eligible combination of 2 cards to trash
for (i=1; i<G.handCount[thisPlayer]; i++) {
                for (j=i+1; j<G.handCount[thisPlayer]; j++) {

                        G.hand[thisPlayer][0] = great_hall;
                        // copy the game state to a test case
 memcpy(&testG, &G, sizeof(struct gameState));

                        printf("starting cards: ");
                        for (m=0; m<testG.handCount[thisPlayer]; m++) {
                                printf("(%d)", testG.hand[thisPlayer][m]);
                        }
                        printf("; ");

                        choice2 = j;
                        remove1 = testG.hand[thisPlayer][i];

                        printf("removed: (%d)(%d); ", remove1);
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

