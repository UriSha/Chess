#ifndef CHESS_GUIMAINWINDOW_H
#define CHESS_GUIMAINWINDOW_H


#include "GuiDefinitions.h"


typedef struct {
    SDL_Window *window;
    SDL_Renderer *mainRenderer;
    SDL_Texture *newTexture;
    SDL_Texture *loadTexture;
    SDL_Texture *quitTexture;
} mainWin;

typedef enum {
    MAIN_QUIT,
    MAIN_NEW_GAME,
    MAIN_LOAD_GAME,
    MAIN_INVALID_GUI_ARGUMENT,
    MAIN_NONE,
} MAIN_EVENT;

//Main Window
bool loadImageMainWindow(char *path, mainWin *src, SDL_Texture **texture);

mainWin *mainWindowCreate();

void mainWindowDraw(mainWin *src);

void mainWindowDestroy(mainWin *src);

//void windowHide(SDL_Window *srcWindow);
//
//void windowShow(SDL_Window *srcWindow);

MAIN_EVENT mainWindowHandleEvent(mainWin *src, SDL_Event *event);

#endif //CHESS_GUIMAINWINDOW_H
