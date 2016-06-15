#include "PTHeader.h"

using namespace std;


int main() {
	// Create an instance of the game class

	GameState newGame(13,5);

	// Loop to handle turns until a winner is decided
	while (newGame.getWinningPlayer() == 'n')
	{
		newGame.takeTurn();
	}

	// Declare the winner
	newGame.announceWinner();
	std::cin.get();

	return 0;

}