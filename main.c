#include <stdio.h>
#include "ChessParser.h"
#include "ChessHistory.h"
#include "ChessGame.h"

int main() {
    ChessGame* game = gameCreate(3);
    printBoard(game);

}