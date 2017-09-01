#include <stdio.h>
#include <ctype.h>
#include "ChessParser.h"
#include "ChessHistory.h"
#include "ChessGame.h"



int main() {
    ChessGame* game = gameCreate(3);
    printBoard(game);
    printf("%d\n", isupper('g'));
    Position pos;
    pos.column = 'D';
    pos.row = 8;
    printf("%d", GET_COLUMN(pos));
    printf("%d", GET_ROW(pos));
}