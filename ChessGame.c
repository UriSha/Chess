#include "ChessGame.h"


#define KING_INITIAL_COL_CHAR 'E'
#define KING_INITIAL_COL_NUM 4
#define WHITE_INITIAL_ROW 1
#define BLACK_INITIAL_ROW 8

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
    game->whiteLeftCastle = game->whiteRightCastle = 1;
    game->blackLeftCastle = game->blackRightCastle = 1;

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
    copy->whiteLeftCastle = src->whiteLeftCastle;
    copy->whiteRightCastle = src->whiteRightCastle;
    copy->blackLeftCastle = src->blackLeftCastle;
    copy->blackRightCastle = src->blackRightCastle;

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
        if (GET_COLUMN(game->whiteKingPos) + 2 == GET_COLUMN(dest)) { // right castling white player
            game->gameBoard[WHITE_INITIAL_ROW-1][KING_INITIAL_COL_NUM + 1] = ROOK_WHITE;
            game->gameBoard[WHITE_INITIAL_ROW-1][KING_INITIAL_COL_NUM + 3] = EMPTY_ENTRY;
        } else if (GET_COLUMN(game->whiteKingPos) - 3 == GET_COLUMN(dest)) {// left castling white player
            game->gameBoard[WHITE_INITIAL_ROW-1][KING_INITIAL_COL_NUM - 1] = ROOK_WHITE;
            game->gameBoard[WHITE_INITIAL_ROW-1][KING_INITIAL_COL_NUM - 4] = EMPTY_ENTRY;
        }
        game->whiteKingPos.row = dest.row;
        game->whiteKingPos.column = dest.column;
        game->whiteLeftCastle = game->whiteRightCastle = 0;

    } else if (srcSoldier == KING_BLACK) {
        if (GET_COLUMN(game->blackKingPos) + 2 == GET_COLUMN(dest)) { // right castling black player
            game->gameBoard[BLACK_INITIAL_ROW-1][KING_INITIAL_COL_NUM + 1] = ROOK_BLACK;
            game->gameBoard[BLACK_INITIAL_ROW-1][KING_INITIAL_COL_NUM + 3] = EMPTY_ENTRY;
        } else if (GET_COLUMN(game->blackKingPos) - 3 == GET_COLUMN(dest)) {// left castling black player
            game->gameBoard[BLACK_INITIAL_ROW-1][KING_INITIAL_COL_NUM - 1] = ROOK_BLACK;
            game->gameBoard[BLACK_INITIAL_ROW-1][KING_INITIAL_COL_NUM - 4] = EMPTY_ENTRY;
        }
        game->blackKingPos.row = dest.row;
        game->blackKingPos.column = dest.column;
        game->blackLeftCastle = game->blackRightCastle = 0;
    }
    if (srcSoldier == ROOK_WHITE) {
        if (src.column == 'H' && src.row == WHITE_INITIAL_ROW)//Right Rook White moved
            game->whiteRightCastle = 0;
        else if (src.column == 'A' && src.row == WHITE_INITIAL_ROW)//Left Rook White moved
            game->whiteLeftCastle = 0;
    } else if (srcSoldier == ROOK_BLACK) {
        if (src.column == 'H' && src.row == BLACK_INITIAL_ROW)//Right Rook Black moved
            game->blackRightCastle = 0;
        else if (src.column == 'A' && src.row == BLACK_INITIAL_ROW)//Left Rook Black moved
            game->blackLeftCastle = 0;
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

bool
diagonalOrHorizontalThreat(ChessGame *game, int rowPlusMinus, int colPlusMinus, int curRow, int curCol) {
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
    if (game->gameBoard[row + plusMinus][col + plusMinus] == getOtherPawn(game->currentPlayer) ||
        game->gameBoard[row + plusMinus][col - plusMinus] == getOtherPawn(game->currentPlayer))
        return true;
    return (knightThreatsPosition(game, row, col) || QBRThreatsPosition(game, row, col) ||
            QBRThreatsPosition(game, row, col) || kingThreatsPosition(game, row, col));
}

bool legalCastling(ChessGame *game, Position src, Position dest, bool isRightCastling) {
    if (game == NULL)
        return false;
    int kingRow = game->currentPlayer == WHITE_PLAYER ? WHITE_INITIAL_ROW : BLACK_INITIAL_ROW;
    char rook = (char) (game->currentPlayer == WHITE_PLAYER ? ROOK_WHITE : ROOK_BLACK);
    Position firstStep;
    firstStep.row = kingRow;
    Position kingPos = game->currentPlayer == WHITE_PLAYER ?
                       game->whiteKingPos : game->blackKingPos;
    if (isRightCastling) {
        firstStep.column = KING_INITIAL_COL_CHAR + 1;
        if ((game->gameBoard[kingRow-1][GET_COLUMN(firstStep)] != EMPTY_ENTRY) ||
            (game->gameBoard[kingRow-1][GET_COLUMN(dest)] != EMPTY_ENTRY) ||
            game->gameBoard[kingRow-1][GAME_SIZE - 1] != rook)
            return false;
        if (myPositionUnderThreat(game, kingPos))
            return false;
        ChessGame *copy = gameCopy(game);
        movePiece(copy, src, firstStep);
        kingPos.column++;
        if (myPositionUnderThreat(copy, kingPos)) {
            gameDestroy(&copy);
            return false;
        }
        movePiece(copy, firstStep, dest);
        kingPos.column++;
        if (myPositionUnderThreat(copy, kingPos)) {
            gameDestroy(&copy);
            return false;
        }
        gameDestroy(&copy);
    } else {//leftCastling
        firstStep.column = KING_INITIAL_COL_CHAR - 1;
        Position secondStep;
        secondStep.row = firstStep.row;
        secondStep.column = KING_INITIAL_COL_CHAR - 2;
        if ((game->gameBoard[kingRow-1][GET_COLUMN(firstStep)] != EMPTY_ENTRY) ||
            (game->gameBoard[kingRow-1][GET_COLUMN(secondStep)] != EMPTY_ENTRY) ||
            (game->gameBoard[kingRow-1][GET_COLUMN(dest)] != EMPTY_ENTRY) ||
            (game->gameBoard[kingRow-1][0] != rook))
            return false;
        if (myPositionUnderThreat(game, kingPos))
            return false;
        ChessGame *copy = gameCopy(game);
        movePiece(copy, src, firstStep);
        kingPos.column--;
        if (myPositionUnderThreat(copy, kingPos)) {
            gameDestroy(&copy);
            return false;
        }
        movePiece(copy, firstStep, secondStep);
        kingPos.column--;
        if (myPositionUnderThreat(copy, kingPos)) {
            gameDestroy(&copy);
            return false;
        }
        movePiece(copy, secondStep, dest);
        kingPos.column--;
        if (myPositionUnderThreat(copy, kingPos)) {
            gameDestroy(&copy);
            return false;
        }
        gameDestroy(&copy);
    }
    return true;
}

bool isValidMove_King(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return false;
    if (dest.row == src.row) {//possible Castling
        bool rightCastle = game->currentPlayer == WHITE_PLAYER ? game->whiteRightCastle : game->blackRightCastle;
        bool leftCastle = game->currentPlayer == WHITE_PLAYER ? game->whiteLeftCastle : game->blackLeftCastle;
        if (rightCastle && GET_COLUMN(dest) == KING_INITIAL_COL_NUM + 2)
            return legalCastling(game, src, dest, 1);
        if (leftCastle && GET_COLUMN(dest) == KING_INITIAL_COL_NUM - 3)
            return legalCastling(game, src, dest, 0);
    }
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
            Position kingPos = copy->currentPlayer == WHITE_PLAYER ?
                               copy->whiteKingPos : copy->blackKingPos;
            if (myPositionUnderThreat(copy, kingPos))
                result = false;
        }
        gameDestroy(&copy);
    }
    return result;
}

