#include "Station.h"

Station::Station()
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            board[y][x] = 0;
        }
    }

    board[0][0] = new Piece(Rook, White);
    board[0][1] = new Piece(Knight, White);
    board[0][2] = new Piece(Bishop, White);
    board[0][3] = new Piece(Queen, White);
    board[0][4] = new Piece(King, White);
    board[0][5] = new Piece(Bishop, White);
    board[0][6] = new Piece(Knight, White);
    board[0][7] = new Piece(Rook, White);


    for (int i = 0; i < 8; i++)
    {
        board[1][i] = new Piece(Pawn, White);
        board[6][i] = new Piece(Pawn, Black);
    }




    board[7][0] = new Piece(Rook, Black);
    board[7][1] = new Piece(Knight, Black);
    board[7][2] = new Piece(Bishop, Black);
    board[7][3] = new Piece(Queen, Black);
    board[7][4] = new Piece(King, Black);
    board[7][5] = new Piece(Bishop, Black);
    board[7][6] = new Piece(Knight, Black);
    board[7][7] = new Piece(Rook, Black);
}