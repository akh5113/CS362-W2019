/***************************************************************************
* Anne Harris
* CS362
* Assignmnet 3
* Card Test 2
* Card testing: adventurer
* This file tests to see the accuracy of the "Adventurer" card. It tests for:
*	
****************************************************************************/

/****************************************************************************
* To run this file include the following in your makefile
	cardtest2: cardtest2.c dominion.o rngs.o
		gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
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
	int adventurerPos = 1; // hard code adventurer to be a position 1
	int coin_bonus = 0;

	//initalize game
	initializeGame(numPlayer, cards, seed, &cardG);

	//get before stats
	int handCountBefore = cardG.handCount[0];

	//get number of victory cards
	int estateBefore = supplyCount(estate, &cardG);
	int duchyBefore = supplyCount(duchy, &cardG);
	int provinceBefore = supplyCount(province, &cardG);

	//get number of supply cards for each
	int preKSupply[10];
	int a;
	for (a = 0; a < 10; a++) {
		preKSupply[a] = cardG.supplyCount[cards[a]];
	}

	printf("Testing card: ADVENTURER\n");

	//check current hand for number of treasure cards
	int numTreasure = 0;
	int j;
	for (j = 0; j < cardG.handCount[0]; j++) {
		if (cardG.hand[0][j] >= 4 && cardG.hand[0][j] <= 6) {
			numTreasure++;
		}
	}
	printf("numTreasure = %d\n", numTreasure);

	//call Adventurer card
	//adventurer is enum card number 7
	cardEffect(adventurer, -1, -1, -1, &cardG, adventurerPos, &coin_bonus);

	//check to see if the card is checking for a shuffle

	//check for two additional treasure cards
	printf("Testing for two additional treasure cards in hand\n");
	int numAddTreasure = 0;
	int discardPile = 0;
	int i;
	for (i=0; i < cardG.handCount[0]; i++) {
		if (cardG.hand[0][i] >= 4 && cardG.hand[0][i] <= 6) {
			numAddTreasure++; //if card is a treasure card, incrase count
		}
		/*
		else {
			discardPile++; //card was discarded
		}*/
	}

#if(NOISY==1)
	printf("number of treasure cards total: %d\n", numAddTreasure);
	printf("number of cards discarded %d\n", discardPile);
#endif

	if ((numAddTreasure - numTreasure) == 2) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}
	

	//check hand count
	printf("Testing for number of cards in hand\n");
	int handCountAfter = cardG.handCount[0];
#if(NOISY ==1)
	printf("handCountBefore = %d\n", handCountBefore);
	printf("handCountAfter = %d\n", handCountAfter);
#endif
	if ((handCountAfter - handCountBefore) == 2) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	/*
	//check for other cards discarded 
	printf("Testing to see if other cards are discareded\n");
	int cardsDiscarded = cardG.discardCount[0];
#if(NOISY ==1)
	printf("cardG.discardCount[0] = %d\n", cardsDiscarded);
	printf("discardPile = %d\n", discardPile);
#endif
	if (cardsDiscarded == discardPile) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}*/


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

	//check if deck needs to be shuffled
	printf("Testing behavior when deck is empty\n");
	//set players deck count to 0
	cardG.deckCount[0] = 0;
	cardEffect(adventurer, -1, -1, -1, &cardG, adventurerPos, &coin_bonus);
	int badHandAfter = cardG.handCount[0];
#if(NOISY ==1)
	printf("number of cards in hand before smithy is called: %d\n", handCountAfter);
	printf("number of cards in hand after deck is empty: %d\n", badHandAfter);
#endif
	//expect hand count to not change
	if (badHandAfter == handCountAfter) {
		printf("TEST FAILED\n");
	}
	else {
		printf("TEST PASSED\n");
	}

	return 0;
}