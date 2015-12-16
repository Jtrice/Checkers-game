#ifndef P_T_HEADER
#define P_T_HEADER

#include <string>
#include <array>

class GameState
{
public:
	char winningPlayer;

	GameState();
	void takeTurn();
	void announceWinner();

private:
	char currentPlayer;
	std::array<std::array<char, 8>, 8> gameBoard;

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

#endif	//P_T_HEADER
