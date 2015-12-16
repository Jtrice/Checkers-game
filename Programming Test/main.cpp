#include <iostream>
#include "PTHeader.h"

using namespace std;


int main() {
	// Create an instance of the game class
	GameState newGame;

	// Loop to handle turns until a winner is decided
	while (newGame.winningPlayer == 'n')
	{
		newGame.takeTurn();
	}

	// Declare the winner
	newGame.announceWinner();

	return 0;

}