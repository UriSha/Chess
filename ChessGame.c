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
    game->gameBoard[GAME_SIZE - 1][3] = QUEEN_BLACK;
    game->gameBoard[0][4] = KING_WHITE;
    game->gameBoard[GAME_SIZE - 1][4] = KING_BLACK;

    for (int j = 0; j < GAME_SIZE; j++) {
        game->gameBoard[1][j] = PAWN_WHITE;
        game->gameBoard[GAME_SIZE - 2][j] = PAWN_BLACK;
        for (int i = 2; i < GAME_SIZE - 2; i++)
            game->gameBoard[i][j] = EMPTY_ENTRY;
    }
    game->score = 0;
    game->whiteKnigPos.row = 1;
    game->whiteKnigPos.column = 'E';
    game->blackKnigPos.row = 8;
    game->blackKnigPos.column = 'E';

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
    copy->whiteKnigPos.row = src->whiteKnigPos.row;
    copy->whiteKnigPos.column = src->whiteKnigPos.column;
    copy->blackKnigPos.row = src->blackKnigPos.row;
    copy->blackKnigPos.column = src->blackKnigPos.column;

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


int getPlayer(char soldier) {
    if (soldier == EMPTY_ENTRY)
        return EMPTY_SQUARE;
    if (isupper(soldier) == 0)
        return WHITE_PLAYER;
    return BLACK_PLAYER;
}

CHESS_MESSAGE movePiece(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return INVALID_ARGUMENT;
    char srcSoldier = game->gameBoard[GET_ROW(src)][GET_COLUMN(src)];
    if (srcSoldier == KING_WHITE) {
        game->whiteKnigPos.row = dest.row;
        game->whiteKnigPos.column = dest.column;
    } else if (srcSoldier == KING_BLACK) {
        game->blackKnigPos.row = dest.row;
        game->blackKnigPos.column = dest.column;
    }
    game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)] = srcSoldier;
    game->gameBoard[GET_ROW(src)][GET_COLUMN(src)] = EMPTY_ENTRY;
    return SUCCESS;
}

char getSoldier(char board[GAME_SIZE][GAME_SIZE], int row, int col) {
    if (board == NULL)
        return '\0';
    if (row < 0 || row > GAME_SIZE - 1 || col < 0 || col > GAME_SIZE - 1)
        return '\0';
    return board[row][col];
}

char getOtherKnight(int player) {
    return (char) (player == WHITE_PLAYER ? KNIGHT_BLACK : KNIGHT_WHITE);
}

char getOtherKing(int player) {
    return (char) (player == WHITE_PLAYER ? KING_BLACK : KING_WHITE);
}

char getOtherQueen(int player) {
    return (char) (player == WHITE_PLAYER ? QUEEN_BLACK : QUEEN_WHITE);
}

char getOtherBishop(int player) {
    return (char) (player == WHITE_PLAYER ? BISHOP_BLACK : BISHOP_WHITE);
}

char getOtherRook(int player) {
    return (char) (player == WHITE_PLAYER ? ROOK_BLACK : ROOK_WHITE);
}
char getOtherPawn(int player) {
    return (char) (player == WHITE_PLAYER ? PAWN_BLACK : PAWN_WHITE);
}
int getOtherPlayer(int player) {
    return  player == WHITE_PLAYER ? BLACK_PLAYER : WHITE_PLAYER;
}

bool knightThreatsKing(ChessGame *game, int kingRow, int kingCol) {
    // knights
    if (getSoldier(game->gameBoard, kingRow + 1, kingCol + 2) == getOtherKnight(game->currentPlayer) ||
        getSoldier(game->gameBoard, kingRow + 1, kingCol - 2) == getOtherKnight(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, kingRow - 1, kingCol + 2) == getOtherKnight(game->currentPlayer) ||
        getSoldier(game->gameBoard, kingRow - 1, kingCol - 2) == getOtherKnight(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, kingRow + 2, kingCol + 1) == getOtherKnight(game->currentPlayer) ||
        getSoldier(game->gameBoard, kingRow + 2, kingCol - 1) == getOtherKnight(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, kingRow - 2, kingCol + 1) == getOtherKnight(game->currentPlayer) ||
        getSoldier(game->gameBoard, kingRow - 2, kingCol - 1) == getOtherKnight(game->currentPlayer))
        return true;
    return false;
}

