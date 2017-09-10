
#include "tester.h"

int testGame() {
    ChessGame *game = gameCreate(6);
    Position src;
    Position dest;

    src.row = 2;
    src.column = 'A';
    dest.row = 4;
    dest.column = 'A';

    printBoard(game);
    setMove(game,src, dest);
    printBoard(game);
    src.row = 7;
    src.column = 'A';
    dest.row = 5;
    dest.column = 'A';
    setMove(game,src, dest);
    printBoard(game);
    src.row = 2;
    src.column = 'B';
    dest.row = 3;
    dest.column = 'B';
    setMove(game,src, dest);
    printBoard(game);
    src.row = 8;
    src.column = 'B';
    dest.row = 6;
    dest.column = 'A';
    setMove(game,src, dest);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);

}

int scholarsMate(){
    Position src;
    Position dest;

    ChessGame *game = gameCreate(6);
    printBoard(game);
    printf("\n\n");
    src.row = 2;
    src.column = 'E';
    dest.row = 4;
    dest.column = 'E';
    setMove(game,src,dest);
    printBoard(game);
    checkStatus(game);
    printf("\n\n");
    src.row = 7;
    src.column = 'E';
    dest.row = 5;
    dest.column = 'E';
    setMove(game,src,dest);
    printBoard(game);
    checkStatus(game);
    printf("\n\n");
    src.row = 1;
    src.column = 'D';
    dest.row = 5;
    dest.column = 'H';
    setMove(game,src,dest);
    printBoard(game);
    checkStatus(game);
    printf("\n\n");
    src.row = 8;
    src.column = 'B';
    dest.row = 6;
    dest.column = 'C';
    setMove(game,src,dest);
    printBoard(game);
    checkStatus(game);
    printf("\n\n");
    src.row = 1;
    src.column = 'F';
    dest.row = 4;
    dest.column = 'C';
    setMove(game,src,dest);
    printBoard(game);
    checkStatus(game);
    printf("\n\n");
    src.row = 8;
    src.column = 'G';
    dest.row = 6;
    dest.column = 'F';
    setMove(game,src,dest);
    printBoard(game);
    checkStatus(game);
    printf("\n\n");
    src.row = 5;
    src.column = 'H';
    dest.row = 7;
    dest.column = 'F';
    setMove(game,src,dest);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);
    undoMove(game);
    printBoard(game);
}

void checkPrintMoves()
{
    Position src;
    Position dest;

    ChessGame *game = gameCreate(3);
    printBoard(game);
    src.row=1;
    src.column='B';
    printMoves(game,src);
    src.row = 2;
    src.column = 'E';
    dest.row = 4;
    dest.column = 'E';
    setMove(game,src,dest);
    printBoard(game);
    src.row = 7;
    src.column = 'E';
    dest.row = 5;
    dest.column = 'E';
    setMove(game,src,dest);
    printBoard(game);
    src.row = 1;
    src.column = 'D';
    dest.row = 5;
    dest.column = 'H';
    setMove(game,src,dest);
    printBoard(game);
    src.row = 7;
    src.column = 'A';
    dest.row = 6;
    dest.column = 'A';
    setMove(game,src,dest);
    printBoard(game);
    dest.row = 5;
    dest.column = 'H';
    printMoves(game,dest);




}