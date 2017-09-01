#include "ChessGame.h"

ChessGame *gameCreate(int historySize) {
    if (historySize <= 0)
        return NULL;
    ChessGame *game = (ChessGame *) malloc(sizeof(ChessGame));
    if (game == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }
    game->history = createChessHistory(historySize);
    game->currentPlayer = WHITE_PLAYER;


    game->gameBoard[0][0] = game->gameBoard[0][GAME_SIZE - 1] = ROOK_WHITE;
    game->gameBoard[GAME_SIZE - 1][0] = game->gameBoard[GAME_SIZE - 1][GAME_SIZE - 1] = ROOK_BLACK;
    game->gameBoard[0][1] = game->gameBoard[0][GAME_SIZE - 2] = KNIGHT_WHITE;
    game->gameBoard[GAME_SIZE - 1][1] = game->gameBoard[GAME_SIZE - 1][GAME_SIZE - 2] = KNIGHT_BLACK;
    game->gameBoard[0][2] = game->gameBoard[0][GAME_SIZE - 3] = BISHOP_WHITE;
    game->gameBoard[GAME_SIZE - 1][2] = game->gameBoard[GAME_SIZE - 1][GAME_SIZE - 3] = BISHOP_BLACK;
    game->gameBoard[0][3] = QUEEN_WHITE;
    game->gameBoard[GAME_SIZE - 1][3] = QUEEEN_BLACK;
    game->gameBoard[0][4] = KING_WHITE;
    game->gameBoard[GAME_SIZE - 1][4] = KING_BLACK;

    for (int j = 0; j < GAME_SIZE; j++) {
        game->gameBoard[1][j] = PAWN_WHITE;
        game->gameBoard[GAME_SIZE - 2][j] = PAWN_BLACK;
        for (int i = 2; i < GAME_SIZE - 2; i++)
            game->gameBoard[i][j] = EMPTY_ENTRY;
    }
    game->score = 0;
    game->whiteKnigPos.row = 0; game->whiteKnigPos.column = 4;
    game->blackKnigPos.row = 7; game->blackKnigPos.column = 4;

    return game;
}

ChessGame *gameCopy(ChessGame *src) {
    if (src == NULL)
        return NULL;
    ChessGame *copy = (ChessGame *) malloc(sizeof(ChessGame));
    if (copy == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            copy->gameBoard[i][j] = src->gameBoard[i][j];
        }
    }
    copy->currentPlayer = src->currentPlayer;
    copy->history = copyChessHistory(src->history);
    if (copy->history == NULL)
        return NULL;

    copy->score = src->score;
    copy->whiteKnigPos.row = src->whiteKnigPos.row; copy->whiteKnigPos.column = src->whiteKnigPos.column;
    copy->blackKnigPos.row = src->blackKnigPos.row; copy->blackKnigPos.column = src->blackKnigPos.column;

    return copy;
}

void gameDestroy(ChessGame *src) {
    if (src != NULL) {
        destroyChessHistory(src->history);
        free(src);
    }
}

CHESS_MESSAGE printBoard(ChessGame *src) {
    if (src == NULL)
        return INVALID_ARGUMENT;
    char toBePrinted[GAME_SIZE][GAME_SIZE * 2 + 4];

    // board frame
    for (int i = 0; i < GAME_SIZE; i++) {
        toBePrinted[i][0] = 56 - i;
        toBePrinted[i][1] = toBePrinted[i][GAME_SIZE * 2 + 3] = '|';
    }

    // spaces
    for (int i = GAME_SIZE - 1; i >= 0; i--) {
        for (int j = 2; j < GAME_SIZE * 2 + 4; j += 2)
            toBePrinted[i][j] = ' ';
    }

    // pawns
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 3; j < GAME_SIZE + 3; j++) {
            toBePrinted[i][2 * j - 3] = src->gameBoard[GAME_SIZE - i - 1][j - 3];
        }
    }

    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE * 2 + 4; j++) {
            printf("%c", toBePrinted[i][j]);
        }
        printf("\n");
    }

    printf("  -----------------\n");
    printf("   A B C D E F G H   \n");

    return SUCCESS;
}


int getPlayer(char soldier){
    if (soldier == EMPTY_ENTRY)
        return EMPTY_SQUARE;
    if (isupper(soldier) == 0)
        return WHITE_PLAYER;
    return BLACK_PLAYER;
}

CHESS_MESSAGE movePiece(ChessGame *game, Position src, Position dest){
    if (game==NULL)
        return INVALID_ARGUMENT;
    game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)] = game->gameBoard[GET_ROW(src)][GET_COLUMN(src)];
    game->gameBoard[GET_ROW(src)][GET_COLUMN(src)] = EMPTY_ENTRY;
    return SUCCESS;
}

bool myKingUnderThreat(ChessGame *game){// TODO
    return false;
}

bool isValidMove_King(ChessGame* game, Position src, Position dest){
    if (game==NULL)
        return false;
    if (game->currentPlayer != getPlayer(game->gameBoard[GET_ROW(src)][GET_COLUMN(src)]))
        return false;
    if (dest.column == src.column && dest.row == src.row)
        return false;
    if (abs(dest.column - src.column) <= 1 && abs(dest.row-src.row)<=1){
        char destSoldier = game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)];
        if (game->currentPlayer == getPlayer(destSoldier))
            return false;
        if (destSoldier == KING_BLACK || destSoldier == KING_WHITE) // its in the right color already
            return true;
        ChessGame* copy = gameCopy(game);
        if (movePiece(copy, src, dest)==SUCCESS) {
            if (!myKingUnderThreat(copy)) {
                gameDestroy(copy);
                return true;
            }
        }
        gameDestroy(copy);
    }
    return false;
}
bool isValidMove_Queen(ChessGame* game, Position src, Position dest);
bool isValidMove_Knight(ChessGame* game, Position source, Position dest);
bool isValidMove_Bishop(ChessGame* game, Position source, Position dest);
bool isValidMove_Rook(ChessGame* game, Position source, Position dest);


bool isValidMove_Pawn(ChessGame* game, Position src, Position dest){
    if (game==NULL)
        return false;

    int srcCol = GET_COLUMN(src); int srcRow = GET_ROW(src);
    int destCol = GET_COLUMN(dest); int destRow = GET_ROW(dest);

    if (srcCol==destCol){
        if (destRow-srcRow==2 && )
    }
    else if (abs(srcCol-destCol)==1){ // attack

    }
    return false;

}