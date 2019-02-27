/****************************************************************
* Anne Harris
* CS 362 - 400
* Assignment 4 - Random Test Generator
* Card: Village
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int checkVillage(int currentPIn, int numPlayersIn, struct gameState * gameIn, int handPosIn, int *checkHand, int *checkActions, int *checkDiscard) {
	int bonus = 0;
	//tester variables
	int testsPassed = 0;
	int testsFailed = 0;
	
	// get starting variables
	int player = gameIn->whoseTurn;
	int preHandCount = gameIn->handCount[player];
	int preDiscardCount = gameIn->discardCount[player];
	int preNumActions = gameIn->numActions;

	//call the village card via the cardEffect function
	int result = cardEffect(village, -1, -1, -1, gameIn, handPosIn, &bonus);

	//assert that the function returned 0 as expected
	assert(result == 0);

	//compare results
	//hand count should have a net equal to the original, +1 card -1 discard
	if (preHandCount == gameIn->handCount[player]) {
		testsPassed++;
	}
	else {
		testsFailed++;
		*checkHand = 1;
	}
	//check for an increase of two actions
	if (preNumActions+2 == gameIn->numActions) {
		testsPassed++;
	}
	else {
		testsFailed++;
		*checkActions = 1;
	}
	//check for the discard pile to have increased
	if (preDiscardCount + 1 == gameIn->discardCount[player]) {
		testsPassed++;
	}
	else {
		testsFailed++;
		*checkDiscard = 1;
	}

	//return 1 if at least one test failed
	if (testsFailed > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	printf("TESTING CARD: Village\n");
	//village parameters include: gameState, current player, handPos
	
	//tester variables
	int failedHand = 0;
	int failedActions = 0;
	int failedDiscard = 0;
	int result = 0;
	int failedTests = 0;

	//initiate variables
	int numPlayers; //number of players in the game
	int handPosition;
	int currentPlayer;

	//set up game struct
	struct gameState game;

	//set up randomization
	SelectStream(2);
	PutSeed(3);

	//loop for 2000 tests
	// used implementation of testDrawCard.c as a starting point
	int i, j;
	for (i = 0; i < 2000; i++) {
		//checker variables for failed test response
		int checkHand = 0;
		int checkActions = 0;
		int checkDiscard = 0;

		//set game state to be random
		for (j = 0; j < sizeof(struct gameState); j++) {
			//assigns each byte of the game state (game) to a random value 
			((char*)&game)[j] = floor(Random() * 256);
		}
		//make game realistic
		//set number of players to be random up to the max
		numPlayers = floor(Random() * MAX_PLAYERS);
		currentPlayer = floor(Random() * numPlayers);
		game.whoseTurn = currentPlayer;
		game.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		game.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		game.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		//set cards in hand
		int a;
		for (a = 0; a < game.handCount[currentPlayer]; a++) {
			game.hand[currentPlayer][a] = floor(Random() * 26); //there are 26 possible cards
		}
		//set hand position to be random up to 10
		handPosition = floor(Random() * game.handCount[currentPlayer]);
		//call function
		result = checkVillage(currentPlayer, numPlayers, &game, handPosition, &checkHand, &checkActions, &checkDiscard);
		//add any failed tests to tally
		failedHand += checkHand;
		failedActions += checkActions;
		failedDiscard += checkDiscard;
		failedTests = failedTests + result; 
	}

	//print results
	printf("Test - checking to see if hand count has net 0 increase, test failed %d times\n", failedHand);
	printf("Test - checking to see if number of Actions has increased by 2, test failed %d times\n", failedActions);
	printf("Test - checking to see if discard pile has increased by 1, test failed %d times\n", failedDiscard);
	printf("At least one test failed %d out of 2000 calls to the card's function\n", failedTests);

	return 0;
}