bool kingThreatsKing(ChessGame *game, int kingRow, int kingCol) {

    if (getSoldier(game->gameBoard, kingRow, kingCol + 1) == getOtherKing(game->currentPlayer) ||
        getSoldier(game->gameBoard, kingRow, kingCol - 1) == getOtherKing(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, kingRow + 1, kingCol) == getOtherKing(game->currentPlayer) ||
        getSoldier(game->gameBoard, kingRow - 1, kingCol) == getOtherKing(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, kingRow + 1, kingCol + 1) == getOtherKing(game->currentPlayer) ||
        getSoldier(game->gameBoard, kingRow - 1, kingCol - 1) == getOtherKing(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, kingRow + 1, kingCol - 1) == getOtherKing(game->currentPlayer) ||
        getSoldier(game->gameBoard, kingRow - 1, kingCol + 1) == getOtherKing(game->currentPlayer))
        return true;
return false;
}

bool QBRThreatsKing(ChessGame *game, int kingRow, int kingCol, bool diagonal) {//TODO make a function for while
    int curRow = kingRow;
    int curCol = kingCol;
    char danger;
    char safe;
    if (diagonal){
        danger = getOtherBishop(game->currentPlayer);
        safe = getOtherRook(game->currentPlayer);
    }
    else {
        danger = getOtherRook(game->currentPlayer);
        safe = getOtherBishop(game->currentPlayer);
    }

    do {
        if (diagonal) {//up right
            curRow++;
            curCol++;
        }
        else {//up
            curRow++;
        }
        if (getSoldier(game->gameBoard, curRow, curCol) == danger ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherQueen(game->currentPlayer))
            return true;
        if (getSoldier(game->gameBoard, curRow, curCol) == getOtherPawn(game->currentPlayer) ||
            getSoldier(game->gameBoard, curRow, curCol) == safe ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherKnight(game->currentPlayer))
            break;
    } while (getSoldier(game->gameBoard, curRow, curCol) != '\0' &&
             getPlayer(game->gameBoard[curRow][curCol] != game->currentPlayer));
    // reset
    curRow = kingRow;
    curCol = kingCol;
    do {
        if (diagonal) {//down right
            curRow--;
            curCol++;
        }
        else {//down
            curRow--;
        }
        if (getSoldier(game->gameBoard, curRow, curCol) == danger ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherQueen(game->currentPlayer))
            return true;
        if (getSoldier(game->gameBoard, curRow, curCol) == getOtherPawn(game->currentPlayer) ||
            getSoldier(game->gameBoard, curRow, curCol) == safe ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherKnight(game->currentPlayer))
            break;
    } while (getSoldier(game->gameBoard, curRow, curCol) != '\0' &&
             getPlayer(game->gameBoard[curRow][curCol] != game->currentPlayer));
    curRow = kingRow;
    curCol = kingCol;
    do {
        if (diagonal) {//down left
            curRow--;
            curCol--;
        }
        else {//left
            curCol--;
        }
        if (getSoldier(game->gameBoard, curRow, curCol) == danger ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherQueen(game->currentPlayer))
            return true;
        if (getSoldier(game->gameBoard, curRow, curCol) == getOtherPawn(game->currentPlayer) ||
            getSoldier(game->gameBoard, curRow, curCol) == safe ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherKnight(game->currentPlayer))
            break;
    } while (getSoldier(game->gameBoard, curRow, curCol) != '\0' &&
             getPlayer(game->gameBoard[curRow][curCol] != game->currentPlayer));
    // reset
    curRow = kingRow;
    curCol = kingCol;
    do {
        if (diagonal) {//up left
            curRow++;
            curCol--;
        }
        else {//right
            curCol++;
        }
        if (getSoldier(game->gameBoard, curRow, curCol) == danger ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherQueen(game->currentPlayer))
            return true;
        if (getSoldier(game->gameBoard, curRow, curCol) == getOtherPawn(game->currentPlayer) ||
            getSoldier(game->gameBoard, curRow, curCol) == safe ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherKnight(game->currentPlayer))
            break;
    } while (getSoldier(game->gameBoard, curRow, curCol) != '\0' &&
             getPlayer(game->gameBoard[curRow][curCol] != game->currentPlayer));
    return false;
}

