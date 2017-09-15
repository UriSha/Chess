#include <stdio.h>
//#include <ctype.h>
#include "ChessParser.h"
//#include "ChessHistory.h"
//#include "ChessGame.h"
#include "tester.h"
#include "MainAux.h"



int main() {
    GameSession* gameSession=(GameSession*)malloc(sizeof(GameSession));
    int gameStatus=-1;
    CHESS_MESSAGE msg;
    while(gameStatus!=0) {
        gameStatus = settingState(gameSession);
        if (gameStatus == 0)
            continue;
        msg=gameState(gameSession);
        if(msg==TIE || msg ==MATE || msg==EXIT_GAME)
            gameStatus=0;
    }
    gameDestroy(&(gameSession->game));
    free(gameSession);
    return 0;
}
