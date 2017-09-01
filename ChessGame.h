

#ifndef CHESS_CHESSGAME_H
#define CHESS_CHESSGAME_H
#include "ChessHistory.h"
//typedef enum {
//    PAWN,
//    QUEEN,
//    KING,
//    BISHOP,
//    ROOK,
//    KNIGHT,
//    EMPTY,
//}Soldier;
#define CHESS_GAME_SIZE 8
#define WHITE_PLAYER 0
#define BLACK_PLAYER 1
#define PAWN_WHITE 'm'
#define PAWN_BLACK 'M'
#define BISHOP_WHITE 'b'
#define BISHOP_BLACK 'B'
#define ROOK_WHITE 'r'
#define ROOK_BLACK 'R'
#define KNIGHT_WHITE 'n'
#define KNIGHT_BLACK 'N'
#define QUEEN_WHITE 'q'
#define QUEEEN_BLACK 'Q'
#define KING_WHITE 'k'
#define KING_BLACK 'K'

typedef struct chess_struct{
    char gameBoard[CHESS_GAME_SIZE][CHESS_GAME_SIZE];
    int currentPlayer;
    ChessHistory* history;
    int score;
}ChessGame;




#endif //CHESS_CHESSGAME_H
