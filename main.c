#include <stdio.h>
#include <ctype.h>
#include "ChessParser.h"
//#include "ChessHistory.h"
//#include "ChessGame.h"
#include "tester.h"
#include "MainAux.h"



int main() {
ChessGame* game=gameCreate(6);
    saveGame("../SavedGames/test.xml",game,1,4,0);
    int x=6;
    printf("%.8s","abcdefghhhh");
}
