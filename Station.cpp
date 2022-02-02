#include "Station.h"
#include "Rook.h"
#include "King.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
Station::Station()
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            board[y][x] = 0;
        }
    }

    board[0][0] = new Rook(White);
    board[0][1] = new Knight(White);
    board[0][2] = new Bishop(White);
    board[0][3] = new Queen(White);
    board[0][4] = new King(White);
    board[0][5] = new Bishop(White);
    board[0][6] = new Knight(White);
    board[0][7] = new Rook(White);


    for (int i = 0; i < 8; i++)
    {
        board[1][i] = new Pawn(White);
        board[6][i] = new Pawn(Black);
    }




    board[7][0] = new Rook( Black);
    board[7][1] = new Knight( Black);
    board[7][2] = new Bishop( Black);
    board[7][3] = new Queen( Black);
    board[7][4] = new King( Black);
    board[7][5] = new Bishop( Black);
    board[7][6] = new Knight( Black);
    board[7][7] = new Rook( Black);
}