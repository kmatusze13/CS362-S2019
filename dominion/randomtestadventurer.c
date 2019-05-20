#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//source: Lesson 11, slide 7
int main() {
    struct gameState game;
    int seed = 1000;
    int numPlayers = 2;
    int curPlayer = 0;
        int k[10] = {6, embargo, 3, minion, mine, cutpurse,
                        sea_hag, tribute, 4, council_room};
    int deckSize;
    int handSize;
    int i;
    int j;
    int q;
    int randomCard;
    int randVal;
    int m;
    int coinCount;
    int x;
    int discardCopper;
    int discardSilver;
    int discardGold;
    int coinCountBefore;
    int testPassed = 0;
    int drawTestFailed = 0;
    int discardTestFailed = 0;

    srand(time(NULL));
  
   //randomizes hand size
   for(i = 0; i < 1000000; i++){
        initializeGame(numPlayers, k, seed, &game);
        coinCountBefore = 0;
        deckSize = rand() % (MAX_DECK + 1);
   //set the size of the player's hand
   handSize = rand() % (deckSize + 1);


        game.deckCount[0] = deckSize - handSize;
        game.handCount[0] = handSize;
     // source: Lecture 11, slide 9
        for (j = 0; j < numPlayers; j++){
            for(q = 0; q < game.deckCount[j]; q++){
                randomCard = rand() % (50 + 1);
                randVal = rand() % (10);
                if(randomCard == 1){
                    game.deck[j][q] = copper;
                } else if(randomCard == 2){
                    game.deck[j][q] = silver;
                }
                }else {
                    game.deck[j][q] = k[randK];
                }
            }
        }

// source: Lecture 11, slide 13
        for(m = 0; m < game.handCount[curPlayer]; m++){
            if(game.hand[curPlayer][m] == copper || game.hand[curPlayer][m] == silver){
                coinCountBefore++;
            }
        }
coinCount = 0;

        for(m = 0; m < game.handCount[curPlayer]; m++){
            if(game.hand[curPlayer][m] == copper || game.hand[curPlayer][m] == silver){
                coinCount++;
            }
        }
 discardCopper = 0;
        discardSilver = 0;
        for(x = 0; x < game.discardCount[curPlayer]; x++){
            if(game.discard[curPlayer][x] == copper) {
                discardCopper++;
            } else if(game.discard[curPlayer][x] == silver) {
                discardSilver++;
            }
        }
  int passed = 1;
        if(coinCount > (coinCountBefore + 2)){
            printf("Too many cards were drawn: Test Failed\n\n");
            drawTestFailed++;
            passed = 0;
        }
if( coinCount < coinCountBefore){
            printf("There are fewer cards in the player's hand than at the start: Test Failed\n\n");
            drawTestFailed++;
            passed = 0;
        }
        if(discardCopper != 0){
            printf("Copper was discarded: Test Failed\n\n");
            discardTestFailed++;
            passed = 0;
        }

        if(discardSilver != 0){
            printf("Silver was discarded: Test Failed\n\n");
            discardTestFailed++;
            passed = 0;
        }

if(passed == 1){
            printf("All Tests: Passed\n\n");
            testPassed++;
        }
   }

   return 0;
}

