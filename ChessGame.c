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
    game->whiteKingPos.row = WHITE_INITIAL_ROW;
    game->whiteKingPos.column = KING_INITIAL_COL_CHAR;
    game->blackKingPos.row = BLACK_INITIAL_ROW;
    game->blackKingPos.column = KING_INITIAL_COL_CHAR;
    game->leftBlackRookMoved = game->rightBlackRookMoved = false;
    game->leftWhiteRookMoved = game->rightWhiteRookMoved = false;
    game->whiteCastle = game->blackCastle = true;
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
    copy->whiteKingPos.row = src->whiteKingPos.row;
    copy->whiteKingPos.column = src->whiteKingPos.column;
    copy->blackKingPos.row = src->blackKingPos.row;
    copy->blackKingPos.column = src->blackKingPos.column;
    copy->blackCastle = src->blackCastle;
    copy->whiteCastle = src->whiteCastle;
    copy->rightBlackRookMoved = src->rightBlackRookMoved;
    copy->leftWhiteRookMoved = src->leftWhiteRookMoved;
    copy->leftBlackRookMoved = src->leftBlackRookMoved;
    copy->rightWhiteRookMoved = src->rightWhiteRookMoved;

    return copy;
}

void gameDestroy(ChessGame **src) {
    if (src == NULL || *src == NULL)
        return;

    destroyChessHistory(&((*src)->history));
    free(*src);
    *src = NULL;
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
        game->whiteKingPos.row = dest.row;
        game->whiteKingPos.column = dest.column;
        game->whiteCastle = 0;

    } else if (srcSoldier == KING_BLACK) {
        game->blackKingPos.row = dest.row;
        game->blackKingPos.column = dest.column;
        game->blackCastle = 0;
    }

    game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)] = game->gameBoard[GET_ROW(src)][GET_COLUMN(src)];
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
    return player == WHITE_PLAYER ? BLACK_PLAYER : WHITE_PLAYER;
}

bool knightThreatsPosition(ChessGame *game, int row, int col) {
    // knights
    if (getSoldier(game->gameBoard, row + 1, col + 2) == getOtherKnight(game->currentPlayer) ||
        getSoldier(game->gameBoard, row + 1, col - 2) == getOtherKnight(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, row - 1, col + 2) == getOtherKnight(game->currentPlayer) ||
        getSoldier(game->gameBoard, row - 1, col - 2) == getOtherKnight(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, row + 2, col + 1) == getOtherKnight(game->currentPlayer) ||
        getSoldier(game->gameBoard, row + 2, col - 1) == getOtherKnight(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, row - 2, col + 1) == getOtherKnight(game->currentPlayer) ||
        getSoldier(game->gameBoard, row - 2, col - 1) == getOtherKnight(game->currentPlayer))
        return true;
    return false;
}

bool kingThreatsPosition(ChessGame *game, int row, int col) {

    if (getSoldier(game->gameBoard, row, col + 1) == getOtherKing(game->currentPlayer) ||
        getSoldier(game->gameBoard, row, col - 1) == getOtherKing(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, row + 1, col) == getOtherKing(game->currentPlayer) ||
        getSoldier(game->gameBoard, row - 1, col) == getOtherKing(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, row + 1, col + 1) == getOtherKing(game->currentPlayer) ||
        getSoldier(game->gameBoard, row - 1, col - 1) == getOtherKing(game->currentPlayer))
        return true;
    if (getSoldier(game->gameBoard, row + 1, col - 1) == getOtherKing(game->currentPlayer) ||
        getSoldier(game->gameBoard, row - 1, col + 1) == getOtherKing(game->currentPlayer))
        return true;
    return false;
}

