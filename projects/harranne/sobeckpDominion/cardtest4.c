/***************************************************************************
* Anne Harris
* CS362
* Assignmnet 3
* Card Test 4
* Card testing: council room
* This file tests to see the accuracy of the "council room" card. It tests for:
*
****************************************************************************/

/****************************************************************************
* To run this file include the following in your makefile
	cardtest4: cardtest4.c dominion.o rngs.o
		gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
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
	int numPlayer = MAX_PLAYERS;
	struct gameState cardG;
	int cards[10] = { adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine };
	int coin_bonus = 0;
	int councilRoomPos = 1;
	int flag = 0;


	//initalize game
	initializeGame(numPlayer, cards, seed, &cardG);
	
	//set current player
	cardG.whoseTurn = 0;

	//set number of actions to 1
	cardG.numBuys = 1;

	//get before values
	int beforeDeck[MAX_PLAYERS];
	int beforeHand[MAX_PLAYERS];

	int i;
	// get deck count
	for (i = 0; i < MAX_PLAYERS; i++) {
		beforeDeck[i] = cardG.deckCount[i];
	}
	// get hand count
	for (i = 0; i < MAX_PLAYERS; i++) {
		beforeHand[i] = cardG.handCount[i];
	}

	//get number of supply cards for each kingdom card
	int preKSupply[10];
	int a;
	for (a = 0; a < 10; a++) {
		preKSupply[a] = cardG.supplyCount[cards[a]];
	}

	//get discard count
	/*
	for (i = 0; i < MAX_PLAYERS; i++) {
		beforeDiscard[i] = cardG.discardCount[i];
	}*/

	//victory cards
	int estateBefore, duchyBefore, provinceBefore;
	estateBefore = cardG.supplyCount[estate];
	duchyBefore = cardG.supplyCount[duchy];
	provinceBefore = cardG.supplyCount[province];

	printf("TESTING: card COUNCIL_ROOM\n");

	//call function
	cardEffect(council_room, -1, -1, -1, &cardG, councilRoomPos, &coin_bonus);

	//test after function has been called

	//check for player 1 to have +4 cards
	// net of 3 additional cards.. add 4 and subtract 1 for discard
	printf("Testing if player one has +4 cards\n");
#if (NOISY == 1)
	printf("Number of cards in hand before play: %d\n", beforeHand[0]);
	printf("Number of cards in hand after play: %d\n", cardG.handCount[0]);
#endif
	if (cardG.handCount[0] == (beforeHand[0] + 3)) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//check for player 1 to have +1 buy
	printf("Testing if there is +1 buy\n");
	if (cardG.numBuys == 2) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//check for all other players to have an extra card in draw
	printf("Testing if other players each have an additional card in hand\n");
	for (i = 1; i < MAX_PLAYERS; i++) {
		//printf("Player %d hand count before: %d and after %d\n", i+1, beforeHand[i], cardG.handCount[i]);
		if (cardG.handCount[i] != (beforeHand[i] + 1)) {
			flag = 1;
		}
	}
	if (flag == 0) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}
	//reset flag
	flag = 0;
	
	//test for vicotry cards to be unchanged
	printf("Testing for Victory Cards to be unchanged\n");
	//check victory piles are unchangeds
	if (estateBefore != cardG.supplyCount[estate]) {
		printf("TEST FAILED\n");
	}
	else if (duchyBefore != cardG.supplyCount[duchy]) {
		printf("TEST FAILED\n");
	}
	else if (provinceBefore != cardG.supplyCount[province]) {
		printf("TEST FAILED\n");
	}
	else {
		printf("TEST PASSED\n");
	}

	//check kingdom cards supply are unchanged
	printf("Testing for no change in kindom card supply\n");
	int checkSupply;
	int flag1 = 0;
	for (a = 0; a < 10; a++) {
		checkSupply = cardG.supplyCount[a];
		if (checkSupply != preKSupply[a]) {
			flag1 = 1;
		}
	}
	if (flag1 == 1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	return 0;
}
