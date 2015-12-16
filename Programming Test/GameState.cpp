#define ROWS 8
#define COLS 8

#include "PTHeader.h"
#include <iostream>
#include <sstream>


GameState::GameState() {
	// Initialize the board for play
	gameBoard.at(0) = { 'b','i','b','i','b','i','b','i' };
	gameBoard.at(1) = { 'i','b','i','b','i','b','i','b' };
	gameBoard.at(2) = { 'b','i','b','i','b','i','b','i' };
	gameBoard.at(3) = { 'i','o','i','o','i','o','i','o' };
	gameBoard.at(4) = { 'o','i','o','i','o','i','o','i' };
	gameBoard.at(5) = { 'i','r','i','r','i','r','i','r' };
	gameBoard.at(6) = { 'r','i','r','i','r','i','r','i' };
	gameBoard.at(7) = { 'i','r','i','r','i','r','i','r' };

	// Set current player to black and winning player to none
	currentPlayer = 'b';
	winningPlayer = 'n';

	// Display the starting board
	displayBoard();
	std::cout << "\nPlayer is b, Computer is r\n";
}


// Swap which player's turn it is
char GameState::swapPlayer() {
	if (currentPlayer == 'b')
		currentPlayer = 'r';
	else
		currentPlayer = 'b';
	return currentPlayer;
}


// Return the current player's opponent
char GameState::opponent() {
	if (currentPlayer == 'b')
		return 'r';
	else
		return 'b';
}

// Check that the player's move is valid. If it is, make the move and return true. Else return false. 
bool GameState::playerMove() {
	// Variables to hold player's move
	int inputRow;
	char inputCol;
	int row;
	int col;
	std::string input;
	int locationRow;
	int locationColumn;
	std::string locInput;

	// Get player's piece
	std::cout << "Input the row and column of the piece to move: ";
	std::getline(std::cin, input);
	std::stringstream(input) >> inputRow >> inputCol;

	//convert raw input into proper indices
	row = inputRow - 1;
	col = int(inputCol) - 97;
	
	// Checks that indices are within range
	if ((row < 0 || row > 7) || (col < 0 || col > 7))
		return false;
	
	// verifies piece at indicated spot is player's
	if (gameBoard.at(row).at(col) != 'b')
	{
		return false;
	}
	
	// verifies that piece has any valid moves
	if (!pieceHasValidJump(row, col) && !pieceHasValidMove(row, col))
	{
		return false;
	}

	// Get player's move
	std::cout << "Input the row and column of the position to move to: ";
	std::getline(std::cin, locInput);
	std::stringstream(locInput) >> inputRow >> inputCol;

	//convert raw input into proper indices
	locationRow = inputRow - 1;
	locationColumn = int(inputCol) - 97;

	// Checks that indices are within range
	if ((locationRow < 0 || locationRow > 7) || (locationColumn < 0 || locationColumn > 7))
		return false;

	// verifies the indicated spot is open
	if (moveIsValid(row, col, locationRow, locationColumn))
	{
		makeMove(row, col, locationRow, locationColumn);
		row = locationRow;
		col = locationColumn;
		while (pieceHasValidJump(row, col))
		{
			// Handle multiple jumps
			displayBoard();
			std::cout << "Additional jumps available\n";
			// Get player's move
			std::cout << "Input the row and column of the position to move to: ";
			std::getline(std::cin, locInput);
			std::stringstream(locInput) >> inputRow >> inputCol;

			//convert raw input into proper indices
			locationRow = inputRow - 1;
			locationColumn = int(inputCol) - 97;

			// Checks that indices are within range
			if ((locationRow < 0 || locationRow > 7) || (locationColumn < 0 || locationColumn > 7))
				return false;

			// verifies the indicated spot is open
			if (moveIsValid(row, col, locationRow, locationColumn))
			{
				makeMove(row, col, locationRow, locationColumn);
				row = locationRow;
				col = locationColumn;
			}
		}
		return true;
	}
	else
		return false;
}

// Make a move for the computer/red team
void GameState::computerMove() {

	// ToDo: Need to add computer's AI  --> AI IS STILL VERY NAIVE, AND DOES NOT DOUBLE JUMP
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			if (gameBoard.at(i).at(j) == currentPlayer)
			{
				if ((i - 2) >= 0 && (i - 2) < 8)
				{
					if ((j + 2 < 8) && gameBoard.at(i - 2).at(j + 2) == 'o' && gameBoard.at(i - 1).at(j + 1) == opponent())
					{
						makeMove(i,j,i-2,j+2);
						return;
					}
					if ((j - 2 >= 0) && gameBoard.at(i - 2).at(j - 2) == 'o' && gameBoard.at(i - 1).at(j - 1) == opponent())
					{
						makeMove(i, j, i - 2, j + 2);
						return;
					}
				}
				if (i - 1 >= 0 && i - 1 < 8)
				{
					if ((j + 1 < 8) && gameBoard.at(i - 1).at(j + 1) == 'o')
					{
						makeMove(i, j, i - 1, j + 1);
						return;
					}
					if ((j - 1 >= 0) && gameBoard.at(i - 1).at(j - 1) == 'o')
					{
						makeMove(i, j, i - 1, j - 1);
						return;
					}
				}

			}
		}
	}

}