bool diagonalOrHorizontalThreat(ChessGame *game, int rowPlusMinus, int colPlusMinus, int curRow, int curCol) {
    char danger, safe;

    if (rowPlusMinus != 0 && colPlusMinus != 0) {
        danger = getOtherBishop(game->currentPlayer);
        safe = getOtherRook(game->currentPlayer);
    } else {
        danger = getOtherRook(game->currentPlayer);
        safe = getOtherBishop(game->currentPlayer);
    }
    do {
        curRow += rowPlusMinus;
        curCol += colPlusMinus;
        if (getSoldier(game->gameBoard, curRow, curCol) == danger ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherQueen(game->currentPlayer))
            return true;
        if (getSoldier(game->gameBoard, curRow, curCol) == getOtherPawn(game->currentPlayer) ||
            getSoldier(game->gameBoard, curRow, curCol) == safe ||
            getSoldier(game->gameBoard, curRow, curCol) == getOtherKnight(game->currentPlayer))
            break;
    } while (getSoldier(game->gameBoard, curRow, curCol) != '\0' &&
             getPlayer(game->gameBoard[curRow][curCol]) != game->currentPlayer);
    return false;
}

bool QBRThreatsPosition(ChessGame *game, int row, int col) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (diagonalOrHorizontalThreat(game, i, j, row, col))
                return true;
        }
    }
    return false;
}

bool myPositionUnderThreat(ChessGame *game, Position pos) {
    if (game == NULL)
        return false;
    int col = GET_COLUMN(pos);
    int row = GET_ROW(pos);
    int plusMinus = game->currentPlayer == WHITE_PLAYER ? 1 : -1;
    // pawns
    if (getSoldier(game->gameBoard, row + plusMinus, col + plusMinus) == getOtherPawn(game->currentPlayer) ||
        getSoldier(game->gameBoard, row + plusMinus, col - plusMinus) == getOtherPawn(game->currentPlayer))
        return true;
    return (knightThreatsPosition(game, row, col) || QBRThreatsPosition(game, row, col) ||
            QBRThreatsPosition(game, row, col) || kingThreatsPosition(game, row, col));
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
    }
    if (destCol < srcCol && destRow > srcRow) { // up-left
        curCol--;
        curRow++;
        while (destCol < curCol) {
            if (game->gameBoard[curRow][curCol] != EMPTY_ENTRY)
                return false;
            curCol--;
            curRow++;
        }
        return true;

    }
    if (destCol > srcCol && destRow < srcRow) { // down-right
        curCol++;
        curRow--;
        while (destCol > curCol) {
            if (game->gameBoard[curRow][curCol] != EMPTY_ENTRY)
                return false;
            curCol++;
            curRow--;
        }
        return true;
    }
    if (destCol < srcCol && destRow < srcRow) { // down-left
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
        }
        // going down
        currentRow = srcRow - 1;
        while (destRow < currentRow) {
            if (game->gameBoard[currentRow][srcCol] != EMPTY_ENTRY)
                return false;
            currentRow--;
        }
        return true;
    }
    if (srcRow == destRow) {
        int currentCol;
        if (destCol > srcCol) { // going right
            currentCol = srcCol + 1;
            while (destCol > currentCol) {
                if (game->gameBoard[srcRow][currentCol] != EMPTY_ENTRY)
                    return false;
                currentCol++;
            }
            return true;
        }
        // going left
        currentCol = srcCol - 1;
        while (destCol < currentCol) {
            if (game->gameBoard[srcRow][currentCol] != EMPTY_ENTRY)
                return false;
            currentCol--;
        }
        return true;
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
        return isCastleMove(game, src, dest);


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
            Position kingPos = copy->currentPlayer == WHITE_PLAYER ?
                               copy->whiteKingPos : copy->blackKingPos;
            if (myPositionUnderThreat(copy, kingPos))
                result = false;
        }
        gameDestroy(&copy);
    }
    return result;
}

void updateScore(char soldierDied, ChessGame *game) {
    int isBlackDied = isupper(soldierDied) == 0 ? -1 : 1;

    switch (soldierDied) {
        case PAWN_BLACK :
        case PAWN_WHITE :
            game->score += (1 * isBlackDied);
            break;
        case ROOK_BLACK :
        case ROOK_WHITE :
            game->score += (5 * isBlackDied);
            break;
        case KNIGHT_BLACK :
        case KNIGHT_WHITE :
            game->score += (3 * isBlackDied);
            break;
        case BISHOP_BLACK :
        case BISHOP_WHITE :
            game->score += (3 * isBlackDied);
            break;
        case QUEEN_BLACK :
        case QUEEN_WHITE :
            game->score += (9 * isBlackDied);
            break;
        case KING_BLACK :
        case KING_WHITE :
            game->score += (100 * isBlackDied);
            break;
        default :
            return;
    }


}

