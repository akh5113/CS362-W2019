/***************************************************************************
* Anne Harris
* CS362
* Assignmnet 3
* Unit Test 3
* Function testing: whoseTurn
* This file tests to see the accuracy of the whose turn function. 
****************************************************************************/

/****************************************************************************
* To run this file include the following in your makefile
	unittest3: unittest3.c dominion.o rngs.o
		gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
*****************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
	//set up game
	int seed = 1000;
	int numPlayers = MAX_PLAYERS;
	struct gameState cardG;
	int cards[10] = { adventurer, smithy, village, great_hall, council_room, feast, gardens, minion, steward, mine };
	int flag = 0;

	//initalize game
	initializeGame(numPlayers, cards, seed, &cardG);

	printf("TESTING: function whoseTurn()\n");

	//begin tests
	int returnedPlayer;
	int i; 
	for (i = 0; i < MAX_PLAYERS; i++) {
		//set turn to equal i
		cardG.whoseTurn = i;
		//test the function
		returnedPlayer = whoseTurn(&cardG);
		if (returnedPlayer != i) {
			printf("TEST FAILED\n");
			flag = 1;
		}
	}

	if (flag == 0) {
		printf("TEST PASSED\n");
	}

	return 0;
}