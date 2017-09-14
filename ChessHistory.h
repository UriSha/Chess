
#ifndef CHESS_CHESSHISTORY_H
#define CHESS_CHESSHISTORY_H
#include <stdio.h>
#include <stdlib.h>
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

// new type used to hold chess moves
typedef struct chess_array_list{
    HistoryNode* moves;
    int actualSize;
    int maxSize;
}ChessHistory;

// enum used for chess game messages
typedef enum{
    SUCCESS,
    ILLEGAL_MOVE,
    INVALID_ARGUMENT,
    NO_HISTORY,
    CHECK,
    MATE,
    TIE,
    CONTINUE,

}CHESS_MESSAGE;

/**
 * creates a struct to hold a given amount (the input) of chess game moves
 *
 * @return a pointer to the new struct
 */
ChessHistory* createChessHistory(int maxSize);

/**
 * copies a given ChessHistory
 *
 * @return a pointer to the new struct
 */
ChessHistory * copyChessHistory(ChessHistory* source);

/**
 * deletes a ChessHistory struct, frees all resources
 *
 */
void destroyChessHistory(ChessHistory **source);

/**
 * add a given move to the given ChessHistory
 *
 * @return message that indicates success of failure
 */
CHESS_MESSAGE addMovetoHistory(ChessHistory* source, HistoryNode move);

/**
 * remove the most recent added move from the given ChessHistory (LIFO order)
 *
 * @return message that indicates success of failure
 */
HistoryNode* removeRecentMove(ChessHistory* source);

/**
 *
 * @return true if the given ChessHistory is empty, false otherwise
 */
bool isHistoryEmpty(ChessHistory* source);


#endif //CHESS_CHESSHISTORY_H
