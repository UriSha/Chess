#include <stdio.h>
#include "ChessParser.h"
#include "ChessHistory.h"

int main() {
    ChessHistory* history=createChessHistory(3);
    HistoryNode move;
    char col='A';
    int row=2;

    Position pos;
    pos.row=row;
    pos.column=col;
    move.source=pos;
    col='B';
    row=3;
    Position pos2;
    pos2.column=col;
    pos2.row=row;
    move.destination=pos2;
    addMovetoHistory(history,move);
    char *pawn;

   printf("Moved %c%d to %c%d and We ate a %s",move.destination.column,move.destination.row,move.source.column
   ,move.source.row,pawn);

}