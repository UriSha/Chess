#include "MiniMax.h"
#include <limits.h>

void updateScoreExpert(char soldierThreatened, int *score) {

    switch (soldierThreatened) {
        case PAWN_BLACK:
        case PAWN_WHITE:
            *score -= 1;
            break;
        case ROOK_BLACK :
        case ROOK_WHITE :
            *score -= 5;
            break;
        case KNIGHT_BLACK :
        case KNIGHT_WHITE :
            *score -= 3;
            break;
        case BISHOP_BLACK :
        case BISHOP_WHITE :
            *score -= 3;
            break;
        case QUEEN_BLACK :
        case QUEEN_WHITE :
            *score -= 9;
            break;
        case KING_BLACK :
        case KING_WHITE :
            *score -= 40;
            break;
        default :
            return;
    }


}

int expertLevel(ChessGame *game, int blackOrWhite) {
    int currentScore = game->score * blackOrWhite * 5;
    bool isWhite = blackOrWhite == 1 ? true : false;
    Position threat;
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            if (isWhite) {
                if (getPlayer(game->gameBoard[i][j]) == WHITE_PLAYER) {
                    threat.row = i + 1;
                    threat.column = 'A' + j;
                    if (myPositionUnderThreat(game, threat))
                        updateScoreExpert(game->gameBoard[i][j], &currentScore);
                }
            } else {
                if (getPlayer(game->gameBoard[i][j]) == BLACK_PLAYER) {
                    threat.row = i + 1;
                    threat.column = 'A' + j;
                    if (myPositionUnderThreat(game, threat))
                        updateScoreExpert(game->gameBoard[i][j], &currentScore);
                }
            }
        }
    }
    return currentScore;


}

int scoringFunction(ChessGame *game, bool isExpertLevel) {
    int blackOrWhite = game->currentPlayer == WHITE_PLAYER ? 1 : -1;
    if (checkStatus(game) == MATE)
        return INT_MAX * blackOrWhite;
    if (!isExpertLevel)
        return game->score * blackOrWhite;

    return expertLevel(game, blackOrWhite);
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
    if (root == NULL || child == NULL)
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
                                gameDestroy(&copy);
                                nodeDestroy(child);
                                return;
                            }
                            if (!root->isMaxType)
                                changePlayer(copy);
                            undoMove(copy);
                            nodeDestroy(child);
                        } else {
                            changePlayer(copy);
                            child = createNode(root->alpha, root->beta, 1 - root->isMaxType, copy);
                            updateAlphaBeta(child, isExpertLevel, maxDepth - 1);
                            updateRoot(root, child);
                            if (root->alpha >= root->beta) {
                                gameDestroy(&copy);
                                nodeDestroy(child);
                                return;
                            }
                            changePlayer(copy);
                            undoMove(copy);
                            nodeDestroy(child);
                        }
                    }
                }
            }
        }
    }
    gameDestroy(&copy);
}

moveNode bestMove(ChessGame *game, int maxDepth, bool isExpertLevel) {
    moveNode bestMove;
    int bestScoreSoFar = INT_MIN;
    Position src, dest;
    src.row = dest.row = 100;
    src.column = dest.column = 'Z';
    bestMove.source = src;
    bestMove.destination = dest;
    bestMove.destSoldier = 'Z';
    if (maxDepth == 5)
        maxDepth--;
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
                    dest.column = 'A' + j;
                    if (isValidMove(copy, src, dest)) {

                        setMove(copy, src, dest);

                        if (firstValid) {
                            bestMove= copy->history->moves[copy->history->actualSize-1];
                            firstValid = false;
                        }

                        if (maxDepth == 1) {// no recursion
                            int moveScore = scoringFunction(copy, isExpertLevel);
                            if (moveScore > bestScoreSoFar) {
                                bestScoreSoFar = moveScore;
                                bestMove= copy->history->moves[copy->history->actualSize-1];
                            }
                        } else {
                            changePlayer(copy);
                            MiniMaxNode *child = createNode(currentAlpha, INT_MAX, false, copy);
                            updateAlphaBeta(child, isExpertLevel, maxDepth - 1);
                            if (child->beta > currentAlpha) {
                                currentAlpha = child->beta;
                                bestMove= copy->history->moves[copy->history->actualSize-1];
                            }
                            changePlayer(copy);
                            nodeDestroy(child);
                        }
                        undoMove(copy);
                    }
                }
            }
        }
    }
    gameDestroy(&copy);
    return bestMove;
}
