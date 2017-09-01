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


    game->gameBoard[0][0] = game->gameBoard[0][GAME_SIZE-1] = ROOK_WHITE;
    game->gameBoard[GAME_SIZE-1][0] = game->gameBoard[GAME_SIZE-1][GAME_SIZE-1] =  ROOK_BLACK;
    game->gameBoard[0][1] = game->gameBoard[0][GAME_SIZE-2] = KNIGHT_WHITE;
    game->gameBoard[GAME_SIZE-1][1] = game->gameBoard[GAME_SIZE-1][GAME_SIZE-2] =  KNIGHT_BLACK;
    game->gameBoard[0][2] = game->gameBoard[0][GAME_SIZE-3] = BISHOP_WHITE;
    game->gameBoard[GAME_SIZE-1][2] = game->gameBoard[GAME_SIZE-1][GAME_SIZE-3] =  BISHOP_BLACK;
    game->gameBoard[0][3] = QUEEN_WHITE; game->gameBoard[GAME_SIZE-1][3] = QUEEEN_BLACK;
    game->gameBoard[0][4] = KING_WHITE; game->gameBoard[GAME_SIZE-1][4] = KNIGHT_BLACK;

    for (int j = 0; j < GAME_SIZE; j++) {
        game->gameBoard[1][j] = PAWN_WHITE;
        game->gameBoard[GAME_SIZE-2][j] = PAWN_BLACK;
        for (int i = 2; i<GAME_SIZE-2; i++)
            game->gameBoard[i][j] = EMPTY_ENTRY;
    }
    game->score = 0;
    return game;
}


CHESS_MESSAGE printBoard(ChessGame *src){
    if (src==NULL)
        return INVALID_ARGUMENT;
    char toBePrinted[GAME_SIZE + 2][GAME_SIZE * 2 + 4];

    for (int i=GAME_SIZE-1;i>=0;i--){
        toBePrinted[i][0] = i+49;

    }
    return INVALID_ARGUMENT;
}