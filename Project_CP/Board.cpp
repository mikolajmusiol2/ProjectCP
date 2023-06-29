#include "Board.h"
#include <iostream>
#include "Player.h"
#include <vector>
#include "Tile.h"

Board::Board()
{
    boardSize = 3;
    winningCount = 3;
    winner = Player::None;

    board = new char*[boardSize];
    for (int i = 0; i < boardSize; i++)
    {
        board[i] = new char[boardSize];
    }

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = (char)Player::None;
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < boardSize; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

void Board::PrintBoard()
{
    std::cout << "      ";
    for (int i = 0; i < boardSize; i++) {
        if (i < 9) {
            std::cout << i + 1 << "   ";
        }
        else {
            std::cout << i + 1 << "  ";
        }
    }
    std::cout << "\n    +";
    for (int i = 0; i < boardSize; i++) {
        std::cout << "---+";
    }
    std::cout << "\n";
    for (int i = 0; i < boardSize; i++) {
        if (i < 9) {
            std::cout << "  " << i + 1 << " |";
        }
        else {
            std::cout << " " << i + 1 << " |";
        }
        for (int j = 0; j < boardSize; j++) {
            std::cout << " " << board[i][j] << " |";
        }
        std::cout << "\n    +";
        for (int i = 0; i < boardSize; i++) {
            std::cout << "---+";
        }
        std::cout << "\n";
    }
}

Tile Board::EnterMove(Player player)
{
    int row, col;
    do {
        std::cout << "Player " << (char)player << ", enter row and column for your move: ";
        std::cin >> row >> col;
        row--;
        col--;
    } while (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != (char)Player::None);
    return Tile{ row, col, (char)player };
}

void Board::MakeMove(Tile tile)
{
    board[tile.row][tile.column] = tile.symbol;
}

Player Board::OtherPlayer(Player player)
{
    if (player == Player::X)
    {
        return Player::O;
    }
    else
    {
        return Player::X;
    }
}

bool Board::BoardFull()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] == (char)Player::None)
            {
                return false;
            }
        }
    }
    return true;
}

std::vector<Tile> Board::FindNeighbours(Tile tile, char** board)
{
    std::vector<Tile> neighbours;

    if (tile.column != boardSize - 1)
    {
        if (board[tile.row][tile.column + 1] == tile.symbol) 
        {
            neighbours.push_back(Tile{ tile.row, tile.column + 1, tile.symbol });
        }
    }

    if (tile.column != boardSize - 1 && tile.row != boardSize - 1 )
    {
        if (board[tile.row + 1][tile.column + 1] == tile.symbol) 
        {
            neighbours.push_back(Tile{ tile.row + 1, tile.column + 1, tile.symbol });
        }
    }

    if (tile.row != boardSize - 1)
    {
        if (board[tile.row + 1][tile.column] == tile.symbol) 
        {
            neighbours.push_back(Tile{ tile.row + 1, tile.column, tile.symbol });
        }
    }

    if (tile.row != boardSize - 1 && tile.column != 0)
    {
        if (board[tile.row + 1][tile.column - 1] == tile.symbol) 
        {
            neighbours.push_back(Tile{ tile.row + 1, tile.column - 1, tile.symbol });
        }
    }

    return neighbours;
}

Tile Board::NextTileInSequence(Tile currentTile, Tile previousTile)
{
    if (previousTile.column + 1 == currentTile.column && previousTile.row == currentTile.row)
    {
        return Tile{ currentTile.row, currentTile.column + 1, currentTile.symbol };
    }

    if (previousTile.row + 1 == currentTile.row && previousTile.column + 1 == currentTile.column)
    {
        return Tile{ currentTile.row + 1, currentTile.column + 1, currentTile.symbol };
    }

    if (previousTile.row + 1 == currentTile.row && previousTile.column == currentTile.column)
    {
        return Tile{ currentTile.row + 1, currentTile.column, currentTile.symbol };
    }

    if (previousTile.row + 1 == currentTile.row && previousTile.column - 1 == currentTile.column)
    {
        return Tile{ currentTile.row + 1, currentTile.column - 1, currentTile.symbol };
    }
}

std::vector<Tile> Board::WinningSequence(Tile parentTile, Tile neighbour, int winningCount)
{
    std::vector<Tile> wSequence;
    Tile currentTile = neighbour;
    Tile previousTile = parentTile;

    wSequence.push_back(parentTile);
    wSequence.push_back(neighbour);

    for (int i = wSequence.size(); i < winningCount; i++)
    {
        Tile nextTile = NextTileInSequence(currentTile, previousTile);
        wSequence.push_back(nextTile);
        previousTile = currentTile;
        currentTile = nextTile;
    }

    return wSequence;
}

bool Board::MatchSequences(std::vector<Tile> winningSequence, char** board)
{
    int matches = 0;

    for (Tile winningTile : winningSequence)
    {
        if (winningTile.row < 0 || winningTile.row > boardSize - 1 || winningTile.column < 0 || winningTile.column > boardSize - 1)
        {
            break;
        }
        if (board[winningTile.row][winningTile.column] == winningTile.symbol)
        {
            matches++;
        }
    }

    if (matches == winningSequence.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::CheckTheSequence(Tile tile, std::vector<Tile> neighbours, int winningCount, char** board)
{
    for (Tile neighbour : neighbours)
    {
        std::vector<Tile> winningSequence = WinningSequence(tile, neighbour, winningCount);

        if (MatchSequences(winningSequence, board) == true)
        {
            return true;
        }
    }
    return false;
}

Player Board::CheckForWin()
{
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] == (char)Player::X || board[i][j] == (char)Player::O)
            {
                Tile tileToCheck{ i, j, board[i][j] };
                std::vector<Tile> neighbours = FindNeighbours(tileToCheck, board);

                if (CheckTheSequence(tileToCheck, neighbours, winningCount, board) == true)
                {
                    return (Player)board[i][j];
                }
            }
        }
    }
    return Player::None;
}


int Board::EvaluateBoard()
{
    if (CheckForWin() == Player::X)
    {
        return -10;
    }
    else if (CheckForWin() == Player::O)
    {
        return 10;
    }
    else
    {
        return 0;
    }
}

int Board::MiniMax(char ** mboard, int depth, bool isMax)
{
    int score = EvaluateBoard();

    if (score == 10 || score == -10)
    {
        return score;
    }
    else if (BoardFull() == true)
    {
        return 0;
    }
    else if (depth > 4)
    {
        return 0;
    }

    if (isMax)
    {
        int bestScore = std::numeric_limits<int>::min();

        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (mboard[i][j] == (char)Player::None)
                {
                    mboard[i][j] = (char)Player::O;

                    int score = MiniMax(mboard, depth + 1, false);

                    mboard[i][j] = (char)Player::None;

                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = std::numeric_limits<int>::max();

        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (mboard[i][j] == (char)Player::None)
                {
                    mboard[i][j] = (char)Player::X;

                    int score = MiniMax(mboard, depth + 1, true);

                    mboard[i][j] = (char)Player::None;

                    bestScore = std::min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

Tile Board::LetAIMove(Player player)
{
    int bestScore = std::numeric_limits<int>::min();

    Tile bestMove{ -1, -1, (char)player };

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if (board[i][j] == (char)Player::None)
            {
                board[i][j] = (char)Player::O;

                int moveScore = MiniMax(board, 0, false);

                board[i][j] = (char)Player::None;

                if (moveScore > bestScore)
                {
                    bestScore = moveScore;
                    bestMove.row = i;
                    bestMove.column = j;
                }
            }
        }
    }

    return  bestMove;
}