void pawnPromotion(ChessGame *game, Position posOfPawn) {//TODO computer pawn promotion
    char userInput[MAX_LINE_LENGTH];
    char chosenSolider = '\0';
    do {
        printf("Pawn promotion- please replace the pawn by queen, rook, knight, bishop or pawn:\n");
        scanf("%s", userInput);
        if (strcmp(userInput, "queen") == 0)
            chosenSolider = (char) (game->currentPlayer == WHITE_PLAYER ? QUEEN_WHITE : QUEEN_BLACK);
        else if (strcmp(userInput, "bishop") == 0)
            chosenSolider = (char) (game->currentPlayer == WHITE_PLAYER ? BISHOP_WHITE : BISHOP_BLACK);
        else if (strcmp(userInput, "rook") == 0)
            chosenSolider = (char) (game->currentPlayer == WHITE_PLAYER ? ROOK_WHITE : ROOK_BLACK);
        else if (strcmp(userInput, "knight") == 0)
            chosenSolider = (char) (game->currentPlayer == WHITE_PLAYER ? KNIGHT_WHITE : KNIGHT_BLACK);
        else if (strcmp(userInput, "pawn") == 0)
            chosenSolider = (char) (game->currentPlayer == WHITE_PLAYER ? PAWN_WHITE : PAWN_BLACK);
        else {
            printf("Invalid Type\n");
        }
    } while (chosenSolider == '\0');

    game->gameBoard[GET_ROW(posOfPawn)][GET_COLUMN(posOfPawn)] = chosenSolider;

}
void updateScore(char soldierDied,ChessGame* game){
    int isBlackDied= isupper(soldierDied)==0 ? -1 : 1 ;

    switch(soldierDied)
    {
        case PAWN_BLACK :
        case PAWN_WHITE :
            game->score+=(1*isBlackDied);
            break;
        case ROOK_BLACK :
        case ROOK_WHITE :
            game->score+=(5*isBlackDied);
            break;
        case KNIGHT_BLACK :
        case KNIGHT_WHITE :
            game->score+=(3*isBlackDied);
            break;
        case BISHOP_BLACK :
        case BISHOP_WHITE :
            game->score+=(3*isBlackDied);
            break;
        case QUEEN_BLACK :
        case QUEEN_WHITE :
            game->score+=(9*isBlackDied);
            break;
        case KING_BLACK :
        case KING_WHITE :
            game->score+=(100*isBlackDied);
            break;
        default :
            return;
    }


}