void doCastleMove(ChessGame *game, Position src, Position dest, moveNode *move) {
    char srcSoldier = game->gameBoard[GET_ROW(src)][GET_COLUMN(src)];
    int myRow = game->currentPlayer == WHITE_PLAYER ? WHITE_INITIAL_ROW : BLACK_INITIAL_ROW;

    Position kingDest;
    Position rookDest;
    kingDest.row = myRow;
    rookDest.row = myRow;


    if (srcSoldier == KING_WHITE || srcSoldier == KING_BLACK) {
        if (dest.column == 'A') { // left castling
            if (srcSoldier == KING_WHITE)
                move->turnedOffWhiteLeftCastle = 1;
            else if (srcSoldier == KING_BLACK)
                move->turnedOffBlackLeftCastle = 1;
            kingDest.column = 'C';
            rookDest.column = 'D';
        } else if (dest.column == 'H') {
            if (srcSoldier == KING_WHITE)
                move->turnedOffWhiteRightCastle = 1;
            else if (srcSoldier == KING_BLACK)
                move->turnedOffBlackRightCastle = 1;
            kingDest.column = 'G';
            rookDest.column = 'F';
        }
        movePiece(game, src, kingDest);
        movePiece(game, dest, rookDest);
    } else if (srcSoldier == ROOK_WHITE || srcSoldier == ROOK_BLACK) {
        if (src.column == 'A') { // left castling
            if (srcSoldier == ROOK_WHITE)
                move->turnedOffWhiteLeftCastle = 1;
            else if (srcSoldier == ROOK_BLACK)
                move->turnedOffBlackLeftCastle = 1;
            kingDest.column = 'C';
            rookDest.column = 'D';
        } else if (src.column == 'H') {
            if (srcSoldier == ROOK_WHITE)
                move->turnedOffWhiteRightCastle = 1;
            else if (srcSoldier == ROOK_BLACK)
                move->turnedOffBlackRightCastle = 1;
            kingDest.column = 'G';
            rookDest.column = 'F';
        }
        movePiece(game, dest, kingDest);
        movePiece(game, src, rookDest);
    }
    if (game->currentPlayer == WHITE_PLAYER)
        game->whiteCastle = 0;
    else
        game->blackCastle = 0;
}



void updateCastleFlags(ChessGame *game, moveNode *move) {
    if (move->source.column == 'A') {
        if (move->srcSoldier == ROOK_WHITE) {
            if (game->leftWhiteRookMoved == 0)
                move->turnedOffWhiteLeftCastle = 1;
            else
                move->turnedOffWhiteLeftCastle = 0;
        } else if (move->srcSoldier == ROOK_BLACK) {
            if (game->leftBlackRookMoved == 0)
                move->turnedOffBlackLeftCastle = 1;
            else
                move->turnedOffBlackLeftCastle = 0;
        }
    } else if (move->source.column == 'H') {
        if (move->srcSoldier == ROOK_WHITE) {
            if (game->rightWhiteRookMoved == 0)
                move->turnedOffWhiteRightCastle = 1;
            else
                move->turnedOffWhiteRightCastle = 0;
        } else if (move->srcSoldier == ROOK_BLACK) {
            if (game->rightBlackRookMoved == 0)
                move->turnedOffBlackRightCastle = 1;
            else
                move->turnedOffBlackRightCastle = 0;
        }
    } else if (move->source.column == KING_INITIAL_COL_CHAR) {
        if (move->srcSoldier == KING_WHITE) {
            if (game->whiteCastle == 1) {
                move->turnedOffWhiteRightCastle = 1;
                move->turnedOffWhiteLeftCastle = 1;
            } else {
                move->turnedOffWhiteRightCastle = 0;
                move->turnedOffWhiteLeftCastle = 0;
            }
        } else if (move->srcSoldier == KING_BLACK) {
            if (game->blackCastle == 1) {
                move->turnedOffBlackRightCastle = 1;
                move->turnedOffBlackLeftCastle = 1;
            } else {
                move->turnedOffBlackRightCastle = 0;
                move->turnedOffBlackLeftCastle = 0;
            }
        }
    }
}