// Display the current game board
void GameState::displayBoard() {
	std::ostringstream oss;
	oss << "\n     a   b   c   d   e   f   g   h\n\n";
	for (int i = 0; i < ROWS; ++i)
	{
		oss << (i + 1) << "  ";
		for (int j = 0; j < COLS; ++j)
		{
			oss << "| ";
			if (gameBoard.at(i).at(j) == 'b' || gameBoard.at(i).at(j) == 'r')
			{
				oss << gameBoard.at(i).at(j);
				oss << " ";
			}
			else
			{
				oss << "  ";
			}
		}
		oss << "|\n   ---------------------------------\n";
	}
	std::cout << oss.str() << std::endl;
}


// Check to see if either side won
bool GameState::validMoveRemains() {

	// Check to see if current player has any remaining pieces with legal moves available
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			if (gameBoard.at(i).at(j) == currentPlayer)
			{
				// checks a non-capturing move
				if (pieceHasValidMove(i, j))
					return true;

				// checks a capturing move
				if (pieceHasValidJump(i, j))
					return true;
			}
		}
	}
	return false;
}

bool GameState::pieceHasValidMove(int row, int col)
{
	// set turn to positive or negative 1 depending on direction player is moving
	int turn;
	if (currentPlayer == 'r')
		turn = -1;
	else
		turn = 1;

	if (row + turn >= 0 && row + turn < 8)
	{
		if ((col + 1 < 8) && gameBoard.at(row + turn).at(col + 1) == 'o')
			return true;
		if ((col - 1 >= 0) && gameBoard.at(row + turn).at(col - 1) == 'o')
			return true;
	}
	return false;
}

// Checks if a piece has a valid jump available
bool GameState::pieceHasValidJump(int row, int col)
{
	// set turn to positive or negative 1 depending on direction player is moving
	int turn;
	if (currentPlayer == 'r')
		turn = -1;
	else
		turn = 1;

	// Check for a valid jump move
	if ((row + turn + turn) >= 0 && (row + turn + turn) < 8)
	{
		if ((col + 2 < 8) && gameBoard.at(row + turn + turn).at(col + 2) == 'o' && gameBoard.at(row + turn).at(col + 1) == opponent())
			return true;
		if ((col - 2 >= 0) && gameBoard.at(row + turn + turn).at(col - 2) == 'o' && gameBoard.at(row + turn).at(col - 1) == opponent())
			return true;
	}
	return false;
}

// Main method to handle turns
void GameState::takeTurn() {
	
	// Check to see if any valid moves remain to the current player
	if (!validMoveRemains())
	{
		winningPlayer = opponent();

	}
	else
	{
		std::cout << "It is player " << currentPlayer << "'s turn\n";
		if (currentPlayer == 'b')
		{
			bool playerMoveIsValid = false;
			while (!playerMoveIsValid)
			{
				playerMoveIsValid = playerMove();
				if (!playerMoveIsValid)
				{
					displayBoard();
					std::cout << "\nThat is an invalid piece or move, please try again\n";
				}
			}
			swapPlayer();
		}
		else
		{
			computerMove();
			swapPlayer();
		}

	}
	displayBoard();
}

void GameState::announceWinner() {
	std::cout << "We have a winner! Winning player is " << winningPlayer << "!!\n";
}

// Make a legal move
void GameState::makeMove(int rowFrom, int colFrom, int rowTo, int colTo)
{
	// Make move if it is a non-jump move
	if (abs(rowFrom - rowTo) == 1)
	{
		gameBoard.at(rowFrom).at(colFrom) = 'o';
		gameBoard.at(rowTo).at(colTo) = currentPlayer;
	}
	// Make move if it is a jump move
	else
	{
		gameBoard.at(rowFrom).at(colFrom) = 'o';
		gameBoard.at((rowFrom + rowTo) / 2).at((colFrom + colTo) / 2) = 'o';
		gameBoard.at(rowTo).at(colTo) = currentPlayer;
	}
}


bool GameState::moveIsValid(int rowFrom, int colFrom, int rowTo, int colTo)
{
	// set turn to positive or negative 1 depending on direction player is moving
	int turn;
	if (currentPlayer == 'r')
		turn = -1;
	else
		turn = 1;

	// If the move is to an empty diagonal spot, return true
	if (rowTo - rowFrom == turn && abs(colTo - colFrom) == 1)
		return(gameBoard.at(rowTo).at(colTo) == 'o');
	
	// If the move is a jump, the target spot is empty, and the in between spot is occupied
	// by the opponents piece, return true
	if (rowTo - rowFrom == 2 * turn && abs(colTo - colFrom) == 2)
		return(gameBoard.at(rowTo).at(colTo) == 'o' && gameBoard.at((rowFrom + rowTo) / 2).at((colFrom + colTo) / 2) == opponent());

	// Returns false if the spot is more than 1 or 2 rows away
	return false;
}