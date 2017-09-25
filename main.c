#include <stdio.h>
//#include <ctype.h>
#include "ChessParser.h"
//#include "ChessHistory.h"
//#include "ChessGame.h"
#include "tester.h"
#include "GuiWindows.h"
#include "GuiManager.h"


void consoleMode(){

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
        if(msg==RESET_GAME){
            gameDestroy(&(gameSession->game));
        }
    }
    gameDestroy(&(gameSession->game));
    free(gameSession);
}
void guiMode(){
    GameSession* gameSession=(GameSession*)malloc(sizeof(GameSession));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
        printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
        return ;
    }
    GuiManager* manager = ManagerCreate();
    if (manager == NULL ) {
        SDL_Quit();
        return;
    }
    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if (ManagerHandleEvent(gameSession,manager, &event) == MANAGER_QUTT) {
            break;
        }

        ManagerDraw(manager);
    }
    ManagerDestroy(manager);
    SDL_Quit();
}
int main(int argc, char** argv) {
    guiMode();
//    consoleMode();
    return 0;
}
