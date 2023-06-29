/** @file Board.h */
//Declarations (headers) of board related functions

#pragma once
#include "Player.h"
#include <vector>
#include "Tile.h"

/**
@class Board contains functions realted to operations on the game board
@var board a pointer to an array of pointers which represents a 2D board
@var boardsize integer representing number of rows and columns in the board
@var winningCount number of marked squares one have to obtain in order to win
@var winner Player who won
*/
class Board
{
	char** board;
	int boardSize;
	int winningCount;

	/**
	* @brief Returns vector of adjacent Tiles
	* @param tile
	* @param board
	* @return std::vector<Tile>
	*/
	std::vector<Tile> FindNeighbours(Tile tile, char** board);

	/**
	* @brief Finds next Tile in a line based on previous and current tiles
	* @param currentTile
	* @param previousTile
	* @return Tile
	*/
	Tile NextTileInSequence(Tile currentTile, Tile previousTile);

	/**
	* @brief Returns a vector of winning sequences of Tiles based on the current layout of the board
	* @param parentTile
	* @param neighbour
	* @param winningCount
	* @return std::vector<Tile>
	*/
	std::vector<Tile> WinningSequence(Tile parentTile, Tile neighbour, int winningCount);

	/**
	* @brief Checks if the current state of the board contains any winning sequences
	* @param winningSequence
	* @param board
	* @return bool
	*/
	bool MatchSequences(std::vector<Tile> winningSequence, char** board);

	/**
	* @brief Checks if any neighbouring Tile lead to winning sequence
	* @param tile
	* @param neighbours
	* @param winningCount
	* @param board
	* @return bool
	*/
	bool CheckTheSequence(Tile tile, std::vector<Tile> neighbours, int winningCount, char** board);

	/**
	* @brief Returns an integer based on the current layout of the board
	* @return int
	*/
	int EvaluateBoard();

	/**
	* @brief Recursive function responsible for finding a move with the best outcome 
	* @param board
	* @param depth
	* @param isMax
	* @return int
	*/
	int MiniMax(char** board, int depth, bool isMax);

public:
	Player winner;

	/**
	* @brief Constructor of the class Board, it creates a pointer that points to an array of pointers filled with whitespaces
	*/
	Board();

	/**
	* @brief Destructor of the class Board
	*/
	~Board();

	/**
	* @brief Prints current state of the board
	*/
	void PrintBoard();

	/**
	* @brief Function responsible for getting the input from user
	* @param player
	* @return Tile
	*/
	Tile EnterMove(Player player);

	/**
	* @brief Short function for altering the board state
	* @param tile
	*/
	void MakeMove(Tile tile);

	/**
	* @brief Switches between players
	* @param player
	* @return Player
	*/
	Player OtherPlayer(Player player);

	/**
	* @brief Function that returns which player won
	* @return Player
	*/
	Player CheckForWin();

	/**
	* @brief Simple function which tells if the board is full
	* @return bool
	*/
	bool BoardFull();

	/**
	* @brief Function that return the best move for AI to play
	* @return Tile
	*/
	Tile LetAIMove(Player player);
};

