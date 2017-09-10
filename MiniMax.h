

#ifndef CHESS_MINIMAX_H
#define CHESS_MINIMAX_H

#include <stdbool.h>
#include "ChessGame.h"

typedef struct minimax_node {
    int alpha;
    int beta;
    bool isMaxType; // flag helps determine if  this node is a max or min node
    ChessGame *game; // copy of the current game state
    int player; // the player who has to play next
    HistoryNode move // the historynode representing the move made by this node
} MiniMaxNode;


#endif //CHESS_MINIMAX_H
