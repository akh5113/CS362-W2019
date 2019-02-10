/***************************************************************************
* Anne Harris
* CS362
* Assignmnet 3
* Unit Test 2
* Function testing: numHandCards
* This file tests to see the accuracy of the numHandCards function. It tests for:
*	The function returning the correct number of cards in the players hand
****************************************************************************/

/****************************************************************************
* To run this file include the following in your makefile
	unittest2: unittest2.c dominion.o rngs.o
		gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
*****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
	//prepare game
	int seed = 1000;
	int numPlayers = 2;
	struct gameState cardG;
	int cards[10] = { adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine };

	//initalize game
	initializeGame(numPlayers, cards, seed, &cardG);

	printf("TESTING: Function numHandCards()\n");

	//get number of cards before test
	//set whose turn for player 1
	cardG.whoseTurn = 0;
	//:wint p1Cards = numHandCards(&cardG);
	cardG.handCount[0] = 2;
	int p1Cards = 2;
	//set whose turn for player 2
	cardG.whoseTurn = 1;
	//int p2Cards = numHandCards(&cardG);
	cardG.handCount[1] = 2;
	int p2Cards = 2;

	//add cards
	cardG.handCount[0]++;
	cardG.handCount[1]++;

	//call function
	//set whose turn for player 1
	cardG.whoseTurn = 0;
	int p1CardsAdd = numHandCards(&cardG);
	//set whose turn for player 2
	cardG.whoseTurn = 1;
	int p2CardsAdd = numHandCards(&cardG);

	//remove cards
	cardG.handCount[0]--;
	cardG.handCount[1]--;

	//call function
	//set whose turn for player 1
	cardG.whoseTurn = 0;
	int p1CardsSub = numHandCards(&cardG);
	//set whose turn for player 2
	cardG.whoseTurn = 1;
	int p2CardsSub = numHandCards(&cardG);

	//print results
	printf("Number of carsd in P1's hand at start: %d\n", p1Cards);
	printf("Number of cards in P2's hand at start: %d\n", p2Cards);
	printf("Number of cards in P1's hand after addition: %d\n", p1CardsAdd);
	printf("Number of cards in P2's hand after addition: %d\n", p2CardsAdd);
	//test for if the number has increased by 1
	if (p1CardsAdd == (p1Cards + 1)) {
		printf("P1 TEST PASSED\n");
	}
	else {
		printf("P1 TEST FAILED\n");
	}
	if (p2CardsAdd == (p2Cards + 1)) {
		printf("P2 TEST PASSED\n");
	}
	else {
		printf("P2 TEST FAILED\n");
	}
	printf("Number of cards in P1's hand after subration: %d\n", p1CardsSub);
	printf("Number of cards in P2's hand after subtraction: %d\n", p2CardsSub);
	//test for if the number has decreased by 1 (back to original number)
	if (p1CardsSub == (p1Cards)) {
		printf("P1 TEST PASSED\n");
	}
	else {
		printf("P1 TEST FAILED\n");
	}
	if (p2CardsSub == (p2Cards)) {
		printf("P2 TEST PASSED\n");
	}
	else {
		printf("P2 TEST FAILED\n");
	}



	return 0;
}