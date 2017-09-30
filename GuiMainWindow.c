
#include "GuiMainWindow.h"

int isClickOnNew(int x, int y) {
    if ((x >= WINDOW_WIDTH / 2 - 80 && x <= WINDOW_WIDTH / 2 + 82) && (y >= 100 && y <= 150)) {
        return 1;
    }
    return 0;
}

int isClickOnLoad(int x, int y) {
    if ((x >= WINDOW_WIDTH / 2 - 80 && x <= WINDOW_WIDTH / 2 + 82) && (y >= 170 && y <= 220)) {
        return 1;
    }
    return 0;
}

int isClickOnQuit(int x, int y) {
    if ((x >= WINDOW_WIDTH / 2 - 46 && x <= WINDOW_WIDTH / 2 + 46) && (y >= 240 && y <= 290)) {
        return 1;
    }
    return 0;
}

bool loadImageMainWindow(char *path, mainWin *src, SDL_Texture **texture) {
    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        mainWindowDestroy(src);
        printf("couldn't create surface\n");
        return false;
    }
    (*texture) = SDL_CreateTextureFromSurface(src->mainRenderer, loadingSurface);
    if ((*texture) == NULL) {
        SDL_FreeSurface(loadingSurface);
        mainWindowDestroy(src);
        printf("couldn't create texture\n");
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}

mainWin *mainWindowCreate() {
    mainWin *res = NULL;
    res = (mainWin *) malloc(sizeof(mainWin));
    if (res == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }

    // Create an application window with the following settings:
    res->window = SDL_CreateWindow("Chess", // window title
                                   SDL_WINDOWPOS_CENTERED,           // initial x position
                                   SDL_WINDOWPOS_CENTERED,           // initial y position
                                   WINDOW_HEIGHT,                               //
                                   WINDOW_WIDTH,                               //
                                   SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->window == NULL) {
        mainWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    res->mainRenderer = SDL_CreateRenderer(res->window, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->mainRenderer == NULL) {
        // In the case that the window could not be made...
        mainWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    if (!loadImageMainWindow("images/new.bmp", res, &(res->newTexture)))
        return NULL;
    if (!loadImageMainWindow("images/load.bmp", res, &(res->loadTexture)))
        return NULL;
    if (!loadImageMainWindow("images/quit.bmp", res, &(res->quitTexture)))
        return NULL;
    return res;
}

void mainWindowDestroy(mainWin *src) {
    if (!src) {
        return;
    }
    if (src->newTexture != NULL) {
        SDL_DestroyTexture(src->newTexture);
    }
    if (src->loadTexture != NULL) {
        SDL_DestroyTexture(src->loadTexture);
    }
    if (src->quitTexture != NULL) {
        SDL_DestroyTexture(src->quitTexture);
    }
    if (src->mainRenderer != NULL) {
        SDL_DestroyRenderer(src->mainRenderer);
    }
    if (src->window != NULL) {
        SDL_DestroyWindow(src->window);
    }
    free(src);
}

void mainWindowDraw(mainWin *src) {
    if (src == NULL) {
        return;
    }
    SDL_Rect newR = {.x = WINDOW_WIDTH / 2 - 80, .y = 100, .h = 50, .w = 159};
    SDL_Rect loadR = {.x = WINDOW_WIDTH / 2 - 80, .y = 170, .h = 50, .w = 162};
    SDL_Rect quitR = {.x = WINDOW_WIDTH / 2 - 46, .y = 240, .h = 50, .w = 93};
    SDL_SetRenderDrawColor(src->mainRenderer, 0, 0, 0, 0);
    SDL_RenderClear(src->mainRenderer);
    SDL_RenderCopy(src->mainRenderer, src->newTexture, NULL, &newR);
    SDL_RenderCopy(src->mainRenderer, src->loadTexture, NULL, &loadR);
    SDL_RenderCopy(src->mainRenderer, src->quitTexture, NULL, &quitR);
    SDL_RenderPresent(src->mainRenderer);
}

MAIN_EVENT mainWindowHandleEvent(SDL_Event *event) {
    if (!event) {
        return MAIN_INVALID_GUI_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnNew(event->button.x, event->button.y)) {
                return MAIN_NEW_GAME;
            } else if (isClickOnLoad(event->button.x, event->button.y)) {
                return MAIN_LOAD_GAME;
            } else if (isClickOnQuit(event->button.x, event->button.y)) {
                return MAIN_QUIT;
            }
            break;
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return MAIN_QUIT;
            }
            break;
        default:
            return MAIN_NONE;
    }
    return MAIN_NONE;
}
