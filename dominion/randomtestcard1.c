
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {

//source: Lesson 11, slide 7
    struct gameState game;
    int seed = 1000;
    int numPlayers = 2;
        int k[10] = {6, embargo, 3, minion, mine, cutpurse,
                        sea_hag, tribute, 4, council_room};
    int deckSize;
    int handSize;
    int deckBefore;
    int deckAfter;
    int handBefore;
int handAfter;
    int discardBefore;
    int discardAfter;
    int i;
    int deckFailure = 0;
    int handFailure = 0;
    int discardFailure = 0;
    int testPassed = 0;
    int passed;

// source for making cards random: https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
    srand(time(NULL));
for(i = 0; i < 1000; i++){
        initializeGame(numPlayers, k, seed, &game);
        deckSize = rand() % (MAX_DECK + 1);

// sets the size of the player's hand
handSize = rand() % (deckSize + 1);

// source: Lecture 11, slide 13
        game.deckCount[0] = deckSize - handSize;
        game.handCount[0] = handSize;


        deckBefore = game.deckCount[0];
handBefore = game.handCount[0];
discardBefore = game.playedCardCount;
smithy(handSize, &game);

        deckAfter = game.deckCount[0];
handAfter = game.handCount[0];
discardAfter = game.playedCardCount;

 passed = 1;

// print statements for testing
        if(handAfter != (handBefore + 1)){
            printf("Failure: Incorrect number of cards drawn.\n\n");
            handFailure++;
            passed = 0;
        }

        if(deckAfter != (deckBefore - 3)){
            printf("Failure: Incorrect number of cards removed from deck.\n\n");
            deckFailure++;
            passed = 0;
        }
if(discardAfter != (discardBefore + 1)){
            printf("Failure: Smithy card not discarded after use.\n\n");
            discardFailure++;
            passed = 0;
        }

        if(passed == 1){
            printf("Great News! All tests passed!\n\n");
            testPassed++;
        }

    }

   printf("\n\n");
printf("Number of Tests Passed: %d\n", testPassed);
   printf("Number of Cards Drawn resulting in failure: %d\n", handFailure);
   printf("Number of times Smithy card failed to discard: %d\n\n", discardFailure);

   return 0;
}
