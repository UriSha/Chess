

#include "GuiLoadWindow.h"


bool loadImageLoadWindow(char *path, loadGameWin *src, SDL_Texture **texture) {
    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        loadGameWindowDestroy(src);
        printf("Couldn't create surface\n");
        return false;
    }
    (*texture) = SDL_CreateTextureFromSurface(src->loadRenderer, loadingSurface);
    if ((*texture) == NULL) {
        SDL_FreeSurface(loadingSurface);
        loadGameWindowDestroy(src);
        printf("Couldn't create texture\n");
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}

int isClickOnBackloadWin(int x, int y) {
    if ((x >= 0 && x <= 108) && (y >= (GAME_HEIGHT - 48) && y <= GAME_HEIGHT)) {
        return 1;
    }
    return 0;

}

int isSlot1Clicked(int x, int y, int availableSlots) {
    if (availableSlots >= 1) {
        if ((x >= GAME_WIDTH / 2 - 54 && x <= GAME_WIDTH / 2 + 54) && (y >= 195 && y <= 248)) {
            return 1;
        }
    }
    return 0;
}

int isSlot2Clicked(int x, int y, int availableSlots) {
    if (availableSlots >= 2) {
        if ((x >= GAME_WIDTH / 2 - 54 && x <= GAME_WIDTH / 2 + 54) && (y >= 270 && y <= 323)) {
            return 1;
        }
    }
    return 0;
}

int isSlot3Clicked(int x, int y, int availableSlots) {
    if (availableSlots >= 3) {
        if ((x >= GAME_WIDTH / 2 - 54 && x <= GAME_WIDTH / 2 + 54) && (y >= 345 && y <= 398)) {
            return 1;
        }
    }
    return 0;
}

int isSlot4Clicked(int x, int y, int availableSlots) {
    if (availableSlots >= 4) {
        if ((x >= GAME_WIDTH / 2 - 54 && x <= GAME_WIDTH / 2 + 54) && (y >= 420 && y <= 473)) {
            return 1;
        }
    }
    return 0;
}

int isSlot5Clicked(int x, int y, int availableSlots) {
    if (availableSlots >= 5) {
        if ((x >= GAME_WIDTH / 2 - 54 && x <= GAME_WIDTH / 2 + 54) && (y >= 495 && y <= 548)) {
            return 1;
        }
    }
    return 0;
}

int getNumOfSlots() {
    FILE *numOfSlotsFile = NULL;
    numOfSlotsFile = fopen("numOfSlots.xml", "r+");
    if (numOfSlotsFile == NULL) {
        printf("Error: File doesn’t exist or cannot be opened\n");
        return false;
    }
    char *token = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    int result;

    fgets(token, MAX_LINE_LENGTH, numOfSlotsFile);
    fgets(token, MAX_LINE_LENGTH, numOfSlotsFile);
    sscanf(token, "<validSlots>%d</validSlots>", &(result));
    fclose(numOfSlotsFile);
    return result;
}

int isClickOnLoadGame(int x, int y, int chosenSlot) {
    if (chosenSlot != 0) {
        if (x >= GAME_WIDTH - 119 && x <= GAME_WIDTH && (y >= GAME_HEIGHT - 48 && y <= GAME_HEIGHT)) {
            return 1;
        }
    }
    return 0;
}