bool myKingUnderThreat(ChessGame *game) {
    if (game == NULL)
        return false;

    int kingCol = 100;
    int kingRow = 100;
    if (game->currentPlayer == WHITE_PLAYER) {
        kingCol = GET_COLUMN(game->whiteKnigPos);
        kingRow = GET_ROW(game->whiteKnigPos);

        // pawns
        if (game->gameBoard[kingRow + 1][kingCol + 1] == PAWN_BLACK ||
            game->gameBoard[kingRow + 1][kingCol - 1] == PAWN_BLACK)
            return true;
    } else if (game->currentPlayer == BLACK_PLAYER) {
        kingCol = GET_COLUMN(game->blackKnigPos);
        kingRow = GET_ROW(game->blackKnigPos);
        // pawns
        if (game->gameBoard[kingRow - 1][kingCol + 1] == PAWN_WHITE ||
            game->gameBoard[kingRow - 1][kingCol - 1] == PAWN_WHITE)
            return true;
    }
    return (knightThreatsKing(game, kingRow, kingCol) || QBRThreatsKing(game, kingRow, kingCol, 1) ||
            QBRThreatsKing(game, kingRow, kingCol, 0) || kingThreatsKing(game, kingRow, kingCol));
}

bool isValidMove_King(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return false;
    return (abs(dest.column - src.column) <= 1 && abs(dest.row - src.row) <= 1);
}

bool isValidMove_Queen(ChessGame *game, Position src, Position dest) {
    return (isValidMove_Rook(game, src, dest) || isValidMove_Bishop(game, src, dest));
}


bool isValidMove_Knight(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return false;

    int srcCol = GET_COLUMN(src);
    int srcRow = GET_ROW(src);
    int destCol = GET_COLUMN(dest);
    int destRow = GET_ROW(dest);

    if (srcCol + 1 == destCol && abs(srcRow - destRow) == 2)
        return true;
    if (srcCol - 1 == destCol && abs(srcRow - destRow) == 2)
        return true;
    if (srcCol + 2 == destCol && abs(srcRow - destRow) == 1)
        return true;
    if (srcCol - 2 == destCol && abs(srcRow - destRow) == 1)
        return true;

    return false;
}

bool isValidMove_Bishop(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return false;

    int srcCol = GET_COLUMN(src);
    int srcRow = GET_ROW(src);
    int destCol = GET_COLUMN(dest);
    int destRow = GET_ROW(dest);

    if (abs(destCol - srcCol) != abs(destRow - srcRow))
        return false;

    int curCol = srcCol;
    int curRow = srcRow;

    if (destCol > srcCol && destRow > srcRow) { // up-right
        curCol++;
        curRow++;
        while (destCol > curCol) {
            if (game->gameBoard[curRow][curCol] != EMPTY_ENTRY)
                return false;
            curCol++;
            curRow++;
        }
        return true;
    } else if (destCol < srcCol && destRow > srcRow) { // up-left
        curCol--;
        curRow++;
        while (destCol < curCol) {
            if (game->gameBoard[curRow][curCol] != EMPTY_ENTRY)
                return false;
            curCol--;
            curRow++;
        }
        return true;

    } else if (destCol > srcCol && destRow < srcRow) { // down-right
        curCol++;
        curRow--;
        while (destCol > curCol) {
            if (game->gameBoard[curRow][curCol] != EMPTY_ENTRY)
                return false;
            curCol++;
            curRow--;
        }
        return true;
    } else if (destCol < srcCol && destRow < srcRow) { // down-left
        curCol--;
        curRow--;
        while (destCol < curCol) {
            if (game->gameBoard[curRow][curCol] != EMPTY_ENTRY)
                return false;
            curCol--;
            curRow--;
        }
        return true;
    }
    return false;
}

