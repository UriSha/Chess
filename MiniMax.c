#include "MiniMax.h"
#include <limits.h>
#include <stdbool.h>

int scoringFunction(ChessGame *game, bool isExpertLevel) {
    int blackOrWhite = game->currentPlayer == WHITE_PLAYER ? 1 : -1;
    if (checkStatus(game) == MATE)
        return INT_MAX * blackOrWhite;
    if (!isExpertLevel)
        return game->score * blackOrWhite;
    return 0;//TODO expert level scoring function

}

MiniMaxNode *createNode(int alpha, int beta, bool isMaxType, ChessGame *copyOfGame) {
    if (copyOfGame == NULL)
        return NULL;
    MiniMaxNode *node = (MiniMaxNode *) malloc(sizeof(MiniMaxNode));
    if (node == NULL) {
        printf(MALLOC_ERROR);
        return NULL;
    }
    node->game = copyOfGame;
    node->alpha = alpha;
    node->beta = beta;
    node->isMaxType = isMaxType;
    node->player = copyOfGame->currentPlayer;
    return node;
}

void nodeDestroy(MiniMaxNode *node) {
    if (node != NULL)
        free(node);
}

void updateRoot(MiniMaxNode *root, MiniMaxNode *child) {
    if (root == NULL || child==NULL)
        return;
    if (root->isMaxType) {
        if (root->alpha < child->beta)
            root->alpha = child->beta;
    } else {
        if (root->beta > child->alpha)
            root->beta = child->alpha;
    }
}

void updateAlphaBeta(MiniMaxNode *root, bool isExpertLevel, int maxDepth) {
    if (root->game == NULL)
        return;
    if (checkStatus(root->game) == TIE) {
        if (root->isMaxType == true)
            root->alpha = 0;
        else
            root->beta = 0;
        return;
    }
    if (checkStatus(root->game) == MATE) {
        if (root->isMaxType == true)
            root->alpha = INT_MIN;
        else
            root->beta = INT_MAX;
        return;
    }
    Position src, dest;
    ChessGame *copy = gameCopy(root->game);
    MiniMaxNode *child;
    for (int row = 1; row <= GAME_SIZE; row++) {
        src.row = row;
        for (int col = 0; col < GAME_SIZE; col++) {
            src.column = 'A' + col;
            for (int i = 1; i <= GAME_SIZE; i++) {
                dest.row = i;
                for (int j = 0; j < GAME_SIZE; j++) {
                    dest.column = 'A' + j;
                    if (isValidMove(copy, src, dest)) {
                        setMove(copy, src, dest);
                        if (maxDepth == 1) {
                            if (!root->isMaxType)
                                changePlayer(copy);
                            int moveScore = scoringFunction(copy, isExpertLevel);
                            child = createNode(moveScore, moveScore, 1 - root->isMaxType, copy);
                            updateRoot(root, child);
                            if (root->alpha >= root->beta) {
                                gameDestroy(copy);
                                nodeDestroy(child);
                                return;
                            }
                            if (!root->isMaxType)
                                changePlayer(copy);
                            undoMove(copy);
                        } else {
                            child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy);
                            updateAlphaBeta(child, isExpertLevel, maxDepth - 1);
                            updateRoot(root, child);
                            if (root->alpha >= root->beta) {
                                gameDestroy(copy);
                                nodeDestroy(child);
                                return;
                            }
                            undoMove(copy);

                        }
                    }
                }
            }
        }
    }
}


HistoryNode bestMove(ChessGame *game, int maxDepth, bool isExpertLevel) {
    HistoryNode bestMove;
    int bestScoreSoFar = INT_MIN;
    Position src, dest;
    src.row = dest.row = 100;
    src.column = src.column = 'Z';
    bestMove.source = src;
    bestMove.destination = dest;
    bestMove.soldierDied = 'Z';
    bool firstValid = true;
    int currentAlpha = INT_MIN;
    if (game == NULL || maxDepth < 1 || maxDepth > 4)
        return bestMove;
    ChessGame *copy = gameCopy(game);
    for (int row = 1; row <= GAME_SIZE; row++) {
        src.row = row;
        for (int col = 0; col < GAME_SIZE; col++) {
            src.column = 'A' + col;
            for (int i = 1; i <= GAME_SIZE; i++) {
                dest.row = i;
                for (int j = 0; j < GAME_SIZE; j++) {
//                    if (row ==3 && col ==0 && i == 5 && j == 1 && copy->gameBoard[2][0]==KNIGHT_WHITE)
//                        printf("hii");
//                    if (row ==7 && col ==0 && i == 6 && j == 1 && copy->gameBoard[5][1]==PAWN_WHITE)
//                        printf("hii\n");
                    dest.column = 'A' + j;
                    if (isValidMove(copy, src, dest)) {
                        if (firstValid) {
                            bestMove.soldierDied = game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)];
                            bestMove.source = src;
                            bestMove.destination = dest;
                            firstValid = false;
                        }
                        setMove(copy, src, dest);

                        if (maxDepth == 1) {// no recursion
                            int moveScore = scoringFunction(copy, isExpertLevel);
                            if (moveScore > bestScoreSoFar) {
                                bestScoreSoFar = moveScore;
                                bestMove.soldierDied = game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)];
                                bestMove.source = src;
                                bestMove.destination = dest;
                            }
                        } else {
                            changePlayer(copy);
                            MiniMaxNode *child = createNode(currentAlpha, INT_MAX, false, copy);
                            updateAlphaBeta(child, isExpertLevel, maxDepth - 1);
                            if (child->beta > currentAlpha) {
                                currentAlpha = child->beta;
                                bestMove.soldierDied = game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)];
                                bestMove.source = src;
                                bestMove.destination = dest;
                            }
                            changePlayer(copy);
//                            nodeDestroy(child); // TODO bugs were here
                        }
                        undoMove(copy);
                    }
                }
            }
        }
    }
    gameDestroy(copy);
    return bestMove;
}