CHESS_MESSAGE setMove(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return INVALID_ARGUMENT;

    if (!isValidMove(game, src, dest))
        return ILLEGAL_MOVE;

    int otherPlayer = game->currentPlayer == WHITE_PLAYER ? BLACK_PLAYER : WHITE_PLAYER;
    char destSoldier = game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)];
    char srcSoldier = game->gameBoard[GET_ROW(src)][GET_COLUMN(src)];

    if (getPlayer(destSoldier) == otherPlayer)
        updateScore(destSoldier, game);

    moveNode move;
    move.source = src;
    move.destination = dest;
    move.destSoldier = destSoldier;
    move.srcSoldier = srcSoldier;
    move.turnedOffBlackRightCastle = 0;
    move.turnedOffBlackLeftCastle = 0;
    move.turnedOffWhiteRightCastle = 0;
    move.turnedOffWhiteLeftCastle = 0;

    if (isCastleMove(game, src, dest)) {
        doCastleMove(game, src, dest, &move);
    } else {
        updateCastleFlags(game, &move);
        movePiece(game, src, dest);
    }


    if (game->gameBoard[WHITE_INITIAL_ROW - 1][0] != ROOK_WHITE)
        game->leftWhiteRookMoved = true;

    if (game->gameBoard[WHITE_INITIAL_ROW - 1][GAME_SIZE - 1] != ROOK_WHITE)
        game->rightWhiteRookMoved = true;
    if (game->gameBoard[BLACK_INITIAL_ROW - 1][0] != ROOK_BLACK)
        game->leftBlackRookMoved = true;
    if (game->gameBoard[BLACK_INITIAL_ROW - 1][GAME_SIZE - 1] != ROOK_BLACK)
        game->rightBlackRookMoved = true;

    addMovetoHistory(game->history, move);
    return SUCCESS;

}

void changePlayer(ChessGame *game) {
    game->currentPlayer = 1 - game->currentPlayer;
}

bool areThereAnyMoves(ChessGame *game) {

    Position src, dest;
    for (int i = 1; i <= GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            src.row = i;
            src.column = 'A' + j;
            if (getPlayer(game->gameBoard[i - 1][j]) != game->currentPlayer)
                continue;
            for (int k = 1; k <= GAME_SIZE; k++) {
                for (int l = 0; l < GAME_SIZE; l++) {
                    dest.row = k;
                    dest.column = 'A' + l;
                    if (isValidMove(game, src, dest))
                        return true;
                }
            }
        }
    }
    return false;
}

CHESS_MESSAGE checkStatus(ChessGame *game) {
    if (game == NULL)
        return INVALID_ARGUMENT;
    Position kingPos = game->currentPlayer == WHITE_PLAYER ?
                       game->whiteKingPos : game->blackKingPos;
    if (myPositionUnderThreat(game, kingPos)) {
        if (!areThereAnyMoves(game)) {

            return MATE;
        }

        return CHECK;
    }
    if (!areThereAnyMoves(game)) {

        return TIE;
    }
    return CONTINUE;
}

char *getStringFromPosition(Position dest) {
    char *result = (char *) malloc(sizeof(char) * 15);
    if (result == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }
    result[0] = '<';
    result[4] = '>';
    result[1] = (char) (dest.row + '0');
    result[2] = 44;
    result[3] = dest.column;
    result[5] = '\0';
    return result;
}

