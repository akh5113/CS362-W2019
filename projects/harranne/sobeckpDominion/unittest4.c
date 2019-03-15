/***************************************************************************
* Anne Harris
* CS362
* Assignmnet 3
* Unit Test 4
* Function testing: gainCard
* This file tests to see the accuracy of the gainCard function.
****************************************************************************/

/****************************************************************************
 To run this file include the following in your makefile
	unittest4: unittest4.c dominion.o rngs.o
		gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
*****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// set NOISY to 0 to exclude printf statements
#define NOISY 1

int main() {
	//set up game
	int seed = 1000;
	int numPlayers = 2;
	struct gameState cardG;
	int cards[10] = { adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine };
	int player = 0; 

	//initalize game
	initializeGame(numPlayers, cards, seed, &cardG);

	printf("TESTING: Function gainCard()\n");
	int gainCardReturn;

	//using gold to test if it the function will return -1 when gold count is 0
	//set gold supply to 0
	printf("Testing if function will return -1 when supply count is 0\n");
	cardG.supplyCount[gold] = 0;
	gainCardReturn = gainCard(gold, &cardG, 1, player);
	if (gainCardReturn == -1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}
	//set supply back for feast card
	cardG.supplyCount[gold] = 30;

	//set test flag
	int testFlag = 0;
	//set feast supply to 10
	cardG.supplyCount[feast] = 5;

	// toFlag = 0 : add to discard
	//check that discard has changed
	printf("Testing if the discard count has increased by 1\n");
	//get current discard count
	int startDiscardCount = cardG.discardCount[0];
	//using card feast
	gainCard(feast, &cardG, 0, player);
	//check for discardCount increase
	int newDiscardCount = cardG.discardCount[0];

	//printf("startDiscardCount = %d\n", startDiscardCount);
	//printf("newDiscardCount = %d\n", newDiscardCount);

	//get new discardCount
	if (newDiscardCount == (startDiscardCount + 1)) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}
	//check that card is in discard deck
	printf("Testing if the card is found within the discard deck\n");
	
	int i;
	for (i = 0; i < cardG.discardCount[0]; i++) {
		//printf("Card %d is %d\n", i, cardG.discard[0][i]);
		if (cardG.discard[0][i] == feast) {
			testFlag = 1;
		}
	}
	if (testFlag == 1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//reset flag
	testFlag = 0;

	//set supplycount for mine
	cardG.supplyCount[mine] = 5;

	// toFlag = 1 : add to deck
	//check for deck increase
	//check that card is in players deck
	//check that deck has changed
	printf("Testing if deck count has increased by 1\n");
	//get current deck count
	int startDeckCount = cardG.deckCount[0];
	//using card mine
	gainCard(mine, &cardG, 1, player);
	//check for deckCount increase
	int newDeckCount = cardG.deckCount[0];
	//get new deckCount
	if (newDeckCount == (startDeckCount + 1)) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}
	//check that card is in deck
	printf("Testing that card is within deck\n");
	
	int j;
	for (j = 0; j < cardG.deckCount[0]; j++) {
		//printf("Card %d is %d\n",j, cardG.deck[0][j]);
		if (cardG.deck[0][j] == mine) {
			testFlag = 1;
		}
	}
	if (testFlag == 1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//reset flag
	testFlag = 0;

	//set supplycount for mine
	cardG.supplyCount[steward] = 5;

	// toFlag = 2 : add to hand
	//check for hand increase
	//check that hand has changed
	printf("Testing if hand count has increased by 1\n");
	//get current hand count
	int startHandCount = cardG.handCount[0];
	//using card steward
	gainCard(steward, &cardG, 2, player);
	//check for handCount increase
	//get new handCount
	int newHandCount = cardG.handCount[0];
	if (newHandCount == (startHandCount + 1)) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}
	//check that card is in hand
	printf("Testing that card is in the hand\n");
	
	int k;
	for (k = 0; k < cardG.handCount[0]; k++) {
		if (cardG.hand[0][k] == steward) {
			testFlag = 1;
		}
	}
	if (testFlag == 1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//check that supply count has decreased
	//set supply count for village to 5
	printf("Testing if the supply count of card decreases\n");
	cardG.supplyCount[village] = 5;
	gainCard(village, &cardG, 1, player);
	if (cardG.supplyCount[village] == 4) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//testing for bad flag
	printf("Testing for behavoir when a bad flag value is passed\n");
	cardG.supplyCount[gold] = 10;
	//get current discard count
	int badFlagCount = cardG.discardCount[0];
	//using card feast
	gainCardReturn = gainCard(gold, &cardG, 555, player);
	//check for discardCount increase
	int badFlagCount2 = cardG.discardCount[0];

	//if card shows up in discard pile, it has been incorrectly set
	if (badFlagCount2 == (badFlagCount +1)) {
		printf("TEST FAILED\n");
	}
	else {
		printf("TEST PASSED\n");
	}

	return 0;
}