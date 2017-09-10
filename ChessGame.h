

#ifndef CHESS_CHESSGAME_H
#define CHESS_CHESSGAME_H

#include "ChessHistory.h"
#include <ctype.h>

#define GAME_SIZE 8
#define WHITE_PLAYER 0
#define BLACK_PLAYER 1
#define EMPTY_SQUARE (-1)
#define EMPTY_ENTRY '_'
#define PAWN_WHITE 'm'
#define PAWN_BLACK 'M'
#define BISHOP_WHITE 'b'
#define BISHOP_BLACK 'B'
#define ROOK_WHITE 'r'
#define ROOK_BLACK 'R'
#define KNIGHT_WHITE 'n'
#define KNIGHT_BLACK 'N'
#define QUEEN_WHITE 'q'
#define QUEEN_BLACK 'Q'
#define KING_WHITE 'k'
#define KING_BLACK 'K'

#define GET_COLUMN(x) ((x).column-65)
#define GET_ROW(x) ((x).row-1)

typedef struct chess_struct {
    char gameBoard[GAME_SIZE][GAME_SIZE];
    int currentPlayer;
    ChessHistory *history;
    int score;
    Position whiteKingPos;
    Position blackKingPos;
    bool whiteRightCastle;
    bool whiteLeftCastle;
    bool blackRightCastle;
    bool blackLeftCastle;
} ChessGame;

ChessGame *gameCreate(int historySize);

ChessGame *gameCopy(ChessGame *src);

void gameDestroy(ChessGame *src);

CHESS_MESSAGE printBoard(ChessGame *src);

int getPlayer(char soldier);
CHESS_MESSAGE movePiece(ChessGame *game, Position src, Position dest);
char getSoldier( char board[GAME_SIZE][GAME_SIZE], int row, int col);

char getOtherKnight(int player);
char getOtherKing(int player);
char getOtherQueen(int player);
char getOtherBishop(int player);
char getOtherRook(int player);
char getOtherPawn(int player);
int getOtherPlayer(int player);
bool knightThreatsPosition(ChessGame *game, int row, int col);
bool kingThreatsPosition(ChessGame *game, int row, int col);

bool QBRThreatsPosition(ChessGame *game, int row, int col);
bool myPositionUnderThreat(ChessGame *game,Position pos);
bool legalCastling(ChessGame *game, Position src, Position dest, bool isRightCastling);
bool isValidMove_King(ChessGame *game, Position src, Position dest);
bool isValidMove_Queen(ChessGame *game, Position src, Position dest);
bool isValidMove_Knight(ChessGame *game, Position src, Position dest);
bool isValidMove_Bishop(ChessGame *game, Position src, Position dest);
bool isValidMove_Rook(ChessGame *game, Position src, Position dest);
bool isValidMove_Pawn(ChessGame *game, Position src, Position dest);
void pawnPromotion(ChessGame *game, Position posOfPawn);
void updateScore(char soldierDied,ChessGame* game);
void changePlayer(ChessGame* game);
CHESS_MESSAGE setMove(ChessGame *game, Position src, Position dest);
CHESS_MESSAGE checkStatus(ChessGame* game);


/**
 *
 *
 * @param game
 * @param src
 * @param dest
 * @return
 */
bool isValidMove(ChessGame* game, Position src, Position dest);


char *getStringFromPosition(Position dest);

// bonus functions
void printMoves(ChessGame *game, Position pos);

int getMoves(ChessGame* game, Position *result, Position pos);

void undoMove(ChessGame* game);
#endif //CHESS_CHESSGAME_H