int getMoves(ChessGame *game, Position *result, Position pos) {
    Position dest;
    int movesCounter = 0;
    for (int i = 1; i <= GAME_SIZE; i++) {
        dest.row = i;
        for (int j = 0; j < GAME_SIZE; j++) {
            dest.column = 'A' + j;
            if (isValidMove(game, pos, dest)) {
                result[movesCounter++] = dest;
            }
        }
    }
    return movesCounter;
}


void printMoves(ChessGame *game, Position pos) {
    if (game == NULL)
        return;
    Position *result = (Position *) malloc(28 * sizeof(Position));//28 is approximately the maximum number of moves
    if (result == NULL) {
        printf("%s", MALLOC_ERROR);
        return;
    }
    int positionCounter = getMoves(game, result, pos);
    if (positionCounter == 0) {
        free(result);
        printf("No available move\n");
        return;
    }
    result = (Position *) realloc(result, positionCounter * sizeof(Position));
    if (result == NULL) {
        printf("%s", MALLOC_ERROR);
        return;
    }
    char **movesArray = (char **) malloc(sizeof(char) * positionCounter);
    if (movesArray == NULL) {
        printf("%s", MALLOC_ERROR);
        return;
    }
    for (int i = 0; i < positionCounter; i++) {
        movesArray[i] = (char *) malloc(sizeof(char) * 15);//15 is maximum length of a row
        if (movesArray[i] == NULL) {
            printf("%s", MALLOC_ERROR);
            return;
        }
    }
    int k = 0;
    char castle1[15] = "";
    char castle2[15] = "";

    for (int i = 0; i < positionCounter; i++, k++) {
        movesArray[k] = getStringFromPosition(result[i]);
        if (movesArray[k] == NULL) {
            for (int i = 0; i < positionCounter; i++)
                free(movesArray[i]);
            free(result);
            return;
        }
        char myKing = (char) (game->currentPlayer == WHITE_PLAYER ? KING_WHITE : KING_BLACK);
        int myKingInitRow = game->currentPlayer == WHITE_PLAYER ? WHITE_INITIAL_ROW - 1 : BLACK_INITIAL_ROW - 1;

        bool castleRight = game->currentPlayer == WHITE_PLAYER ? (game->whiteCastle && !(game->rightWhiteRookMoved)) :
                           (game->blackCastle && !(game->rightBlackRookMoved));
        bool castleLeft = game->currentPlayer == WHITE_PLAYER ? (game->whiteCastle && !(game->leftWhiteRookMoved)) : (
                game->blackCastle && !(game->leftBlackRookMoved));

        if (game->gameBoard[GET_ROW(pos)][GET_COLUMN(pos)] == myKing) {//if get_moves asks for king
            if (pos.column == KING_INITIAL_COL_CHAR && GET_ROW(pos) == myKingInitRow) {
                if (GET_ROW(result[i]) == myKingInitRow) {
                    if (castleRight && result[i].column == 'H') {
                        sprintf(castle2, "castle <%d,H>", result[i].row);
                        k--;
                        continue;
                    }
                    if (castleLeft && GET_COLUMN(result[i]) == 'A') {
                        sprintf(castle1, "castle <%d,A>", result[i].row);
                        k--;
                        continue;
                    }
                }
            }
        } else if (movesArray[k][3] == KING_INITIAL_COL_CHAR &&
                   movesArray[k][1] - '0' == pos.row) { // if get_moves asks for rook
            if (game->gameBoard[GET_ROW(result[i])][GET_COLUMN(result[i])] == myKing) {
                sprintf(castle1, "castle <%d,%c>", result[i].row, pos.column);
                k--;
                continue;
            }
        }

        char soldierDiedOrMyKing = game->gameBoard[GET_ROW(result[i])][GET_COLUMN(result[i])];
        bool someoneDied;
        if (getPlayer(soldierDiedOrMyKing) == game->currentPlayer)
            someoneDied = false;
        else if (getPlayer(soldierDiedOrMyKing) == EMPTY_SQUARE)
            someoneDied = false;
        else
            someoneDied = true;


        ChessGame *copy = gameCopy(game);
        movePiece(copy, pos, result[i]);
        if (myPositionUnderThreat(copy, result[i])) {
            movesArray[k][5] = '*';
            if (someoneDied) {
                movesArray[k][6] = '^';
                movesArray[k][7] = '\0';

            } else
                movesArray[k][6] = '\0';
        } else if (someoneDied) {
            movesArray[k][5] = '^';
            movesArray[k][6] = '\0';
        }
        gameDestroy(&copy);

    }
    if (strcmp(castle1, "") != 0)
        strcpy(movesArray[k++], castle1);
    if (strcmp(castle2, "") != 0)
        strcpy(movesArray[k], castle2);
    for (int i = 0; i < positionCounter; i++)
        printf("%s\n", movesArray[i]);
    for (int i = 0; i < positionCounter; i++)
        free(movesArray[i]);

    free(result);
}

