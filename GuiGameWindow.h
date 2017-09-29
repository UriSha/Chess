#ifndef CHESS_GUIGAMEWINDOW_H
#define CHESS_GUIGAMEWINDOW_H


#include "GuiDefinitions.h"


typedef enum{
    GAME_QUIT_SAVED,
    GAME_QUIT_UNSAVED,
    GAME_UNDO,
    GAME_RESTART,
    GAME_MAINMENU_SAVED,
    GAME_MAINMENU_UNSAVED,
    GAME_SAVE,
    GAME_LOAD,
    GAME_MOVE,
    GAME_NONE,
    GAME_INVALID
}GAME_EVENT;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *gameRenderer;
    SDL_Texture *gameBoardTexture;
    SDL_Texture *restartTexture;
    SDL_Texture *saveTexture;
    SDL_Texture *saveFadeTexture;
    SDL_Texture *loadTexture;
    SDL_Texture *undoFadeTexture;
    SDL_Texture *undoTexture;
    SDL_Texture *mainMenuTexture;
    SDL_Texture *quitTexture;
    SDL_Texture *pawnWhiteTexture;
    SDL_Texture *pawnBlackTexture;
    SDL_Texture *knightWhiteTexture;
    SDL_Texture *knightBlackTexture;
    SDL_Texture *bishopWhiteTexture;
    SDL_Texture *bishopBlackTexture;
    SDL_Texture *rookWhiteTexture;
    SDL_Texture *rookBlackTexture;
    SDL_Texture *queenWhiteTexture;
    SDL_Texture *queenBlackTexture;
    SDL_Texture *kingWhiteTexture;
    SDL_Texture *kingBlackTexture;
    SDL_Rect movingRect;
    Position moveSrc;
    Position moveDest;
    int currentlyDragged;
    int isSaved;
    int getMovesShowing;
    SDL_Texture** movesGrid;
    SDL_Texture* yellow;
    SDL_Texture* red;
    SDL_Texture* green;
    SDL_Texture* purple;
} gameWin;



bool loadImageGameWindow(char *path, gameWin *src, SDL_Texture **texture);

gameWin *gameWindowCreate(GameSession *session);

SDL_Texture *getTexture(gameWin *gameWin, char soldier);

void gameWindowDraw(gameWin *src, GameSession *session);

void gameWindowDestroy(gameWin *src);

GAME_EVENT gameWindowHandleEvent(GameSession* session, gameWin *src, SDL_Event *event);

#endif //CHESS_GUIGAMEWINDOW_H
