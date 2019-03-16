/***************************************************************************
* Anne Harris
* CS362
* Assignmnet 3
* Unit test 1
* Function testing: fullDeckCount()
****************************************************************************/

/****************************************************************************
* To run this file individually include the following in your makefile
	unittest1: unittest1.c dominion.o rngs.o
		gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
*****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// set NOISY to 0 to exclude extra printf statements
// set NOISY to 1 to include extra printf statements
#define NOISY 0


int main() {
	//prepare game
	int seed = 1000;
	int numPlayers = 2;
	struct gameState cardG;
	int cards[10] = { adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine };
	int player = 0;
	int card;

	//initalize game
	initializeGame(numPlayers, cards, seed, &cardG);
	int returnedDeckCount = 0;

	printf("TESTING: Function getFullCount()\n");


	printf("Testing if function returns correct int\n");
	//check that function returns the correct count
	card = great_hall; //enum 16

#if (NOISY == 1)
	printf("Number of cards in deck = %d\n", cardG.deckCount[player]);
	printf("Number of cards in hand = %d\n", cardG.handCount[player]);
	printf("Number of cards in discard = %d\n", cardG.discardCount[player]);
	printf("Last card in deck is: %d\n", cardG.deck[player][cardG.deckCount[player]]);
	printf("Last card in hand is: %d\n", cardG.hand[player][cardG.handCount[player]]);
	printf("Last card in discard is: %d\n", cardG.discard[player][cardG.discardCount[player]]);
#endif

	//attempt to set up manually
	//set up so player has one great_hall card in deck, hand and discard
	/*
	cardG.deck[player][cardG.deckCount[player]] = card;
	cardG.hand[player][cardG.handCount[player]] = card;
	cardG.discard[player][cardG.discardCount[player]] = card;
	*/
	//use gain card to add a card
	gainCard(card, &cardG, 1, player);
	gainCard(card, &cardG, 2, player);
	gainCard(card, &cardG, 0, player);

#if (NOISY == 1)
	printf("Number of cards in deck = %d\n", cardG.deckCount[player]);
	printf("Number of cards in hand = %d\n", cardG.handCount[player]);
	printf("Number of cards in discard = %d\n", cardG.discardCount[player]);
	printf("Last card in deck is: %d\n", cardG.deck[player][cardG.deckCount[player]]);
	printf("Last card in hand is: %d\n", cardG.hand[player][cardG.handCount[player]]);
	printf("Last card in discard is: %d\n", cardG.discard[player][cardG.discardCount[player]]);
#endif

	//call function
#if (NOISY == 1)
	int a;
	for (a = 0; a < cardG.handCount[player]; a++) {
		printf("Card in hand: %d\n", cardG.hand[player][cardG.handCount[player]]);
	}
	for (a = 0; a < cardG.deckCount[player]; a++) {
		printf("Card in deck: %d\n", cardG.deck[player][cardG.deckCount[player]]);
	}
	for (a = 0; a < cardG.discardCount[player]; a++) {
		printf("Card in discard: %d\n", cardG.discard[player][cardG.discardCount[player]]);
	}
#endif

	returnedDeckCount = fullDeckCount(player, card, &cardG);

#if (NOISY == 1)
	printf("returnedDeckCount = %d\n", returnedDeckCount);
#endif
	if (returnedDeckCount == 3) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	printf("Testing for correct count in deck pile\n");
	//check that it has the correct count in players deck
	int deckCount = 0;
	int i = 0;
	for (i = 0; i < cardG.deckCount[player]; i++) {
		//printf("Card = %d\n", cardG.deck[player][i]);
		if (cardG.deck[player][i] == card) {
			deckCount++;
		}
	}
	if (deckCount == 1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//check that it has the correct count in players hand
	printf("Testing for correct count in hand pile\n");
	int handCount = 0;
	int j = 0;
	for (j = 0; j < cardG.handCount[player]; j++) {
		//printf("Card = %d\n", cardG.hand[player][j]);
		if (cardG.hand[player][j] == card) {
			handCount++;
		}
	}
	if (handCount == 1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}

	//check that it has the correct count in players discard
	printf("Testing for correct count in discard pile\n");
	int discardCount = 0;
	int k = 0;
	for (k = 0; k < cardG.discardCount[player]; k++) {
		//printf("Card: %d\n", cardG.discard[player][i]);
		if (cardG.discard[player][k] == card) {
			discardCount++;
		}
	}
#if (NOISY == 1)
	printf("discardCount = %d\n", discardCount);
#endif
	if (discardCount == 1) {
		printf("TEST PASSED\n");
	}
	else {
		printf("TEST FAILED\n");
	}


	return 0;
}