Position *isCastling(moveNode move) {
    Position *res = (Position *) malloc(sizeof(Position) * 4);

    int myRow = INVALID_ROW;
    char myKing = INVALID_COL;
    char myRook = INVALID_COL;

    if (move.srcSoldier == KING_WHITE || move.srcSoldier == KING_BLACK) {
        myRow = move.srcSoldier == KING_WHITE ? WHITE_INITIAL_ROW : BLACK_INITIAL_ROW;
        myKing = (char) (move.srcSoldier == KING_WHITE ? KING_WHITE : KING_BLACK);
        myRook = (char) (move.srcSoldier == KING_WHITE ? ROOK_WHITE : ROOK_BLACK);
    }

    if (move.destSoldier == KING_WHITE || move.destSoldier == KING_BLACK) {
        myRow = move.destSoldier == KING_WHITE ? WHITE_INITIAL_ROW : BLACK_INITIAL_ROW;
        myKing = (char) (move.destSoldier == KING_WHITE ? KING_WHITE : KING_BLACK);
        myRook = (char) (move.destSoldier == KING_WHITE ? ROOK_WHITE : ROOK_BLACK);
    }


    res[0].row = INVALID_ROW;
    res[0].column = INVALID_COL;
    res[1].row = INVALID_ROW;
    res[1].column = INVALID_COL;
    res[2].row = INVALID_ROW;
    res[2].column = INVALID_COL;
    res[3].row = INVALID_ROW;
    res[3].column = INVALID_COL;

    if (move.srcSoldier == myKing && move.destSoldier == myRook) {
        res[0].row = myRow;
        res[1].row = myRow;
        res[2].row = myRow;
        res[3].row = myRow;
        if (move.destination.column == 'A') {
            res[0].column = 'D';
            res[1].column = 'A';
            res[2].column = 'C';
            res[3].column = KING_INITIAL_COL_CHAR;
        } else if (move.destination.column == 'H') {
            res[0].column = 'F';
            res[1].column = 'H';
            res[2].column = 'G';
            res[3].column = KING_INITIAL_COL_CHAR;
        }

    } else if (move.srcSoldier == myRook && move.destSoldier == myKing) {
        res[0].row = myRow;
        res[1].row = myRow;
        res[2].row = myRow;
        res[3].row = myRow;
        if (move.source.column == 'A') {
            res[0].column = 'D';
            res[1].column = 'A';
            res[2].column = 'C';
            res[3].column = KING_INITIAL_COL_CHAR;
        } else if (move.source.column == 'H') {
            res[0].column = 'F';
            res[1].column = 'H';
            res[2].column = 'G';
            res[3].column = KING_INITIAL_COL_CHAR;
        }

    }

    return res;

}

int isCastleSoldiers(moveNode *lastMove) {
    if (lastMove->srcSoldier == ROOK_WHITE && lastMove->destSoldier == KING_WHITE)
        return 1;
    if (lastMove->srcSoldier == KING_WHITE && lastMove->destSoldier == ROOK_WHITE)
        return 1;
    if (lastMove->srcSoldier == ROOK_BLACK && lastMove->destSoldier == KING_BLACK)
        return 2;
    if (lastMove->srcSoldier == KING_BLACK && lastMove->destSoldier == ROOK_BLACK)
        return 2;
    return 0;
}

