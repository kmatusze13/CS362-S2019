/*
 *  *  * Include the following lines in your makefile:
 *   *   *
 *    *    * cardtest2: cardtest2.c dominion.o rngs.o
 *     *     *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 *      *      */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

// source: updateCoins.c example file

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
        int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                        sea_hag, tribute, smithy, council_room};


// initialize a game state and player cards

initializeGame(numPlayers, k, seed, &G);

        printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

 // ----------- TEST 1: add coins for each drawn treasure
int maxHandCount = 5;
// arrays of all coppers, silvers, and golds
int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    printf ("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
#if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
#endif
                memset(&G, 23, sizeof(struct gameState)); // clear game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
#endif
                assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct

                memcpy(G.hand[p], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
#endif
                assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct
                   }
        }
    }
// ----------- TEST 2: discard cards from hand --------------
printf("TEST 2: discard cards\n");
        choice1 = 3;

// cycle through each eligible combination of cards to discard
for (i=1; i<G.handCount[thisPlayer]; i++) {
                for (j=i+1; j<G.handCount[thisPlayer]; j++) {

                        G.hand[thisPlayer][0] = steward;
                        G.hand[thisPlayer][1] = copper;
                        G.hand[thisPlayer][2] = duchy;
                        G.hand[thisPlayer][3] = estate;
                        G.hand[thisPlayer][4] = feast;

                        // copy the game state to a test case
                        memcpy(&testG, &G, sizeof(struct gameState));

                        printf("starting cards: ");
                        for (m=0; m<testG.handCount[thisPlayer]; m++) {
                                printf("(%d)", testG.hand[thisPlayer][m]);
                        }
                        printf("; ");

                        choice2 = j;
                        choice3 = i;
                        remove1 = testG.hand[thisPlayer][i];
                        remove2 = testG.hand[thisPlayer][j];
                        cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

                        printf("removed: (%d)(%d); ", remove1, remove2);
                        printf("ending cards: ");

// tests that the removed cards are no longer in the player's hand
for (m=0; m<testG.handCount[thisPlayer]; m++) {
                                printf("(%d)", testG.hand[thisPlayer][m]);
                                assert(testG.hand[thisPlayer][m] != remove1);
                                assert(testG.hand[thisPlayer][m] != remove2);
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
                        discarded = 3;
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
