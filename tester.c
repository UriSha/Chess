
#include "tester.h"

int testGame() {
    ChessGame *game = gameCreate(3);
    Position src;
    Position dest;

    src.row = 2;
    src.column = 'A';
    dest.row = 4;
    dest.column = 'A';

    printBoard(game);
    setMove(game,src, dest);
    printBoard(game);

}

int scholarsMate(){
    Position src;
    Position dest;

    ChessGame *game = gameCreate(3);
    printBoard(game);

    src.row = 2;
    src.column = 'E';
    dest.row = 4;
    dest.column = 'E';

    src.row = 7;
    src.column = 'E';
    dest.row = 5;
    dest.column = 'E';
}