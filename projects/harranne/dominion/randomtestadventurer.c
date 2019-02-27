/****************************************************************
* Anne Harris
* CS 362 - 400
* Assignment 4 - Random Test Generator
* Card: Adventurer
****************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int checkAdventurer(int currentPlayerIn, struct gameState * gameIn, int handPosIn, int *checkCount, int *checkTreasure, int *checkDiscard) {
	int bonus = 0;

	//tester variables
	int testsPassed = 0;
	int testsFailed = 0;

	//get current variables
	int preDiscardCount = gameIn->discardCount[currentPlayerIn];
	int preHandCount = gameIn->handCount[currentPlayerIn];
	int preDeckCount = gameIn->deckCount[currentPlayerIn];
	//get the number of treasure cards in the hand
	int preTreasureCards = 0;
	int i;
	for (i = 0; i < preHandCount; i++) {
		//printf("card = %d\n", gameIn->hand[currentPlayerIn][i]);
		if (gameIn->hand[currentPlayerIn][i] >= 4 && gameIn->hand[currentPlayerIn][i] <= 6)
			preTreasureCards++;
	}

	//call the cards function via card effect
	int result = cardEffect(adventurer, -1, -1, -1, gameIn, handPosIn, &bonus);

	//assert that the function returned normally
	assert(result == 0);

	//check that hand count is +2 cards 
	int postHandCount = gameIn->handCount[currentPlayerIn];
	//printf("preHandCount = %d\n", preHandCount);
	//printf("postHandCount = %d\n", postHandCount);
	if (postHandCount == preHandCount + 2) {
		testsPassed++;
	}
	else {
		testsFailed++;
		*checkCount = 1;
	}

	// check that the additional two cards in hand are treasure cards
	int postTreasureCards = 0;
	int j;
	for (j = 0; j < postHandCount; j++) {
		if (gameIn->hand[currentPlayerIn][j] >= 4 && gameIn->hand[currentPlayerIn][j] <= 6)
			postTreasureCards++;
	}
	//printf("preTreasureCards = %d\n", preTreasureCards);
	//printf("postTreasureCards = %d\n", postTreasureCards);
	if (postTreasureCards == preTreasureCards + 2) {
		testsPassed++;
	}
	else {
		testsFailed++;
		*checkTreasure = 1;
	}

	//check discard pile for additional cards
	//discard pile should have the deck difference minus two, because two treasure cards from deck should be in hand

	//get post deck count
	int postDeckCount = gameIn->deckCount[currentPlayerIn];
	//printf("pre deck count: %d\n", preDeckCount);
	//printf("post deck count: %d\n", postDeckCount);

	//get the difference between the pre and post deck counts
	int deckDiff = preDeckCount - postDeckCount;

	//get post discard pile count
	int postDiscardCount = gameIn->discardCount[currentPlayerIn];
	//printf("pre discard count: %d\n", preDiscardCount);
	//printf("post discard count: %d\n", postDiscardCount);

	//get the difference between the pre and post discard count
	int discardDiff = postDiscardCount - preDiscardCount;

	//printf("deck diff = %d\n", deckDiff);
	//printf("discard dif = %d\n", discardDiff);

	if ((deckDiff-2) == discardDiff) {
		testsPassed++;
	}
	else{
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
	printf("TESTING CARD: Adventurer\n");
	//adventurer parameters include:  game state, current player

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
	int failedTreasure = 0;
	int failedDiscard = 0;
	int failedTests = 0;
	int result = 0;

	//loop for 2000 tests
	// used implementation of testDrawCard.c as a starting point
	int i, j;
	for (i = 0; i < 2000; i++) {
		//checker variables for failed test response
		int checkHand = 0;
		int checkTreasure = 0;
		int checkDiscard = 0;

		//set game state to be random
		for (j = 0; j < sizeof(struct gameState); j++) {
			//assigns each byte of the game state (game) to a random value 
			((char*)&game)[j] = floor(Random() * 256);
		}
		//refine variables that matter to the game working
		//set number of players to be random up to the max
		numPlayers = floor(Random() * MAX_PLAYERS);
		//set current player to be one from the total number of players
		currentPlayer = floor(Random() * numPlayers);
		// set the whos turn game state to be the current player
		game.whoseTurn = currentPlayer;
		//set the various deck counts
		game.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		game.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		game.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		// no cards will have been played yet in the game
		game.playedCardCount = 0;
		//set cards in hand to choose between 0-26 for the enum cards
		int a;
		for (a = 0; a < game.handCount[currentPlayer]; a++) {
			game.hand[currentPlayer][a] = floor(Random() * 26); // there are 26 possible cards
		}
		//set cards in deck to choose between 0-26 for the enum cards
		int d;
		for (d = 0; d < game.deckCount[currentPlayer]; d++) {
			game.deck[currentPlayer][d] = floor(Random() * 26); // there are 26 possible cards
		}
		//set hand position to be random up to the current hand count
		handPosition = floor(Random() * game.handCount[currentPlayer]);
		//call function
		result = checkAdventurer(currentPlayer, &game, handPosition, &checkHand, &checkTreasure, &checkDiscard);
		//add any failed tests to tally
		failedHand += checkHand;
		failedTreasure += checkTreasure;
		failedDiscard += checkDiscard;
		failedTests += result;
	}

	//print results
	printf("Test - checking to see if hand count has increased by 2, test failed %d times\n", failedHand);
	printf("Test - checking to see if additional cards are treasure cards, test failed %d times\n", failedTreasure);
	printf("Test - checking to see if discard pile has appropriate number of cards, test failed %d times\n", failedDiscard);
	printf("At least one test failed %d out of 2000 calls to the card's function\n", failedTests);

	return 0;
}