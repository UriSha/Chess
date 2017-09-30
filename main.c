#include "GuiManager.h"


void consoleMode() {

    GameSession *gameSession = (GameSession *) malloc(sizeof(GameSession));
    int gameStatus = -1;
    CHESS_MESSAGE msg;
    while (gameStatus != 0) {
        gameStatus = settingState(gameSession);
        if (gameStatus == 0)
            continue;
        msg = gameState(gameSession);
        if (msg == TIE || msg == MATE || msg == EXIT_GAME)
            gameStatus = 0;
        if (msg == RESET_GAME) {
            gameDestroy(&(gameSession->game));
        }
    }
    gameDestroy(&(gameSession->game));
    free(gameSession);
}

void guiMode() {
    GameSession *gameSession = (GameSession *) malloc(sizeof(GameSession));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { //SDL2 INIT
        printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
        free(gameSession);
        return;
    }
    GuiManager *manager = ManagerCreate();
    if (manager == NULL) {
        SDL_Quit();
        return;
    }
    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if (ManagerHandleEvent(gameSession, manager, &event) == MANAGER_QUIT) {
            break;
        }

        ManagerDraw(manager, gameSession);
    }
    ManagerDestroy(manager);
    free(gameSession);
    SDL_Quit();
}

int main(int argc, char **argv) {
    if (argc > 2) {
        printf("too many argument where given. 1 expected\n");
        return 0;
    }
    else if (argc == 1)
        guiMode();
    else if (argc == 2){
        if (strcmp(argv[1], "-c") == 0)
            consoleMode();
        else if (strcmp(argv[1], "-g") == 0)
            guiMode();
        else
            printf("expected argument: '-c' or '-g'\n");

    }

    return 0;
}
