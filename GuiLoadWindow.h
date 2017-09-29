#ifndef CHESS_GUILOADWINDOW_H
#define CHESS_GUILOADWINDOW_H

#include "GuiDefinitions.h"
#define MAX_NUM_OF_SLOTS 5

typedef struct {
    SDL_Window *window;
    SDL_Renderer *loadRenderer;
    SDL_Texture *logoTexture;
    SDL_Texture *headerTexture;
    SDL_Texture *load1Texture;
    SDL_Texture *load1FadeTexture;
    SDL_Texture *load2Texture;
    SDL_Texture *load2FadeTexture;
    SDL_Texture *load3Texture;
    SDL_Texture *load3FadeTexture;
    SDL_Texture *load4Texture;
    SDL_Texture *load4FadeTexture;
    SDL_Texture *load5Texture;
    SDL_Texture *load5FadeTexture;
    SDL_Texture *startTexture;
    SDL_Texture *backTexture;
    int chosenSlot;
    int availableSlots;
    int fromMainMenu;
} loadGameWin;

typedef enum {
    LOAD_1SLOT,
    LOAD_2SLOT,
    LOAD_3SLOT,
    LOAD_4SLOT,
    LOAD_5SLOT,
    LOAD_BACK,
    LOAD_START,
    LOAD_QUIT,
    LOAD_INVALID_GUI_ARGUMENT,
    LOAD_NONE,
} LOAD_EVENT;

bool loadImageLoadWindow(char *path, loadGameWin *src, SDL_Texture **texture);

loadGameWin *loadGameWindowCreate();

void loadGameWindowDraw(loadGameWin *src);

void loadGameWindowDestroy(loadGameWin *src);

LOAD_EVENT loadGameWindowHandleEvent(loadGameWin *src, SDL_Event *event);


#endif //CHESS_GUILOADWINDOW_H
