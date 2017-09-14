
#include <stdio.h>
#include <stdlib.h>
#include "ChessGame.h"
#include "ChessParser.h"
#include "ChessHistory.h"

ChessHistory *createChessHistory(int maxSize) {
    if (maxSize <= 0) {
        return NULL;
    }
    ChessHistory *history = (ChessHistory *) malloc(sizeof(ChessHistory));
    if (history == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }
    history->maxSize = maxSize;
    history->actualSize = 0;
    history->moves = (HistoryNode *) malloc(maxSize * sizeof(HistoryNode));
    if (history->moves == NULL) {
        free(history);
        printf("%s", MALLOC_ERROR);
        return NULL;
    }

    return history;
}

ChessHistory *copyChessHistory(ChessHistory *source) {
    if (source == NULL)
        return NULL;
    ChessHistory *history = (ChessHistory *) malloc(sizeof(ChessHistory));
    if (history == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }
    history->moves = (HistoryNode *) malloc(source->maxSize * sizeof(HistoryNode));
    if (history->moves == NULL) {
        free(history);
        printf("%s", MALLOC_ERROR);
        return NULL;
    }
    for (int i = 0; i < source->actualSize; i++)
        history->moves[i] = source->moves[i];
    history->actualSize = source->actualSize;
    history->maxSize = source->maxSize;
    return history;
}

void destroyChessHistory(ChessHistory **source) {
    if (source == NULL || *source == NULL)
        return;
    free ((*source)->moves);
    free(*source);
    *source = NULL;
    return;
}

CHESS_MESSAGE addMovetoHistory(ChessHistory *source, HistoryNode move) {
    if (source == NULL || source->maxSize <= 0)
        return INVALID_ARGUMENT;

    int actualSize = source->actualSize;
    int maxSize = source->maxSize;

    if (actualSize < maxSize) {
        source->moves[actualSize] = move;
        source->actualSize++;
    } else {
        for (int i = 0; i < actualSize - 1; i++)
            source->moves[i] = source->moves[i + 1];
        source->moves[actualSize - 1] = move;
    }
    return SUCCESS;
}

HistoryNode *removeRecentMove(ChessHistory *source) {
    if (source == NULL || source->actualSize < 1)
        return NULL;
    source->actualSize--;
    return &(source->moves[source->actualSize]);
}

bool isHistoryEmpty(ChessHistory *source) {
    return source->actualSize == 0;
}


