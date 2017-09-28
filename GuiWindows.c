
#include "GuiWindows.h"


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
    if (!loadImageMainWindow("../images/new.bmp", res, &(res->newTexture)))
        return NULL;
    if (!loadImageMainWindow("../images/load.bmp", res, &(res->loadTexture)))
        return NULL;
    if (!loadImageMainWindow("../images/quit.bmp", res, &(res->quitTexture)))
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
    src = NULL;
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

EVENT mainWindowHandleEvent(mainWin *src, SDL_Event *event) {
    if (!event) {
        return GUI_INVALID_ARGUMENT;
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
            return NONE;
    }
    return NONE;
}

void windowHide(SDL_Window *srcWindow) {
    SDL_HideWindow(srcWindow);
}

void windowShow(SDL_Window *srcWindow) {
    SDL_ShowWindow(srcWindow);
}

bool loadImageSettingsWindow(char *path, settingsWin *src, SDL_Texture **texture) {
    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        settingsWindowDestroy(src);
        printf("Couldn't create surface\n");
        return false;
    }
    (*texture) = SDL_CreateTextureFromSurface(src->settingsRenderer, loadingSurface);
    if ((*texture) == NULL) {
        SDL_FreeSurface(loadingSurface);
        settingsWindowDestroy(src);
        printf("Couldn't create texture\n");
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}

int isClickOnBack(int x, int y) {
    if ((x >= 0 && x <= 108) && (y >= (GAME_HEIGHT - 48) && y <= GAME_HEIGHT)) {
        return 1;
    }
    return 0;

}

int isClickOnStart(int x, int y) {
    if ((x >= GAME_WIDTH - 110 && x <= GAME_WIDTH) && (y >= (GAME_HEIGHT - 48) && y <= GAME_HEIGHT)) {
        return 1;
    }
    return 0;

}

int isClickOnPlayer1(int x, int y) {
    if ((x >= 295 && x <= 422) && (y >= 130 && y <= 184)) {
        return 1;
    }
    return 0;
}

int isClickOnPlayer2(int x, int y) {
    if ((x >= 490 && x <= 627) && (y >= 130 && y <= 184)) {
        return 1;
    }
    return 0;
}

int isNoobClicked(int x, int y, bool is1Player) {
    if (is1Player) {
        if ((x >= 215 && x <= 310) && (y >= 245 && y <= 299)) {
            return 1;
        }
    }
    return 0;

}

int isEasyClicked(int x, int y, bool is1Player) {
    if (is1Player) {
        if ((x >= 410 && x <= 498) && (y >= 245 && y <= 299)) {
            return 1;
        }
    }
    return 0;
}

int isModerateClicked(int x, int y, bool is1Player) {
    if (is1Player) {
        if ((x >= 595 && x <= 733) && (y >= 245 && y <= 299)) {
            return 1;
        }
    }
    return 0;
}

int isHardClicked(int x, int y, bool is1Player) {
    if (is1Player) {
        if ((x >= 300 && x <= 391) && (y >= 325 && y <= 379)) {
            return 1;
        }
    }
    return 0;
}

int isExpertClicked(int x, int y, bool is1Player) {
    if (is1Player) {
        if ((x >= 500 && x <= 608) && (y >= 325 && y <= 379)) {
            return 1;
        }
    }
    return 0;
}

int isBlackClicked(int x, int y, bool is1Player) {
    if (is1Player) {
        if ((x >= 505 && x <= 601) && (y >= 460 && y <= 514)) {
            return 1;
        }
    }
    return 0;

}

int isWhiteClicked(int x, int y, bool is1Player) {
    if (is1Player) {
        if ((x >= 295 && x <= 397) && (y >= 460 && y <= 514)) {
            return 1;
        }
    }
    return 0;
}

