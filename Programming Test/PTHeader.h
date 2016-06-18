#ifndef P_T_HEADER
#define P_T_HEADER

#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <iomanip>

class GameState
{
public:
	

	GameState();
	GameState(int rows, int cols, int blackRows, int redRows);
	//GameState(int row, int col, std::array<std::array<char, 8>, 8> gameBoard);
	void takeTurn();
	char getWinningPlayer();
	void announceWinner();

private:
	int row;
	int col;
	char currentPlayer;
	char winningPlayer;
	//std::array<std::array<char, 8>, 8> gameBoard;
	std::vector<std::vector<char>> gameBoard;

	char swapPlayer();
	char opponent();
	void computerMove();
	bool playerMove();
	void displayBoard();
	bool validMoveRemains();
	bool pieceHasValidJump(int row, int col);
	bool pieceHasValidMove(int row, int col);
	void makeMove(int rowFrom, int colFrom, int rowTo, int colTo);
	bool moveIsValid(int rowFrom, int colFrom, int rowTo, int colTo);
	
	
};

//std::array<std::array<char, 8>, 8> stdCheckersBoard();




// Method definitions

// Creates a beginning board for checkers
//std::array<std::array<char, 8>, 8> stdCheckersBoard()
//{
//	// Initialize array of arrays to hold gameboard
//	std::array<std::array<char, 8>, 8> gameBoard;
//
//	// Initialize the board for play
//	char piece = 'b';
//
//	for (int i = 0; i < int(gameBoard.size()); i++)
//	{
//		std::cout << &i;
//	};
//
//	gameBoard.at(0) = { 'b','i','b','i','b','i','b','i' };
//	gameBoard.at(1) = { 'i','b','i','b','i','b','i','b' };
//	gameBoard.at(2) = { 'b','i','b','i','b','i','b','i' };
//	gameBoard.at(3) = { 'i','o','i','o','i','o','i','o' };
//	gameBoard.at(4) = { 'o','i','o','i','o','i','o','i' };
//	gameBoard.at(5) = { 'i','r','i','r','i','r','i','r' };
//	gameBoard.at(6) = { 'r','i','r','i','r','i','r','i' };
//	gameBoard.at(7) = { 'i','r','i','r','i','r','i','r' };
//
//
//	return gameBoard;
//}

#endif	//P_T_HEADER
