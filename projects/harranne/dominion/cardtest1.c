/***************************************************************************
* Anne Harris
* CS362
* Assignmnet 3
* Card Test 1
* Card testing: smithy
* This file tests to see the accuracy of the "Smithy" card. It tests for: 
*	The number of cards in the current players hand to have increased by 3
*	The number of cards in player 2's hand to stay the same
****************************************************************************/

/****************************************************************************
* To run this file include the following in your makefile
	cardtest1: cardtest1.c dominion.o rngs.o
		gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
*****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NOISY 1

int main() {

	//prepare game
	int seed = 1000;
	int numPlayer = 2;
	struct gameState cardG;
	int cards[10] = { adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine };
	int smithyPos = 1; // hard code smithy to be a position 1
	int coin_bonus = 0;

	//initalize game
	initializeGame(numPlayer, cards, seed, &cardG);

	//get number of cards in hand before testing smithy
	int handBefore = cardG.handCount[0];
	int otherBefore = cardG.handCount[1];

	//get number of cards in current players deck
	int deckBefore = cardG.deckCount[0];

	//get number of victory cards
	int estateBefore = supplyCount(estate, &cardG);
	int duchyBefore = supplyCount(duchy, &cardG);
	int provinceBefore = supplyCount(province, &cardG);

	//get number of supply cards for each kingdom card
	int preKSupply[10];
	int a;
	for (a = 0; a < 10; a++) {
		preKSupply[a] = cardG.supplyCount[cards[a]];
	}

	printf("TESTING: card SMITHY\n");

	//play the smithy card via cardEffect which will call the individual function
	//smithy is enum card number 13
	int smithyPlay = cardEffect(smithy, -1, -1, -1, &cardG, smithyPos, &coin_bonus);

	//printf("smithy played.\n");
	printf("smithyPlay Value = %d\n", smithyPlay);

	//check that the current players card number is 3 additional to what it had
	int handAfter = cardG.handCount[0];
	//check that other players have the same amount of cards
	int otherafter = cardG.handCount[1];

	// The player should have two more cards than they began with, even though smithy draws 3, 
	// the player will have discareded as part of the card so it will be the 
	// original hand count + 3 (smithy) - 1 (discard) for a difference of 2

	//Print results
	printf("Testing Current player has 2 addtional cards after discard\n");

#if(NOISY == 1)
	printf("Current player hand count before smithy is: %d\n", handBefore);
	printf("Current player hand count after smithy is: %d\n", handAfter);
#endif

	if ((handAfter - handBefore) == 2) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}
	//test for player 2
	printf("Testing Player 2 has same amount of cards\n");
#if(NOISY == 1)
	printf("Player 2 hand count before smithy is: %d\n", otherBefore);
	printf("Player 2 hand count after smithy is: %d\n", otherafter);
#endif
	if (otherBefore == otherafter) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}
	

	//check for 3 cards coming from own pile
	int deckAfter = cardG.deckCount[0];
	printf("Testing for current players +3 cards came from own deck\n");
#if(NOISY == 1)
	printf("Number of cards in deck before smithy is: %d\n", deckBefore);
	printf("Number of cards in deck after smithy is: %d\n", deckAfter);
#endif
	//if ((deckAfter - deckBefore) == (handBefore-handAfter)) {
	if((deckBefore - deckAfter) == 3){
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}	

	//check for no change in victory card pile
	//get number of victory cards
	int estateAfter = supplyCount(estate, &cardG);
	int duchyAfter = supplyCount(duchy, &cardG);
	int provinceAfter = supplyCount(province, &cardG);
	printf("TESTING: Victory cards have not changed\n");
#if (NOISY ==1)
	printf("estate before: %d estate after: %d\n", estateBefore, estateAfter);
	printf("dutchy before: %d dutchy after: %d\n", duchyBefore, duchyAfter);
	printf("province before: %d province afer: %d\n", provinceBefore, provinceAfter);
#endif
	if (estateBefore != estateAfter || duchyBefore != duchyAfter || provinceBefore != provinceAfter) {
		printf("TEST FAILED\n");
	}
	else {
		printf("TEST PASSED\n");
	}


	//check for not change in kingdom card piles
	printf("Testing for no change in kindom card supply\n");
	int checkSupply;
	int flag = 0;
	for (a = 0; a < 10; a++) {
		checkSupply = cardG.supplyCount[a];
		if (checkSupply != preKSupply[a]) {
			flag = 1; 
		}
	}
	if (flag == 1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}



	return 0;
}
