/****************************************************************
* Anne Harris
* CS 362 - 400
* Assignment 4 - Random Test Generator
* Card: Smithy
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int checkSmithy(int currentPIn, int numPlayersIn, struct gameState * gameIn, int handPosIn, int *checkHand, int *checkDeck, int *checkDiscard) {
	int bonus = 0;

	//Tester Variables
	int testsPassed = 0;
	int testsFailed = 0;

	//get the counts for effected variables
	//int player = gameIn->whoseTurn;
	int player = currentPIn;
	int preHandCount = gameIn->handCount[player];
	int preDeckCount = gameIn->deckCount[player];
	int preDiscardCount = gameIn->discardCount[player];

	/*
	printf("hand pos in = %d\n", handPosIn);
	printf("hand count = %d\n", preHandCount);
	printf(" deck count = %d\n", preDeckCount);
	printf("discardCount = %d\n", preDiscardCount);
	*/
	// call the smithy function
	int result = cardEffect(smithy, -1, -1, -1, gameIn, handPosIn, &bonus);

	//assert that value returned was 0
	assert(result == 0);

	//test post conditions
	//check player will have net two additional cards
	//printf("Pre hand count = %d\n", preHandCount);
	//printf("gameIn->handCount[player] = %d\n", gameIn->handCount[player]);
	if (gameIn->handCount[player] != preHandCount + 2) {
		testsFailed++;
		*checkHand = 1;
	}
	else {
		testsPassed++;
	}
	//printf("preDiscardCount = %d\n", preDiscardCount);
	//printf("gameIn->discardCount[player] %d\n", gameIn->discardCount[player]);
	
	//check player will have one additional discard
	if (gameIn->discardCount[player] == preDiscardCount + 1) {
		testsFailed++;
		*checkDiscard = 1;
	}
	else {
		testsPassed++;
	}

	//check deck count will have decrased by 2
	if (gameIn->deckCount[player] == preDeckCount - 2) {
		testsPassed++;
	}
	else {
		testsFailed++;
		*checkDeck = 1;
	}

	//printf("Number of tests passed: %d\n", testsPassed);
	//printf("Number of tests failed: %d\n", testsFailed);

	if (testsFailed > 0) {
		return 1;
	}
	else {
		return 0;
	}

}

int main() {
	printf("TESTING CARD: Smithy\n");
	//smithy parameters include: gameState, numPlayers, handPos

	//initiate variables
	int numPlayers; //number of players in the game
	int handPosition;
	int currentPlayer;

	//set up game struct
	struct gameState game; 


	//set up randomization
	SelectStream(2);
	PutSeed(3);

	//tester variables
	int failedHand = 0;
	int failedDeck = 0;
	int failedDiscard = 0;
	int failedTests = 0;
	int result = 0;

	//loop for 2000 tests
	// used implementation of testDrawCard.c as a starting point
	int i, j;
	for (i = 0; i < 2000; i++) {
		//checker variables for failed test response
		int checkHand = 0;
		int checkDeck = 0;
		int checkDiscard = 0;

		//set game state to be random
		for (j = 0; j < sizeof(struct gameState); j++) {
			//assigns each byte of the game state (game) to a random value 
			((char*)&game)[j] = floor(Random() * 256);
		}
		//set number of players to be random up to the max
		numPlayers = floor(Random() * MAX_PLAYERS); 
		currentPlayer = floor(Random() * numPlayers);
		game.whoseTurn = currentPlayer; 
		//game.whoseTurn = floor(Random() * numPlayers);
		game.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		game.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		game.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		game.playedCardCount = 0;
		//set cards in hand
		int a;
		for (a = 0; a < game.handCount[currentPlayer]; a++) {
			game.hand[currentPlayer][a] = floor(Random() * 26);  //there are 26 possible cards
		}
		//set hand position to be random up to 10
		handPosition = floor(Random() * game.handCount[currentPlayer]);

		//call function
		result = checkSmithy(currentPlayer, numPlayers, &game, handPosition, &checkHand, &checkDeck, &checkDiscard);

		//add any failed tests to tally
		failedHand += checkHand;
		failedDeck += checkDeck;
		failedDiscard += checkDiscard;
		failedTests = failedTests + result;
	}

	//print results
	printf("Test - checking to see if hand count has net 2 increase, test failed %d times\n", failedHand);
	printf("Test - checking to see if deck count has decrased by 2, test failed %d times\n", failedDeck);
	printf("Test - checking to see if discard pile has increased by 1, test failed %d times\n", failedDiscard);
	printf("At least one test failed %d out of 2000 calls to the card's function\n", failedTests);

	return 0;
}