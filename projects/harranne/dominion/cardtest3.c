/***************************************************************************
* Anne Harris
* CS362
* Assignmnet 3
* Card Test 3
* Card testing: village
* This file tests to see the accuracy of the "village" card. It tests for:
****************************************************************************/

/****************************************************************************
* To run this file include the following in your makefile
	cardtest3: cardtest3.c dominion.o rngs.o
		gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	int coin_bonus = 0;
	int villagePos = 1;

	//initalize game
	initializeGame(numPlayer, cards, seed, &cardG);

	//set number of actions to 1
	cardG.numActions = 1; 

	//get before values
	int p1beforeHand; // p1beforeDeck, p1beforeDiscard;
	int p2beforeHand; //p2beforeDeck, p2beforeDiscard;
	int estateBefore, duchyBefore, provinceBefore;


	//player 1
	//p1beforeDeck = cardG.deckCount[0];
	//p1beforeDiscard = cardG.discardCount[0];
	p1beforeHand = cardG.handCount[0];

	//player 2
	//p2beforeDeck = cardG.deckCount[1];
	//p2beforeDiscard = cardG.discardCount[1];
	p2beforeHand = cardG.handCount[1];

	//victory cards
	estateBefore = cardG.supplyCount[estate];
	duchyBefore = cardG.supplyCount[duchy];
	provinceBefore = cardG.supplyCount[province];

	//get number of supply cards for each kingdom card
	int preKSupply[10];
	int a;
	for (a = 0; a < 10; a++) {
		preKSupply[a] = cardG.supplyCount[cards[a]];
	}

	printf("TESTING: card VILLAGE\n");

	//call card effect
	cardEffect(village, -1, -1, -1, &cardG, villagePos, &coin_bonus);

	//check for plus one card
	//should end up with the same count, as you gained a card but also discarded
	printf("Testing for additional card in hand\n");
#if (NOISY ==1)
	printf("Number of cards in hand before call %d\n", p1beforeHand);
	printf("Number of cards in hand after call %d\n", cardG.handCount[0]);
#endif
	if (cardG.handCount[0] == (p1beforeHand)) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//check for plus two actions
	printf("Testing for additional actions\n");
	if(cardG.numActions == 3) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//check player 2 is the unchanged
	printf("Checking for player 2's hand to be unchanged\n");
	if (cardG.handCount[1] == p2beforeHand) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//check victory piles are unchanged
	//int testOK = 0;
	printf("Testing for victory cards to be unchanged\n");
#if (NOISY ==1)
	printf("estate before: %d estate after: %d\n", estateBefore, cardG.supplyCount[estate]);
	printf("dutchy before: %d dutchy after: %d\n", duchyBefore, cardG.supplyCount[duchy]);
	printf("province before: %d province afer: %d\n", provinceBefore, cardG.supplyCount[province]);
#endif
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

	//test for discard in played pile
	printf("Testing for Village card in played cards deck\n");
	int flag = 0;
	int i;
	for (i = 0; i < cardG.playedCardCount; i++) {
		if (cardG.playedCards[i] == village) {
			printf("card in played cards is: %d\n", cardG.playedCards[i]);
			flag++;
		}
	}
	if (flag == 0) {
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