void updateCastleForUndo(ChessGame *game, moveNode *lastMove) {
    if (lastMove->turnedOffWhiteRightCastle == 1 &&
        lastMove->turnedOffWhiteLeftCastle == 1) { // king movement. not castle
        game->whiteCastle = 1;
    } else if (lastMove->turnedOffWhiteRightCastle == 1 &&
               lastMove->turnedOffWhiteLeftCastle == 0) {
        game->rightWhiteRookMoved = 0;
        if (isCastleSoldiers(lastMove) == 1) {
            game->whiteCastle = 1;
        }
    } else if (lastMove->turnedOffWhiteRightCastle == 0 &&
               lastMove->turnedOffWhiteLeftCastle == 1) {
        game->leftWhiteRookMoved = 0;
        if (isCastleSoldiers(lastMove) == 1) {
            game->whiteCastle = 1;
        }
    } else if (lastMove->turnedOffBlackRightCastle == 1 &&
               lastMove->turnedOffBlackLeftCastle == 1) { // king movement. not castle
        game->blackCastle = 1;
    } else if (lastMove->turnedOffBlackRightCastle == 1 &&
               lastMove->turnedOffBlackLeftCastle == 0) {
        game->rightBlackRookMoved = 0;
        if (isCastleSoldiers(lastMove) == 2) {
            game->blackCastle = 1;
        }
    } else if (lastMove->turnedOffBlackRightCastle == 0 &&
               lastMove->turnedOffBlackLeftCastle == 1) {
        game->leftBlackRookMoved = 0;
        if (isCastleSoldiers(lastMove) == 2) {
            game->blackCastle = 1;
        }
    }

}


CHESS_MESSAGE undoMove(ChessGame *game) {
    if (game == NULL)
        return INVALID_ARGUMENT;
    if (isHistoryEmpty(game->history))
        return NO_HISTORY;
    moveNode *lastMove = removeRecentMove(game->history);
    Position *castlingPositions = isCastling(*lastMove);
    if (castlingPositions[0].row != INVALID_ROW) {  // for castling move

        movePiece(game, castlingPositions[0], castlingPositions[1]);
        movePiece(game, castlingPositions[2], castlingPositions[3]);

    } else {
        movePiece(game, lastMove->destination, lastMove->source);
        game->gameBoard[GET_ROW(lastMove->destination)][GET_COLUMN(lastMove->destination)] = lastMove->destSoldier;
        if (lastMove->destSoldier != EMPTY_ENTRY) {
            char soldier = (char) (isupper(lastMove->destSoldier) == 0 ? toupper(lastMove->destSoldier) : tolower(
                    lastMove->destSoldier));
            updateScore(soldier, game);
        }
    }

    updateCastleForUndo(game, lastMove);


    free(castlingPositions);
    return SUCCESS;
}

char *getSoldierName(char soldier) {
    switch (soldier) {
        case PAWN_BLACK :
        case PAWN_WHITE :
            return "pawn";
        case ROOK_BLACK :
        case ROOK_WHITE :
            return "rook";
        case KNIGHT_BLACK :
        case KNIGHT_WHITE :
            return "knight";
        case BISHOP_BLACK :
        case BISHOP_WHITE :
            return "bishop";

        case QUEEN_BLACK :
        case QUEEN_WHITE :
            return "queen";
        case KING_BLACK :
        case KING_WHITE :
            return "king";
        default :
            return "";
    }


}

Position getKingPos(ChessGame *game, bool isWhiteKing) {
    Position kingPos;

    kingPos.row = 100;
    kingPos.column = 'Z';

    char myKing = (char) (isWhiteKing ? KING_WHITE : KING_BLACK);
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            if (game->gameBoard[i][j] == myKing) {
                kingPos.row = i + 1;
                kingPos.column = j + 'A';
                return kingPos;
            }
        }
    }
    return kingPos;
}