settingsWin *settingsWindowCreate() {
    settingsWin *res = NULL;
    res = (settingsWin *) malloc(sizeof(settingsWin));
    if (res == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }

    // Create an application window with the following settings:
    res->window = SDL_CreateWindow("Settings", // window title
                                   SDL_WINDOWPOS_CENTERED,           // initial x position
                                   SDL_WINDOWPOS_CENTERED,           // initial y position
                                   GAME_WIDTH,                               //
                                   GAME_HEIGHT,                               //
                                   SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->window == NULL) {
        settingsWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    res->settingsRenderer = SDL_CreateRenderer(res->window, -1,
                                               SDL_RENDERER_ACCELERATED);
    if (res->settingsRenderer == NULL) {
        // In the case that the window could not be made...
        settingsWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    res->is1player = true;
    res->diff = 2;
    res->user_color = 1;
    if (!loadImageSettingsWindow("../images/back.bmp", res, &(res->backTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/start.bmp", res, &(res->startTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/gameModeBig.bmp", res, &(res->gameModeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/difficultyBig.bmp", res, &(res->difficultyTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/userColorBig.bmp", res, &(res->userColorTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/white.bmp", res, &(res->whiteTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/whiteFade.bmp", res, &(res->whiteFadeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/black.bmp", res, &(res->blackTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/blackFade.bmp", res, &(res->blackFadeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/player1.bmp", res, &(res->player1Texture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/player2.bmp", res, &(res->player2Texture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/player1Fade.bmp", res, &(res->player1FadeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/player2Fade.bmp", res, &(res->player2FadeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/init.bmp", res, &(res->logoTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/moderateFade.bmp", res, &(res->difficulty3FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/moderate.bmp", res, &(res->difficulty3Texture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/noobFade.bmp", res, &(res->difficulty1FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/noob.bmp", res, &(res->difficulty1Texture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/easyFade.bmp", res, &(res->difficulty2FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/easy.bmp", res, &(res->difficulty2Texture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/hardFade.bmp", res, &(res->difficulty4FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/hard.bmp", res, &(res->difficulty4Texture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/expertFade.bmp", res, &(res->difficulty5FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("../images/expert.bmp", res, &(res->difficulty5Texture)))
        return NULL;
    return res;
}

void settingsWindowDestroy(settingsWin *src) {
    if (!src) {
        return;
    }
    if (src->gameModeTexture != NULL) {
        SDL_DestroyTexture(src->gameModeTexture);
    }
    if (src->difficultyTexture != NULL) {
        SDL_DestroyTexture(src->difficultyTexture);
    }
    if (src->userColorTexture != NULL) {
        SDL_DestroyTexture(src->userColorTexture);
    }
    if (src->logoTexture != NULL) {
        SDL_DestroyTexture(src->logoTexture);
    }
    if (src->player1Texture != NULL) {
        SDL_DestroyTexture(src->player1Texture);
    }
    if (src->player2Texture != NULL) {
        SDL_DestroyTexture(src->player2Texture);
    }
    if (src->player2FadeTexture != NULL) {
        SDL_DestroyTexture(src->player2FadeTexture);
    }
    if (src->player1FadeTexture != NULL) {
        SDL_DestroyTexture(src->player1FadeTexture);
    }
    if (src->difficulty1Texture != NULL) {
        SDL_DestroyTexture(src->difficulty1Texture);
    }
    if (src->difficulty2Texture != NULL) {
        SDL_DestroyTexture(src->difficulty2Texture);
    }
    if (src->difficulty3Texture != NULL) {
        SDL_DestroyTexture(src->difficulty3Texture);
    }
    if (src->difficulty4Texture != NULL) {
        SDL_DestroyTexture(src->difficulty4Texture);
    }
    if (src->difficulty5Texture != NULL) {
        SDL_DestroyTexture(src->difficulty5Texture);
    }
    if (src->difficulty1FTexture != NULL) {
        SDL_DestroyTexture(src->difficulty1FTexture);
    }
    if (src->difficulty2FTexture != NULL) {
        SDL_DestroyTexture(src->difficulty2FTexture);
    }
    if (src->difficulty3FTexture != NULL) {
        SDL_DestroyTexture(src->difficulty3FTexture);
    }
    if (src->difficulty4FTexture != NULL) {
        SDL_DestroyTexture(src->difficulty4FTexture);
    }
    if (src->difficulty5FTexture != NULL) {
        SDL_DestroyTexture(src->difficulty5FTexture);
    }
    if (src->whiteTexture != NULL) {
        SDL_DestroyTexture(src->whiteTexture);
    }
    if (src->whiteFadeTexture != NULL) {
        SDL_DestroyTexture(src->whiteFadeTexture);
    }
    if (src->blackTexture != NULL) {
        SDL_DestroyTexture(src->blackTexture);
    }
    if (src->blackFadeTexture != NULL) {
        SDL_DestroyTexture(src->blackFadeTexture);
    }
    if (src->startTexture != NULL) {
        SDL_DestroyTexture(src->startTexture);
    }
    if (src->backTexture != NULL) {
        SDL_DestroyTexture(src->backTexture);
    }
    if (src->settingsRenderer != NULL) {
        SDL_DestroyRenderer(src->settingsRenderer);
    }
    if (src->window != NULL) {
        SDL_DestroyWindow(src->window);
    }
    free(src);
    src = NULL;
}

void settingsWindowDraw(settingsWin *src) {
    if (src == NULL) {
        return;
    }
    SDL_Rect logoR = {.x = GAME_WIDTH / 2 - 100, .y =0, .h = 112, .w =200};
    SDL_Rect playerHeader = {.x = 10, .y =125, .h = 56, .w =216};
    SDL_Rect player1R = {.x = 295, .y =130, .h = 54, .w =127};
    SDL_Rect player2R = {.x = 490, .y =130, .h = 54, .w =137};
    SDL_Rect diffHeader = {.x = 10, .y =285, .h = 56, .w =178};
    SDL_Rect diff1R = {.x = 215, .y = 245, .h = 54, .w =95};
    SDL_Rect diff2R = {.x = 410, .y =245, .h = 54, .w =88};
    SDL_Rect diff3R = {.x = 585, .y =245, .h = 54, .w =138};
    SDL_Rect diff4R = {.x = 310, .y =325, .h = 54, .w =91};
    SDL_Rect diff5R = {.x = 500, .y = 325, .h = 54, .w =108};
    SDL_Rect colorHeader = {.x = 10, .y =455, .h = 56, .w =200};
    SDL_Rect color1R = {.x = 295, .y =460, .h = 54, .w =102};
    SDL_Rect color0R = {.x = 505, .y =460, .h = 54, .w =96};
    SDL_Rect backR = {.x = 0, .y = (GAME_HEIGHT - 48), .h = 48, .w =108};
    SDL_Rect startR = {.x = GAME_WIDTH - 110, .y = (GAME_HEIGHT - 48), .h = 48, .w =110};
    SDL_SetRenderDrawColor(src->settingsRenderer, 0, 0, 0, 0);
    SDL_RenderClear(src->settingsRenderer);
    SDL_RenderCopy(src->settingsRenderer, src->logoTexture, NULL, &logoR);
    SDL_RenderCopy(src->settingsRenderer, src->gameModeTexture, NULL, &playerHeader);
    if (src->is1player) {
        SDL_RenderCopy(src->settingsRenderer, src->player1Texture, NULL, &player1R);
        SDL_RenderCopy(src->settingsRenderer, src->player2FadeTexture, NULL, &player2R);
    } else {
        SDL_RenderCopy(src->settingsRenderer, src->player1FadeTexture, NULL, &player1R);
        SDL_RenderCopy(src->settingsRenderer, src->player2Texture, NULL, &player2R);
    }
    SDL_RenderCopy(src->settingsRenderer, src->difficultyTexture, NULL, &diffHeader);
    if (src->is1player && src->diff == 1)
        SDL_RenderCopy(src->settingsRenderer, src->difficulty1Texture, NULL, &diff1R);
    else
        SDL_RenderCopy(src->settingsRenderer, src->difficulty1FTexture, NULL, &diff1R);
    if (src->is1player && src->diff == 2)
        SDL_RenderCopy(src->settingsRenderer, src->difficulty2Texture, NULL, &diff2R);
    else
        SDL_RenderCopy(src->settingsRenderer, src->difficulty2FTexture, NULL, &diff2R);
    if (src->is1player && src->diff == 3)
        SDL_RenderCopy(src->settingsRenderer, src->difficulty3Texture, NULL, &diff3R);
    else
        SDL_RenderCopy(src->settingsRenderer, src->difficulty3FTexture, NULL, &diff3R);
    if (src->is1player && src->diff == 4)
        SDL_RenderCopy(src->settingsRenderer, src->difficulty4Texture, NULL, &diff4R);
    else
        SDL_RenderCopy(src->settingsRenderer, src->difficulty4FTexture, NULL, &diff4R);
    if (src->is1player && src->diff == 5)
        SDL_RenderCopy(src->settingsRenderer, src->difficulty5Texture, NULL, &diff5R);
    else
        SDL_RenderCopy(src->settingsRenderer, src->difficulty5FTexture, NULL, &diff5R);

    SDL_RenderCopy(src->settingsRenderer, src->userColorTexture, NULL, &colorHeader);
    if (src->is1player && src->user_color == 1)
        SDL_RenderCopy(src->settingsRenderer, src->whiteTexture, NULL, &color1R);
    else
        SDL_RenderCopy(src->settingsRenderer, src->whiteFadeTexture, NULL, &color1R);
    if (src->is1player && src->user_color == 0)
        SDL_RenderCopy(src->settingsRenderer, src->blackTexture, NULL, &color0R);
    else
        SDL_RenderCopy(src->settingsRenderer, src->blackFadeTexture, NULL, &color0R);
    SDL_RenderCopy(src->settingsRenderer, src->backTexture, NULL, &backR);
    SDL_RenderCopy(src->settingsRenderer, src->startTexture, NULL, &startR);
    SDL_RenderPresent(src->settingsRenderer);
}

EVENT settingsWindowHandleEvent(settingsWin *src, SDL_Event *event) {
    if (!event) {
        return GUI_INVALID_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnBack(event->button.x, event->button.y))
                return SETTINGS_BACK;
            if (isClickOnStart(event->button.x, event->button.y))
                return SETTINGS_START;
            if (isClickOnPlayer1(event->button.x, event->button.y))
                return SETTINGS_1PLAYER;
            if (isClickOnPlayer2(event->button.x, event->button.y))
                return SETTINGS_2PLAYER;
            if (isNoobClicked(event->button.x, event->button.y, src->is1player))
                return SETTINGS_1DIFF;
            if (isEasyClicked(event->button.x, event->button.y, src->is1player))
                return SETTINGS_2DIFF;
            if (isModerateClicked(event->button.x, event->button.y, src->is1player))
                return SETTINGS_3DIFF;
            if (isHardClicked(event->button.x, event->button.y, src->is1player))
                return SETTINGS_4DIFF;
            if (isExpertClicked(event->button.x, event->button.y, src->is1player))
                return SETTINGS_5DIFF;
            if (isBlackClicked(event->button.x, event->button.y, src->is1player))
                return SETTINGS_USERCOLOR_0;
            if (isWhiteClicked(event->button.x, event->button.y, src->is1player))
                return SETTINGS_USERCOLOR_1;

        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return MAIN_QUIT;
            }
            break;
        default:
            return NONE;
    }
    return NONE;
}

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
    if (!loadImageLoadWindow("../images/back.bmp", res, &(res->backTexture)))
        return NULL;
    if (!loadImageLoadWindow("../images/gameLoadWindow.bmp", res, &(res->startTexture)))
        return NULL;
    if (!loadImageLoadWindow("../images/init.bmp", res, &(res->logoTexture)))
        return NULL;
    if (!loadImageLoadWindow("../images/loadGame.bmp", res, &(res->headerTexture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot1.bmp", res, &(res->load1Texture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot1Fade.bmp", res, &(res->load1FadeTexture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot2.bmp", res, &(res->load2Texture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot2Fade.bmp", res, &(res->load2FadeTexture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot3.bmp", res, &(res->load3Texture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot3Fade.bmp", res, &(res->load3FadeTexture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot4.bmp", res, &(res->load4Texture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot4Fade.bmp", res, &(res->load4FadeTexture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot5.bmp", res, &(res->load5Texture)))
        return NULL;
    if (!loadImageLoadWindow("../images/slot5Fade.bmp", res, &(res->load5FadeTexture)))
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
    src = NULL;
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


//    SDL_RenderCopy(src->loadRenderer, src->load1Texture, NULL, &slot1R);
//    SDL_RenderCopy(src->loadRenderer, src->load2Texture, NULL, &slot2R);
//    SDL_RenderCopy(src->loadRenderer, src->load3Texture, NULL, &slot3R);
//    SDL_RenderCopy(src->loadRenderer, src->load4Texture, NULL, &slot4R);
//    SDL_RenderCopy(src->loadRenderer, src->load5Texture, NULL, &slot5R);

    SDL_RenderCopy(src->loadRenderer, src->backTexture, NULL, &backR);
    SDL_RenderCopy(src->loadRenderer, src->startTexture, NULL, &startR);
    SDL_RenderPresent(src->loadRenderer);
}

EVENT loadGameWindowHandleEvent(loadGameWin *src, SDL_Event *event) {
    if (!event) {
        return GUI_INVALID_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnBack(event->button.x, event->button.y))
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
                return MAIN_QUIT;
            }
            break;
        default:
            return NONE;
    }
    return NONE;
}

bool loadImageGameWindow(char *path, gameWin *src, SDL_Texture **texture) {
    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        gameWindowDestroy(src);
        printf("Couldn't create surface\n");
        return false;
    }
    (*texture) = SDL_CreateTextureFromSurface(src->gameRenderer, loadingSurface);
    if ((*texture) == NULL) {
        SDL_FreeSurface(loadingSurface);
        gameWindowDestroy(src);
        printf("Couldn't create texture\n");
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}

int isClickedOnUndo(int x, int y, GameSession *session) {
    if (session == NULL)
        return 0;
    if (session->game->history->actualSize > 0) {
        if ((x >= 500 && x <= 590) && (y >= 100 && y <= 150)) {//TODO check the pixels
            return 1;
        }
    }
    return 0;
}
int isClickedOnRestartGame(int x, int y) {
    if ((x >= 500 && x <= 590) && (y >= 100 && y <= 150)) {//TODO check the pixels
        return 1;
    }
    return 0;
}
int isClickedOnSaveGame(int x, int y) {
    if ((x >= 500 && x <= 590) && (y >= 100 && y <= 150)) {//TODO check the pixels
        return 1;
    }
    return 0;
}
int isClickedOnLoadGame(int x, int y) {
    if ((x >= 500 && x <= 590) && (y >= 100 && y <= 150)) {//TODO check the pixels
        return 1;
    }
    return 0;
}
int isClickedOnMainMenu(int x, int y) {
    if ((x >= 500 && x <= 590) && (y >= 100 && y <= 150)) {//TODO check the pixels
        return 1;
    }
    return 0;
}
int isClickedOnQuitGame(int x, int y) {
    if ((x >= 500 && x <= 590) && (y >= 100 && y <= 150)) {//TODO check the pixels
        return 1;
    }
    return 0;
}

gameWin *gameWindowCreate(GameSession *session) {
    gameWin *res = NULL;
    res = (gameWin *) malloc(sizeof(gameWin));
    if (res == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }

    // Create an application window with the following settings:
    res->window = SDL_CreateWindow("Blood and Honor", // window title
                                   SDL_WINDOWPOS_CENTERED,           // initial x position
                                   SDL_WINDOWPOS_CENTERED,           // initial y position
                                   GAME_WIDTH,                               //
                                   GAME_HEIGHT,                               //
                                   SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->window == NULL) {
        gameWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    res->gameRenderer = SDL_CreateRenderer(res->window, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->gameRenderer == NULL) {
        // In the case that the window could not be made...
        gameWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    if (!loadImageGameWindow("../images/board.bmp", res, &(res->gameBoardTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whitePawn.bmp", res, &(res->pawnWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackPawn.bmp", res, &(res->pawnBlackTexture)))//
        return NULL;
    if (!loadImageGameWindow("../images/whiteBishop.bmp", res, &(res->bishopWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackBishop.bmp", res, &(res->bishopBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whiteKnight.bmp", res, &(res->knightWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackKnight.bmp", res, &(res->knightBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whiteRook.bmp", res, &(res->rookWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackRook.bmp", res, &(res->rookBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whiteQueen.bmp", res, &(res->queenWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackQueen.bmp", res, &(res->queenBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whiteKing.bmp", res, &(res->kingWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackKing.bmp", res, &(res->kingBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/undoMove.bmp", res, &(res->undoTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/undoMoveFade.bmp", res, &(res->undoFadeTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/restartGame.bmp", res, &(res->restartTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/saveGame.bmp", res, &(res->saveTexture)))
        return NULL;

    if (!loadImageGameWindow("../images/loadGame.bmp", res, &(res->loadTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/mainMenu.bmp", res, &(res->mainMenuTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/quitGame.bmp", res, &(res->quitTexture)))
        return NULL;
    return res;
}

void gameWindowDestroy(gameWin *src) {
    if (!src) {
        return;
    }
    if (src->gameBoardTexture != NULL) {
        SDL_DestroyTexture(src->gameBoardTexture);
    }
    if (src->pawnWhiteTexture != NULL) {
        SDL_DestroyTexture(src->pawnWhiteTexture);
    }
    if (src->pawnBlackTexture != NULL) {
        SDL_DestroyTexture(src->pawnBlackTexture);
    }
    if (src->knightWhiteTexture != NULL) {
        SDL_DestroyTexture(src->knightWhiteTexture);
    }
    if (src->knightBlackTexture != NULL) {
        SDL_DestroyTexture(src->knightBlackTexture);
    }
    if (src->bishopWhiteTexture != NULL) {
        SDL_DestroyTexture(src->bishopWhiteTexture);
    }
    if (src->bishopBlackTexture != NULL) {
        SDL_DestroyTexture(src->bishopBlackTexture);
    }
    if (src->rookWhiteTexture != NULL) {
        SDL_DestroyTexture(src->rookWhiteTexture);
    }
    if (src->rookBlackTexture != NULL) {
        SDL_DestroyTexture(src->rookBlackTexture);
    }
    if (src->queenWhiteTexture != NULL) {
        SDL_DestroyTexture(src->queenWhiteTexture);
    }
    if (src->queenBlackTexture != NULL) {
        SDL_DestroyTexture(src->queenBlackTexture);
    }
    if (src->kingWhiteTexture != NULL) {
        SDL_DestroyTexture(src->kingWhiteTexture);
    }
    if (src->kingBlackTexture != NULL) {
        SDL_DestroyTexture(src->kingBlackTexture);
    }
    if (src->undoTexture != NULL) {
        SDL_DestroyTexture(src->undoTexture);
    }
    if (src->undoFadeTexture != NULL) {
        SDL_DestroyTexture(src->undoFadeTexture);
    }
    if (src->restartTexture != NULL) {
        SDL_DestroyTexture(src->restartTexture);
    }
    if (src->saveTexture != NULL) {
        SDL_DestroyTexture(src->saveTexture);
    }
    if (src->loadTexture != NULL) {
        SDL_DestroyTexture(src->loadTexture);
    }
    if (src->mainMenuTexture != NULL) {
        SDL_DestroyTexture(src->mainMenuTexture);
    }

    if (src->quitTexture != NULL) {
        SDL_DestroyTexture(src->quitTexture);
    }
    if (src->gameRenderer != NULL) {
        SDL_DestroyRenderer(src->gameRenderer);
    }
    if (src->window != NULL) {
        SDL_DestroyWindow(src->window);
    }

    free(src);
    src = NULL;
}

SDL_Texture *getTexture(gameWin *gameWin,
                        char soldier) {
    switch (soldier) {
        case KING_BLACK:
            return gameWin->kingBlackTexture;
        case KING_WHITE:
            return gameWin->kingWhiteTexture;
        case QUEEN_BLACK:
            return gameWin->queenBlackTexture;
        case QUEEN_WHITE:
            return gameWin->queenWhiteTexture;
        case ROOK_BLACK:
            return gameWin->rookBlackTexture;
        case ROOK_WHITE:
            return gameWin->rookWhiteTexture;
        case BISHOP_BLACK:
            return gameWin->bishopBlackTexture;
        case BISHOP_WHITE:
            return gameWin->bishopWhiteTexture;
        case KNIGHT_BLACK:
            return gameWin->knightBlackTexture;
        case KNIGHT_WHITE:
            return gameWin->knightWhiteTexture;
        case PAWN_BLACK:
            return gameWin->pawnBlackTexture;
        case PAWN_WHITE:
            return gameWin->pawnWhiteTexture;
        default:
            return NULL;
    }

}

void gameWindowDraw(gameWin *src, GameSession *session) {
    if (src == NULL) {
        return;
    }
    SDL_Rect boardR = {.x = GAMEBOARD_X, .y = GAMEBOARD_Y, .h = 480, .w = 480};
    SDL_Rect soldiers[8][8];
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            soldiers[i][j].x = GAMEBOARD_X + (j * 60);
            soldiers[i][j].y = GAMEBOARD_Y + (i * 60);
            soldiers[i][j].h = 60;
            soldiers[i][j].w = 60;
        }
    }
    SDL_Rect undoR = {.x =500, .y = GAMEBOARD_Y, .h = 56, .w = 196};
    SDL_Rect restartR = {.x =500, .y = GAMEBOARD_Y + 60, .h = 56, .w = 196};
    SDL_Rect saveR = {.x =500, .y = GAMEBOARD_Y + 120, .h = 56, .w = 196};
    SDL_Rect loadR = {.x =500, .y = GAMEBOARD_Y + 180, .h = 56, .w = 196};
    SDL_Rect mainMenuR = {.x =500, .y = GAMEBOARD_Y + 240, .h = 56, .w = 196};
    SDL_Rect quitR = {.x =500, .y = GAMEBOARD_Y + 300, .h = 56, .w = 196};
    SDL_SetRenderDrawColor(src->gameRenderer, 0, 0, 0, 0);
    SDL_RenderClear(src->gameRenderer);
    SDL_RenderCopy(src->gameRenderer, src->gameBoardTexture, NULL, &boardR);
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            if (session->game->gameBoard[i][j] != EMPTY_ENTRY)
                SDL_RenderCopy(src->gameRenderer, getTexture(src, session->game->gameBoard[i][j]),
                               NULL, &soldiers[7 - i][j]);
        }
    }
    if(session->mode==ONE_PLAYER){
        if(session->game->history->actualSize>0)
            SDL_RenderCopy(src->gameRenderer, src->undoTexture, NULL, &undoR);
        else
            SDL_RenderCopy(src->gameRenderer, src->undoFadeTexture, NULL, &undoR);

    }
    SDL_RenderCopy(src->gameRenderer, src->restartTexture, NULL, &restartR);
    SDL_RenderCopy(src->gameRenderer, src->saveTexture, NULL, &saveR);
    SDL_RenderCopy(src->gameRenderer, src->loadTexture, NULL, &loadR);
    SDL_RenderCopy(src->gameRenderer, src->mainMenuTexture, NULL, &mainMenuR);
    SDL_RenderCopy(src->gameRenderer, src->quitTexture, NULL, &quitR);
    SDL_RenderPresent(src->gameRenderer);
}

GAME_EVENT gameWindowHandleEvent(gameWin *src, SDL_Event *event) {
    if (!event) {
        return GAME_INVALID;
    }
    switch (event->type) {
//        case SDL_MOUSEBUTTONUP:
//            if (isClickOnBack(event->button.x, event->button.y))
//                return LOAD_BACK;
//            if (isClickOnLoadGame(event->button.x, event->button.y,src->chosenSlot))
//                return LOAD_START;
//            if (isSlot1Clicked(event->button.x, event->button.y, src->availableSlots))
//                return LOAD_1SLOT;
//            if (isSlot2Clicked(event->button.x, event->button.y, src->availableSlots))
//                return LOAD_2SLOT;
//            if (isSlot3Clicked(event->button.x, event->button.y, src->availableSlots))
//                return LOAD_3SLOT;
//            if (isSlot4Clicked(event->button.x, event->button.y, src->availableSlots))
//                return LOAD_4SLOT;
//            if (isSlot5Clicked(event->button.x, event->button.y, src->availableSlots))
//                return LOAD_5SLOT;

        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                return GAME_QUIT;
            }
            break;
        default:
            return GAME_NONE;
    }
    return GAME_NONE;
}
