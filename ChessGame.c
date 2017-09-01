#include "ChessGame.h"

ChessGame *gameCreate(int historySize) {
    if (historySize <= 0)
        return NULL;
    ChessGame *game = (ChessGame *) malloc(sizeof(ChessGame));
    if (game == NULL) {
        printf("Error: malloc has failed");
        return NULL;
    }
    game->history = createChessHistory(historySize);
    game->currentPlayer = WHITE_PLAYER;
    for (int i = 0; i < CHESS_GAME_SIZE; i++) {

    }
}