

#ifndef CHESS_MINIMAX_H
#define CHESS_MINIMAX_H

#include <stdbool.h>
#include "ChessGame.h"

/**
 *MiniMax Summary:
 *  A module that contains the MiniMaxNode struct, the functions are our implementation for the Mini Max algorithm
 *  Some of the key functions :
 *
 * int scoringFunction(ChessGame* game, bool isExpertLevel)                - returns the score of the game
 * MiniMaxNode *createNode(int alpha, int beta, bool isMaxType, ChessGame *copyOfGame) - creates a new MiniMax node
 * void nodeDestroy(MiniMaxNode *node)                                      - frees a given node resources
 * void updateRoot(MiniMaxNode *root, MiniMaxNode *child)                   - update the alpha/beta value of the root
 * void updateAlphaBeta(MiniMaxNode *root, bool isExpertLevel, int maxDepth) - recursively get the best moves for the root and
 * moveNode bestMove(ChessGame * game, int maxDepth,bool isExpertLevel)      - returns the best move the player can make
 * CHESS_MESSAGE computerMove(ChessGame *game, int maxDepth,bool isExpertLevel) // TODO necessary?
 *
 *  // bonus function
 *
 *  int expertLevel(ChessGame* game,int blackOrWhite)                       - Calculate the expert level score
 */

/**
 *  A struct that we use to represent a MiniMax node
 *  it hold a game, the alpha and beta and if it is a max type or a min type
 */
typedef struct minimax_node {
    int alpha;
    int beta;
    bool isMaxType; // flag helps determine if  this node is a max or min node
    ChessGame *game; // copy of the current game state
    int player; // the player who has to play next   //TODO necessary?
    moveNode move; // the historynode representing the move made by this node //TODO necessary?
} MiniMaxNode;

/**
 * Uses the score attribute of a given game and the current players color to
 * calculate his relative score, if in expert level, uses expertLevel() to get the expert level
 * score of the board
 *
 * @param game - the game we want to get his score
 * @param isExpertLevel - true if we are in expert level, false otherwise
 * @return
 * the current score of the game
 */
int scoringFunction(ChessGame* game, bool isExpertLevel);

/**
 * creates a new node with the given parameters
 *
 * @param alpha, beta - the values for the algorithm
 * @param isMaxType - true if new node will be a max type and false if it will be a min type
 * @param copyOfGame - a copy of the game we are trying to seek the best move for
 *
 * @return
 * a pointer to the new node
 */
MiniMaxNode *createNode(int alpha, int beta, bool isMaxType, ChessGame *copyOfGame);

/**
 * frees the resources of the given node
 *
 * @param node - the MiniMax node to be freed
 */
void nodeDestroy(MiniMaxNode *node);

/**
 * update the alpha or beta of the root according to its type and if the child score is better of the root
 *
 * @param root - the father node, to be updated
 * @param child - the child node that its value (alpha or beta) may be transfer to the root
 */
void updateRoot(MiniMaxNode *root, MiniMaxNode *child);

/**
 * recursive function that gets a root and choose the best of its possible moves by maximising or minimising
 * (if its a max or min type) and sets its alpha and beta values accordingly.
 * uses pruning to reduce complexity
 *
 * @param root - the MiniMax node the function will update its alpha and beta values
 * @param isExpertLevel - true if new node is a max type and false if its a min type
 * @param maxDepth - the deepest the recursive call can get from this stage
 */
void updateAlphaBeta(MiniMaxNode *root, bool isExpertLevel, int maxDepth);

/**
 * chooses the best move the current player can do according to the MinMax algorithm
 * uses updateAlphaBeta() if necessary (i.e the maxDepth is bigger than 1)
 *
 * @param game - the game we want to get the best move for
 * @param maxDepth - the deepest the recursive call can get
 * @param isExpertLevel - true if new node is a max type and false if its a min
 *
 * @return
 * a moveNode represents the best move the player can do at this point of the game
 */
moveNode bestMove(ChessGame * game, int maxDepth,bool isExpertLevel);

/**
 * returns a score calculated for a board that take in to consideration the remaining pieces but also the pieces that
 * are currently threaten, by doing so it allows the algorithm to mimic another level of recursion without actually
 * calculating it
 *
 * @param game - the game we want to get the expert level score for
 * @param blackOrWhite - 1 if the current player is white and -1 if its black
 *
 * @return
 * the expert level score of the game
 */
int expertLevel(ChessGame* game,int blackOrWhite);

CHESS_MESSAGE computerMove(ChessGame *game, int maxDepth,bool isExpertLevel); // TODO necessary?
#endif //CHESS_MINIMAX_H