loadGameWin *loadGameWindowCreate() {
    loadGameWin *res = NULL;
    res = (loadGameWin *) malloc(sizeof(loadGameWin));
    if (res == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }

    // Create an application window with the following settings:
    res->window = SDL_CreateWindow("Load game", // window title
                                   SDL_WINDOWPOS_CENTERED,           // initial x position
                                   SDL_WINDOWPOS_CENTERED,           // initial y position
                                   GAME_WIDTH,                               //
                                   GAME_HEIGHT,                               //
                                   SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->window == NULL) {
        loadGameWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    res->loadRenderer = SDL_CreateRenderer(res->window, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->loadRenderer == NULL) {
        // In the case that the window could not be made...
        loadGameWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    res->chosenSlot = 0;
    res->availableSlots = getNumOfSlots();
    res->isCurrentGameSaved = 0;
    if (!loadImageLoadWindow("images/back.bmp", res, &(res->backTexture)))
        return NULL;
    if (!loadImageLoadWindow("images/gameLoadWindow.bmp", res, &(res->startTexture)))
        return NULL;
    if (!loadImageLoadWindow("images/init.bmp", res, &(res->logoTexture)))
        return NULL;
    if (!loadImageLoadWindow("images/loadGame.bmp", res, &(res->headerTexture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot1.bmp", res, &(res->load1Texture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot1Fade.bmp", res, &(res->load1FadeTexture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot2.bmp", res, &(res->load2Texture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot2Fade.bmp", res, &(res->load2FadeTexture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot3.bmp", res, &(res->load3Texture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot3Fade.bmp", res, &(res->load3FadeTexture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot4.bmp", res, &(res->load4Texture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot4Fade.bmp", res, &(res->load4FadeTexture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot5.bmp", res, &(res->load5Texture)))
        return NULL;
    if (!loadImageLoadWindow("images/slot5Fade.bmp", res, &(res->load5FadeTexture)))
        return NULL;
    return res;
}


void loadGameWindowDestroy(loadGameWin *src) {
    if (!src) {
        return;
    }
    if (src->headerTexture != NULL) {
        SDL_DestroyTexture(src->headerTexture);
    }
    if (src->logoTexture != NULL) {
        SDL_DestroyTexture(src->logoTexture);
    }
    if (src->load1Texture != NULL) {
        SDL_DestroyTexture(src->load1Texture);
    }
    if (src->load1FadeTexture != NULL) {
        SDL_DestroyTexture(src->load1Texture);
    }
    if (src->load2Texture != NULL) {
        SDL_DestroyTexture(src->load2Texture);
    }
    if (src->load2FadeTexture != NULL) {
        SDL_DestroyTexture(src->load2Texture);
    }
    if (src->load3Texture != NULL) {
        SDL_DestroyTexture(src->load3Texture);
    }
    if (src->load3FadeTexture != NULL) {
        SDL_DestroyTexture(src->load3Texture);
    }
    if (src->load4Texture != NULL) {
        SDL_DestroyTexture(src->load4Texture);
    }
    if (src->load4FadeTexture != NULL) {
        SDL_DestroyTexture(src->load4Texture);
    }
    if (src->load5Texture != NULL) {
        SDL_DestroyTexture(src->load5Texture);
    }
    if (src->load5FadeTexture != NULL) {
        SDL_DestroyTexture(src->load5Texture);
    }
    if (src->startTexture != NULL) {
        SDL_DestroyTexture(src->startTexture);
    }
    if (src->backTexture != NULL) {
        SDL_DestroyTexture(src->backTexture);
    }
    if (src->loadRenderer != NULL) {
        SDL_DestroyRenderer(src->loadRenderer);
    }
    if (src->window != NULL) {
        SDL_DestroyWindow(src->window);
    }
    free(src);
}


void loadGameWindowDraw(loadGameWin *src) {
    if (src == NULL) {
        return;
    }
    SDL_Rect logoR = {.x = GAME_WIDTH / 2 - 100, .y =0, .h = 112, .w =200};
    SDL_Rect headerR = {.x = GAME_WIDTH / 2 - 98, .y =120, .h = 56, .w =196};
    SDL_Rect slot1R = {.x = GAME_WIDTH / 2 - 54, .y =195, .h = 53, .w =108};
    SDL_Rect slot2R = {.x = GAME_WIDTH / 2 - 54, .y =270, .h = 53, .w =108};
    SDL_Rect slot3R = {.x = GAME_WIDTH / 2 - 54, .y =345, .h = 53, .w =108};
    SDL_Rect slot4R = {.x = GAME_WIDTH / 2 - 54, .y =420, .h = 53, .w =108};
    SDL_Rect slot5R = {.x = GAME_WIDTH / 2 - 54, .y =495, .h = 53, .w =108};
    SDL_Rect backR = {.x = 0, .y = (GAME_HEIGHT - 48), .h = 48, .w =108};
    SDL_Rect startR = {.x = GAME_WIDTH - 119, .y = (GAME_HEIGHT - 48), .h = 48, .w =119};
    SDL_SetRenderDrawColor(src->loadRenderer, 0, 0, 0, 0);
    SDL_RenderClear(src->loadRenderer);
    SDL_RenderCopy(src->loadRenderer, src->logoTexture, NULL, &logoR);
    SDL_RenderCopy(src->loadRenderer, src->headerTexture, NULL, &headerR);


    if (src->availableSlots >= 1) {
        if (src->chosenSlot == 1)
            SDL_RenderCopy(src->loadRenderer, src->load1Texture, NULL, &slot1R);
        else
            SDL_RenderCopy(src->loadRenderer, src->load1FadeTexture, NULL, &slot1R);
        if (src->availableSlots >= 2) {
            if (src->chosenSlot == 2)
                SDL_RenderCopy(src->loadRenderer, src->load2Texture, NULL, &slot2R);
            else
                SDL_RenderCopy(src->loadRenderer, src->load2FadeTexture, NULL, &slot2R);
            if (src->availableSlots >= 3) {
                if (src->chosenSlot == 3)
                    SDL_RenderCopy(src->loadRenderer, src->load3Texture, NULL, &slot3R);
                else
                    SDL_RenderCopy(src->loadRenderer, src->load3FadeTexture, NULL, &slot3R);
                if (src->availableSlots >= 4) {
                    if (src->chosenSlot == 4)
                        SDL_RenderCopy(src->loadRenderer, src->load4Texture, NULL, &slot4R);
                    else
                        SDL_RenderCopy(src->loadRenderer, src->load4FadeTexture, NULL, &slot4R);
                    if (src->availableSlots >= 5) {
                        if (src->chosenSlot == 5)
                            SDL_RenderCopy(src->loadRenderer, src->load5Texture, NULL, &slot5R);
                        else
                            SDL_RenderCopy(src->loadRenderer, src->load5FadeTexture, NULL, &slot5R);
                    }
                }
            }
        }

    }

    SDL_RenderCopy(src->loadRenderer, src->backTexture, NULL, &backR);
    SDL_RenderCopy(src->loadRenderer, src->startTexture, NULL, &startR);
    SDL_RenderPresent(src->loadRenderer);
}

LOAD_EVENT loadGameWindowHandleEvent(loadGameWin *src, SDL_Event *event) {
    if (!event) {
        return LOAD_INVALID_GUI_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnBackloadWin(event->button.x, event->button.y))
                return LOAD_BACK;
            if (isClickOnLoadGame(event->button.x, event->button.y, src->chosenSlot))
                return LOAD_START;
            if (isSlot1Clicked(event->button.x, event->button.y, src->availableSlots))
                return LOAD_1SLOT;
            if (isSlot2Clicked(event->button.x, event->button.y, src->availableSlots))
                return LOAD_2SLOT;
            if (isSlot3Clicked(event->button.x, event->button.y, src->availableSlots))
                return LOAD_3SLOT;
            if (isSlot4Clicked(event->button.x, event->button.y, src->availableSlots))
                return LOAD_4SLOT;
            if (isSlot5Clicked(event->button.x, event->button.y, src->availableSlots))
                return LOAD_5SLOT;

        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return LOAD_QUIT;
            }
            break;
        default:
            return LOAD_NONE;
    }
    return LOAD_NONE;
}