CHESS_MESSAGE setMove(ChessGame *game, Position src, Position dest) {
    if (game == NULL)
        return INVALID_ARGUMENT;

    if (!isValidMove(game, src, dest))
        return ILLEGAL_MOVE;


    char soldierDied = game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)];
    if(soldierDied!=EMPTY_ENTRY)
        updateScore(soldierDied ,game);
    HistoryNode move;
    move.source = src;
    move.destination = dest;
    move.soldierDied = soldierDied;

    addMovetoHistory(game->history, move);

    movePiece(game, src, dest);

    if (game->gameBoard[WHITE_INITIAL_ROW-1][0] != ROOK_WHITE)
        game->whiteLeftCastle = 0;
    if (game->gameBoard[WHITE_INITIAL_ROW-1][GAME_SIZE - 1] != ROOK_WHITE)
        game->whiteRightCastle = 0;
    if (game->gameBoard[BLACK_INITIAL_ROW-1][0] != ROOK_BLACK)
        game->blackLeftCastle = 0;
    if (game->gameBoard[BLACK_INITIAL_ROW-1][GAME_SIZE - 1] != ROOK_BLACK)
        game->blackRightCastle = 0;

    int lastRow = game->currentPlayer == WHITE_PLAYER ? BLACK_INITIAL_ROW-1 : WHITE_INITIAL_ROW-1;
    char srcSolider = (char) (game->currentPlayer == WHITE_PLAYER ? PAWN_WHITE : PAWN_BLACK);
    if (game->gameBoard[GET_ROW(dest)][GET_COLUMN(dest)] == srcSolider && GET_ROW(dest) == lastRow)
        pawnPromotion(game, dest);

    return SUCCESS;

}
void changePlayer(ChessGame* game)
{
    game->currentPlayer = 1 - game->currentPlayer;
}
int getSoldierColor(char soldier) {
    if (soldier == EMPTY_ENTRY)
        return -1;
    return isupper(soldier) == 0 ? WHITE_PLAYER : BLACK_PLAYER;
}

