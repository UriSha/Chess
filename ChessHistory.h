
#ifndef CHESS_CHESSHISTORY_H
#define CHESS_CHESSHISTORY_H
#include <stdio.h>
#include <stdlib.h>
#include "ChessGame.h"
#include "ChessParser.h"
/**
 * a struct that saves the last move that happened in the game.
 * source is the source position that was used before the turn
 * destination is the destination position of the move
 * square will be EMPTY if the destination is empty,otherwise it will be one of the soldiers in the game
 */
typedef struct chess_move_history{
    Position source;
    Position destination;
    char soldierDied;
}HistoryNode;

typedef struct chess_array_list{
    HistoryNode* moves;
    int actualSize;
    int maxSize;
}ChessHistory;

typedef enum{
    SUCCESS,
    INVALID_ARGUMENT,

}CHESS_MESSAGE;

ChessHistory* createChessHistory(int maxSize);

ChessHistory * copyChessHistory(ChessHistory* source);

void destroyChessHistory(ChessHistory* source);

CHESS_MESSAGE addMovetoHistory(ChessHistory* source, HistoryNode move);

HistoryNode* removeRecentMove(ChessHistory* source);

bool isHistoryEmpty(ChessHistory* source);


#endif //CHESS_CHESSHISTORY_H