bool isValidMove_Rook(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return false;

    int srcCol = GET_COLUMN(src);
    int srcRow = GET_ROW(src);
    int destCol = GET_COLUMN(dest);
    int destRow = GET_ROW(dest);

    if (srcCol == destCol) {
        int currentRow;
        if (destRow > srcRow) { // going up
            currentRow = srcRow + 1;
            while (destRow > currentRow) {
                if (game->gameBoard[currentRow][srcCol] != EMPTY_ENTRY)
                    return false;
                currentRow++;
            }
            return true;
        } else { // going down
            currentRow = srcRow - 1;
            while (destRow < currentRow) {
                if (game->gameBoard[currentRow][srcCol] != EMPTY_ENTRY)
                    return false;
                currentRow--;
            }
            return true;
        }
    } else if (srcRow == destRow) {
        int currentCol;
        if (destCol > srcCol) { // going right
            currentCol = srcCol + 1;
            while (destCol > currentCol) {
                if (game->gameBoard[srcRow][currentCol] != EMPTY_ENTRY)
                    return false;
                currentCol++;
            }
            return true;
        } else { // going left
            currentCol = srcCol - 1;
            while (destCol < currentCol) {
                if (game->gameBoard[srcRow][currentCol] != EMPTY_ENTRY)
                    return false;
                currentCol--;
            }
            return true;
        }
    }
    return false;
}


bool isValidMove_Pawn(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return false;

    int srcCol = GET_COLUMN(src);
    int srcRow = GET_ROW(src);
    int destCol = GET_COLUMN(dest);
    int destRow = GET_ROW(dest);

    // moving forward
    if (srcCol == destCol && game->gameBoard[destRow][destCol] == EMPTY_ENTRY) {
        if (game->currentPlayer == WHITE_PLAYER) {
            if (destRow - srcRow == 2 && game->gameBoard[srcRow + 1][srcCol] == EMPTY_ENTRY && srcRow == 1)
                return true;
            if (destRow - srcRow == 1)
                return true;
        } else if (game->currentPlayer == BLACK_PLAYER) {
            if (destRow - srcRow == -2 && game->gameBoard[srcRow - 1][srcCol] == EMPTY_ENTRY && srcRow == GAME_SIZE - 2)
                return true;
            if (destRow - srcRow == -1)
                return true;
        }

    }
        // diagonal attack
    else if (abs(srcCol - destCol) == 1) {
        if (game->currentPlayer == WHITE_PLAYER) {
            if (destRow - srcRow == 1 && getPlayer(game->gameBoard[destRow][destCol]) == BLACK_PLAYER)
                return true;
        } else if (game->currentPlayer == BLACK_PLAYER) {
            if (destRow - srcRow == -1 && getPlayer(game->gameBoard[destRow][destCol]) == WHITE_PLAYER)
                return true;
        }
    }

    return false;

}

bool isValidMove(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return false;
    if (game->currentPlayer != getPlayer(game->gameBoard[GET_ROW(src)][GET_COLUMN(src)]))
        return false;
    if (game->currentPlayer == getPlayer(game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)]))
        return false;

    bool result;

    switch (game->gameBoard[GET_ROW(src)][GET_COLUMN(src)]) {
        case PAWN_WHITE:
        case PAWN_BLACK:
            result = isValidMove_Pawn(game, src, dest);
            break;
        case BISHOP_WHITE:
        case BISHOP_BLACK:
            result = isValidMove_Bishop(game, src, dest);
            break;
        case KNIGHT_WHITE:
        case KNIGHT_BLACK:
            result = isValidMove_Knight(game, src, dest);
            break;
        case ROOK_WHITE:
        case ROOK_BLACK:
            result = isValidMove_Rook(game, src, dest);
            break;
        case QUEEN_WHITE:
        case QUEEN_BLACK:
            result = isValidMove_Queen(game, src, dest);
            break;
        case KING_WHITE:
        case KING_BLACK:
            result = isValidMove_King(game, src, dest);
            break;
        default:
            result = false;
    }
    if (result) {
        if (game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)] == KING_BLACK ||
            game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)] == KING_WHITE)
            return result;
        ChessGame *copy = gameCopy(game);
        if (movePiece(copy, src, dest) == SUCCESS) {
            if (myKingUnderThreat(copy))
                result = false;
        }
        gameDestroy(copy);
    }
    return result;
}