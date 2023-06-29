#include <iostream>
#include <cstdlib>
#include "Board.h"

int gameMode;

void StartGame()
{
    do
    {
        system("cls");
        std::cout << "Welcome to TicTacToe console game!" << std::endl;
        std::cout << "Choose game mode (0 - player vs player | 1 - player vs AI): ";
        std::cin >> gameMode;
    } while (gameMode != 0 && gameMode != 1);
}

int main() 
{
    Player humanPlayer = Player::X;
    Player currentPlayer = humanPlayer;
    
    StartGame();

    Board board;
    system("cls");
    board.PrintBoard(); 

    if (gameMode == 0)
    {
        while (board.CheckForWin() == Player::None && board.BoardFull() == false)
        {
            board.MakeMove(board.EnterMove(currentPlayer));
            system("cls");
            board.PrintBoard();
            currentPlayer = board.OtherPlayer(currentPlayer);
        }
    }
    else if (gameMode == 1)
    {
        enum turn 
        {
            humanTurn,
            botTurn
        };
        turn turn;
        
        if (humanPlayer == Player::X)
        {
            turn = humanTurn;
        }
        else
        {
            turn = botTurn;
        }

        while (board.CheckForWin() == Player::None && board.BoardFull() == false)
        {
            if (turn == humanTurn)
            {
                board.MakeMove(board.EnterMove(currentPlayer));
                turn = botTurn;
            }
            else if (turn == botTurn)
            {
                board.MakeMove(board.LetAIMove(currentPlayer));
                turn = humanTurn;
            }

            system("cls");
            board.PrintBoard();
            currentPlayer = board.OtherPlayer(currentPlayer);
        }
    }
    
    char winner = (char)board.CheckForWin();

    if (winner == (char)Player::None)
    {
        std::cout << "\nThe game is a draw.\n";
    }
    else
    {
        std::cout << "\nThe game ended. " << winner << " is the winner.\n";
    }
    return 0;
}