int getScore(ChessGame *game) {
    int score = 0;
    char current;
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            current = game->gameBoard[i][j];
            if (current == PAWN_WHITE)
                score++;
            else if (current == PAWN_BLACK)
                score--;
            else if (current == ROOK_WHITE)
                score += 5;
            else if (current == ROOK_BLACK)
                score -= 5;
            else if (current == KNIGHT_WHITE)
                score += 3;
            else if (current == KNIGHT_BLACK)
                score -= 3;
            else if (current == BISHOP_WHITE)
                score += 3;
            else if (current == BISHOP_BLACK)
                score -= 3;
            else if (current == QUEEN_WHITE)
                score += 9;
            else if (current == QUEEN_BLACK)
                score -= 9;
            else if (current == KING_WHITE)
                score += 100;
            else if (current == KING_BLACK)
                score -= 100;

        }
    }
    return score;
}

bool checkCastleRules(ChessGame *game, Position src, int castleFlag, int myRow, int plusOrMinus) {
    Position firstStep;
    firstStep.row = myRow + 1;
    firstStep.column = (char) (KING_INITIAL_COL_CHAR + plusOrMinus);

    if (GET_COLUMN(src) != KING_INITIAL_COL_NUM)
        return false;

    if (myPositionUnderThreat(game, src))
        return false;

    if (castleFlag)
        return false;

    if (game->gameBoard[GET_ROW(firstStep)][GET_COLUMN(firstStep)] != EMPTY_ENTRY)
        return false;

    ChessGame *copy = gameCopy(game);
    movePiece(copy, src, firstStep);
    src.column += plusOrMinus;
    firstStep.column += plusOrMinus;

    if (game->gameBoard[GET_ROW(firstStep)][GET_COLUMN(firstStep)] != EMPTY_ENTRY) {
        gameDestroy(&copy);
        return false;
    }
    if (myPositionUnderThreat(copy, src)) {
        gameDestroy(&copy);
        return false;
    }

    movePiece(copy, src, firstStep);
    src.column += plusOrMinus;
    firstStep.column += plusOrMinus;
    if (myPositionUnderThreat(copy, src)) {
        gameDestroy(&copy);
        return false;
    }

    if (plusOrMinus == -1) { // left castle
        if (game->gameBoard[GET_ROW(firstStep)][GET_COLUMN(firstStep)] != EMPTY_ENTRY) {
            gameDestroy(&copy);
            return false;
        }
    }

    gameDestroy(&copy);
    return true;
}


bool isCastleMove(ChessGame *game, Position src, Position dest) {
    int myRow = game->currentPlayer == WHITE_PLAYER ? WHITE_INITIAL_ROW - 1 : BLACK_INITIAL_ROW - 1;
    char myKing = (char) (game->currentPlayer == WHITE_PLAYER ? KING_WHITE : KING_BLACK);
    char myRook = (char) (game->currentPlayer == WHITE_PLAYER ? ROOK_WHITE : ROOK_BLACK);
    char srcSoldier = game->gameBoard[GET_ROW(src)][GET_COLUMN(src)];
    char destSoldier = game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)];

    int myCastle = game->currentPlayer == WHITE_PLAYER ? game->whiteCastle : game->blackCastle;
    int cantDoLeftCastle = game->currentPlayer == WHITE_PLAYER ? game->leftWhiteRookMoved : game->leftBlackRookMoved;
    int cantDoRightCastle = game->currentPlayer == WHITE_PLAYER ? game->rightWhiteRookMoved : game->rightBlackRookMoved;
    if (!myCastle)
        return false;

    if (GET_ROW(src) != myRow || GET_ROW(dest) != myRow)
        return false;


    if (srcSoldier == myKing && destSoldier == myRook) {
        if (dest.column == 'A')
            return checkCastleRules(game, src, cantDoLeftCastle, myRow, -1);
        else if (dest.column == 'H')
            return checkCastleRules(game, src, cantDoRightCastle, myRow, 1);
    } else if (srcSoldier == myRook && destSoldier == myKing) {
        if (src.column == 'A')
            return checkCastleRules(game, dest, cantDoLeftCastle, myRow, -1);
        else if (src.column == 'H')
            return checkCastleRules(game, dest, cantDoRightCastle, myRow, 1);
    }

    return false;


}

