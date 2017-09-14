#include <stdio.h>
#include <ctype.h>
#include "ChessParser.h"
//#include "ChessHistory.h"
//#include "ChessGame.h"
#include "tester.h"



int main() {
ChessGame* game=gameCreate(6);
    MiniMaxNode *node=createNode(1,1,0,game);
    Position src,dest;
    src.row=2;
    src.column='B';
    dest.row=4;
    dest.column='B';
    setMove(game,src,dest);
    nodeDestroy(node);
    int x=6;
}
