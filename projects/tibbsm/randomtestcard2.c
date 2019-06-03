include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//testing procedure for Great Hall card
void testGreatHall(int player1, struct gameState *game, int handPos) {
    int result;
int numActions;
int handFailure = 0;
int deckFailure = 0;
int discardFailure = 0;
int discardBefore;
    int discardAfter;
    int discardCount = 0;
int deckAfter;
    int handBefore;
int handAfter;
int deckBefore;
int deckSize;
    int handSize;
  
  // source: Lecture 11, slide 8
    struct gameState testGame;
    memcpy (&testGame, game, sizeof(struct gameState));


    result = great_hall(handPos, *testG);

    drawCard(player1, game);
    game->numActions += 1;

    discardCard(handPos, player1, game, 0);
    discardCount++;

// source: Lecture 11, slide 13
 game.deckCount[0] = deckSize - handSize;
        game.handCount[0] = handSize;
deckBefore = game.deckCount[0];
handBefore = game.handCount[0];
discardBefore = game.playedCardCount;
great_hall(handSize, &game);
    deckAfter = game.deckCount[0];
handAfter = game.handCount[0];
discardAfter = game.playedCardCount;

   assert (result == 0); // determines whether great hall card works properly
    printf("Number of actions: Actions %d, expected %d\n", testG.numActions, game->numActions);
    if (testG.numActions != game->numActions)
        printf("Failure: Incorrect number of actions taken.\n");

//source: Smithy random test file
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
  printf("Failure: Great Hall not discarded after use\n\n");
            discardFailure++;
            passed = 0;
        }

        if(passed == 1){
            printf("Great News! All tests passed!\n\n");
            testPassed++;
        }

}

// main file
int main() {
    int i, n, player1;
    int handPos = 0;
        struct gameState game;

        SelectStream(2);
    PutSeed(3);

    printf("Testing Great Hall Card. \n");
    for (n = 0; n < 1000; n++) {
        printf("\n TEST\n\n");

         for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&game)[i] = floor(Random() * 256);
        }

        game.numActions = 0;
        player1 = floor(Random() * 2);

        do{
            handPos = Random() * game.handCount[player1];
        } while (handPos == game.handCount[player1]);
        game.hand[player1][handPos] = 3; // integer value for great hall
        testGreatHall(player1, &game, handPos);
    }
        printf("\n Testing is now complete \n\n");

        return 0;
}
