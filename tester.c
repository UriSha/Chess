
#include "tester.h"

void testGame() {
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

void scholarsMate(){
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
//
//void computerMove(ChessGame *game, int maxDepth){
//    HistoryNode move = bestMove(game,maxDepth,false);
//    setMove(game,move.source,move.destination);
//    changePlayer(game);
//}

void testMinMax(){
    ChessGame *game = gameCreate(6);
    printBoard(game);

    Position myMoveSrc;
    Position myMovedest;
    myMoveSrc.row = 2;
    myMoveSrc.column = 'C';

    myMovedest.row = 4;
    myMovedest.column = 'C';
    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
    printBoard(game);
////
    myMoveSrc.row = 4;
    myMoveSrc.column = 'C';

    myMovedest.row = 5;
    myMovedest.column = 'C';
    setMove(game,myMoveSrc, myMovedest);
    printBoard(game);

    myMoveSrc.row = 5;
    myMoveSrc.column = 'C';

    myMovedest.row = 6;
    myMovedest.column = 'C';
    setMove(game,myMoveSrc, myMovedest);
    printBoard(game);


    myMoveSrc.row = 6;
    myMoveSrc.column = 'C';

    myMovedest.row = 7;
    myMovedest.column = 'D';
    setMove(game,myMoveSrc, myMovedest);
    printBoard(game);
    changePlayer(game);
    checkStatus(game);
//    computerMove(game,1);
//    printBoard(game);
//
//
//    myMoveSrc.row = 2;
//    myMoveSrc.column = 'A';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'A';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game,1);
//    printBoard(game);
//
//    myMoveSrc.row = 2;
//    myMoveSrc.column = 'C';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'C';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game,1);
//    printBoard(game);
//
//    myMoveSrc.row = 1;
//    myMoveSrc.column = 'D';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'A';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game,2);
//    printBoard(game);
//
//    myMoveSrc.row = 4;
//    myMoveSrc.column = 'A';
//
//    myMovedest.row = 7;
//    myMovedest.column = 'D';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
////    checkStatus(game);
//    computerMove(game,2);
//    printBoard(game);




}

void computerIsWhite(){

    ChessGame *game = gameCreate(6);
    printBoard(game);
//    computerMove(game,2);
    printBoard(game);

    Position myMoveSrc;
    Position myMovedest;

    myMoveSrc.row = 7;
    myMoveSrc.column = 'B';

    myMovedest.row = 5;
    myMovedest.column = 'B';
    setMove(game,myMoveSrc, myMovedest);
    changePlayer(game);
    printBoard(game);

//    computerMove(game,1);
    printBoard(game);

    myMoveSrc.row = 7;
    myMoveSrc.column = 'A';

    myMovedest.row = 6;
    myMovedest.column = 'A';
    setMove(game,myMoveSrc, myMovedest);
    changePlayer(game);
    printBoard(game);
//    computerMove(game,2);
//    printBoard(game);
}

//void bardak() {
//    ChessGame *game = gameCreate(6);
//    printBoard(game);
//
//    Position myMoveSrc;
//    Position myMovedest;
//    myMoveSrc.row = 2;
//    myMoveSrc.column = 'C';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'C';
//    setMove(game, myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game, 4);
//    printBoard(game);
//
//    myMoveSrc.row = 1;
//    myMoveSrc.column = 'D';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'A';
//    setMove(game, myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game, 3);
//    printBoard(game);
//
//    myMoveSrc.row = 4;
//    myMoveSrc.column = 'C';
//
//    myMovedest.row = 5;
//    myMovedest.column = 'B';
//    setMove(game, myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game, 4);
//    printBoard(game);
//
//    myMoveSrc.row = 2;
//    myMoveSrc.column = 'D';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'D';
//    setMove(game, myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game, 4);
//    printBoard(game);
//
//
//    myMoveSrc.row = 1;
//    myMoveSrc.column = 'G';
//
//    myMovedest.row = 3;
//    myMovedest.column = 'F';
//    setMove(game, myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game, 4);
//    printBoard(game);
//
//    myMoveSrc.row = 3;
//    myMoveSrc.column = 'F';
//
//    myMovedest.row = 5;
//    myMovedest.column = 'E';
//    setMove(game, myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game, 4);
//    printBoard(game);
//
//}
//
//void otherTest(){
//    ChessGame *game = gameCreate(6);
//    printBoard(game);
//
//    Position myMoveSrc;
//    Position myMovedest;
//    myMoveSrc.row = 2;
//    myMoveSrc.column = 'B';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'B';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
////
//    computerMove(game,1);
//    printBoard(game);
//
//
//    myMoveSrc.row = 2;
//    myMoveSrc.column = 'A';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'A';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game,1);
//    printBoard(game);
//
//    myMoveSrc.row = 2;
//    myMoveSrc.column = 'C';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'C';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game,1);
//    printBoard(game);
//
//    myMoveSrc.row = 1;
//    myMoveSrc.column = 'D';
//
//    myMovedest.row = 4;
//    myMovedest.column = 'A';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
//
//    computerMove(game,2);
//    printBoard(game);
//
//    myMoveSrc.row = 4;
//    myMoveSrc.column = 'A';
//
//    myMovedest.row = 7;
//    myMovedest.column = 'D';
//    setMove(game,myMoveSrc, myMovedest);
//    changePlayer(game);
//    printBoard(game);
////    checkStatus(game);
//    computerMove(game,2);
//    printBoard(game);
//
//
//}
void statusCheck(){
    ChessGame * game = gameCreate(6);
    printBoard(game);
    for(int i=0;i<GAME_SIZE;i++)
    {
        for(int j =0;j<GAME_SIZE;j++)
            game->gameBoard[i][j]=EMPTY_ENTRY;
    }
    printBoard(game);
    game->gameBoard[2][4]='r';
    game->gameBoard[0][2]='b';
    game->gameBoard[0][3]='k';
    game->gameBoard[0][4]='n';
    game->gameBoard[0][5]='b';
    game->gameBoard[2][2]='r';

    game->gameBoard[1][0]='m';
    game->gameBoard[2][3]='q';
    game->gameBoard[1][2]='n';
    game->gameBoard[1][5]='m';

    game->gameBoard[3][1]='m';

    game->gameBoard[3][5]='m';
    game->gameBoard[6][1]='m';
    game->gameBoard[6][2]='m';
    game->gameBoard[6][3]='m';
    game->gameBoard[6][4]='M';
    game->gameBoard[6][5]='m';
    game->gameBoard[6][6]='M';
    game->gameBoard[6][7]='M';

    game->gameBoard[7][0]='R';
    game->gameBoard[7][1]='N';
    game->gameBoard[7][2]='B';
    game->gameBoard[7][3]='Q';
    game->gameBoard[4][3]='K';
    game->gameBoard[7][5]='B';
    game->gameBoard[7][6]='N';
    game->gameBoard[7][7]='R';

    printBoard(game);
    game->whiteKingPos.row=1;
    game->whiteKingPos.column='D';
    game->blackKingPos.row=5;
    game->blackKingPos.column='D';
    changePlayer(game);
    checkStatus(game);

}

//void compVsComp(){
//    ChessGame *game = gameCreate(6);
//    printBoard(game);
//    int x = 10;
//    while (x>0) {
//        computerMove(game, 3);
//        printBoard(game);
//        x--;
//    }
//}
void getMovesCheck(){
    ChessGame *game = gameCreate(6);
    printBoard(game);

    Position src;
    Position dest;
    src.row = 1;
    src.column = 'G';
    dest.row = 3;
    dest.column = 'F';
    setMove(game,src,dest);
    printBoard(game);

    src.row = 2;
    src.column = 'G';
    dest.row = 3;
    dest.column = 'G';
    setMove(game,src,dest);
    printBoard(game);

    src.row = 1;
    src.column = 'F';
    dest.row = 3;
    dest.column = 'H';
    setMove(game,src,dest);
    printBoard(game);

    src.row = 1;
    src.column = 'E';
    dest.row = 1;
    dest.column = 'G';
    setMove(game,src,dest);
    printBoard(game);




    printMoves(game,game->whiteKingPos);
}