bool areThereAnyMoves(ChessGame *game) {

    Position src, dest;
    for (int i = 1; i <= GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            src.row = i;
            src.column = 'A' + j;
            if (getSoldierColor(game->gameBoard[i-1][j]) != game->currentPlayer)
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
            if (isValidMove(game, pos, dest))
                result[movesCounter++] = dest;
        }
    }
    return movesCounter;
}


void printMoves(ChessGame *game, Position pos) {
    if (game == NULL)
        return;
//    char *playerColor;
//    playerColor = game->currentPlayer == WHITE_PLAYER ? "white" : "black";
//    if (getSoldierColor(game->gameBoard[GET_ROW(pos)][GET_COLUMN(pos)])
//        != game->currentPlayer)
//        printf("The specified position does not contain %s player piece\n", playerColor);
//    if (pos.row > 8 || pos.row < 1 || pos.column > 'H' || pos.column < 'A')
//        printf("Invalid position on the board\n");
    Position *result = (Position *) malloc(28 * sizeof(Position));//28 is approximately the maximum number of moves
    int positionCounter = getMoves(game, result, pos);
    result = (Position *) realloc(result, positionCounter * sizeof(Position));
    char **movesArray = (char **) malloc(sizeof(char) * positionCounter);
    for (int i = 0; i < positionCounter; i++)
        movesArray[i] = (char *) malloc(sizeof(char) * 15);//15 is maximun length of a row

    for (int i = 0; i < positionCounter; i++) {
        movesArray[i] = getStringFromPosition(result[i]);
        char myKing=(char)(game->currentPlayer==WHITE_PLAYER ? KING_WHITE : KING_BLACK);
        int myKingInitRow=game->currentPlayer==WHITE_PLAYER ? WHITE_INITIAL_ROW-1 : BLACK_INITIAL_ROW-1;

        bool castleRight =game->currentPlayer==WHITE_PLAYER ? game->whiteRightCastle : game->blackRightCastle;
        bool castleLeft =game->currentPlayer==WHITE_PLAYER ? game->whiteLeftCastle : game->blackLeftCastle;

        if (game->gameBoard[GET_ROW(pos)][GET_COLUMN(pos)] == myKing) {
            if(pos.column==KING_INITIAL_COL_CHAR&& GET_ROW(pos)==myKingInitRow)
            {
                if(GET_ROW(result[i])==myKingInitRow){
                    if(castleRight &&GET_COLUMN(result[i])==KING_INITIAL_COL_NUM+2){
                        sprintf(movesArray[i], "castle <%d,%c>", result[i].row, result[i].column);
                        continue;
                    }
                    if (castleLeft && GET_COLUMN(result[i])==KING_INITIAL_COL_NUM-3){
                        sprintf(movesArray[i], "castle <%d,%c>", result[i].row, result[i].column);
                        continue;
                    }
                }
            }
        }
        bool someoneDied = game->gameBoard[GET_ROW(result[i])][GET_COLUMN(result[i])] != EMPTY_ENTRY ?
                           true : false;
        ChessGame *copy = gameCopy(game);
        movePiece(copy, pos, result[i]);
        if (myPositionUnderThreat(copy, result[i])) {
            movesArray[i][5] = '*';
            if (someoneDied) {
                movesArray[i][6] = '^';
                movesArray[i][7] = '\0';

            } else
                movesArray[i][6] = '\0';
        } else if (someoneDied) {
            movesArray[i][5] = '^';
            movesArray[i][6] = '\0';
        }
        gameDestroy(&copy);
    }
    for (int i = 0; i < positionCounter; i++)
        printf("%s\n", movesArray[i]);
    for (int i = 0; i < positionCounter; i++)
        free(movesArray[i]);
    free(movesArray);
}
CHESS_MESSAGE undoMove(ChessGame* game){
    if (game==NULL)
        return INVALID_ARGUMENT;
    if(isHistoryEmpty(game->history))
        return NO_HISTORY;
    HistoryNode* lastMove = removeRecentMove(game->history);
    movePiece(game,lastMove->destination,lastMove->source);
    game->gameBoard[GET_ROW(lastMove->destination)][GET_COLUMN(lastMove->destination)]=lastMove->soldierDied;
    return SUCCESS;
}