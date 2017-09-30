#include "GuiSettingsWindow.h"


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
    if (!loadImageSettingsWindow("images/back.bmp", res, &(res->backTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/start.bmp", res, &(res->startTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/gameModeBig.bmp", res, &(res->gameModeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/difficultyBig.bmp", res, &(res->difficultyTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/userColorBig.bmp", res, &(res->userColorTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/white.bmp", res, &(res->whiteTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/whiteFade.bmp", res, &(res->whiteFadeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/black.bmp", res, &(res->blackTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/blackFade.bmp", res, &(res->blackFadeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/player1.bmp", res, &(res->player1Texture)))
        return NULL;
    if (!loadImageSettingsWindow("images/player2.bmp", res, &(res->player2Texture)))
        return NULL;
    if (!loadImageSettingsWindow("images/player1Fade.bmp", res, &(res->player1FadeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/player2Fade.bmp", res, &(res->player2FadeTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/init.bmp", res, &(res->logoTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/moderateFade.bmp", res, &(res->difficulty3FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/moderate.bmp", res, &(res->difficulty3Texture)))
        return NULL;
    if (!loadImageSettingsWindow("images/noobFade.bmp", res, &(res->difficulty1FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/noob.bmp", res, &(res->difficulty1Texture)))
        return NULL;
    if (!loadImageSettingsWindow("images/easyFade.bmp", res, &(res->difficulty2FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/easy.bmp", res, &(res->difficulty2Texture)))
        return NULL;
    if (!loadImageSettingsWindow("images/hardFade.bmp", res, &(res->difficulty4FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/hard.bmp", res, &(res->difficulty4Texture)))
        return NULL;
    if (!loadImageSettingsWindow("images/expertFade.bmp", res, &(res->difficulty5FTexture)))
        return NULL;
    if (!loadImageSettingsWindow("images/expert.bmp", res, &(res->difficulty5Texture)))
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

SETTINGS_EVENT settingsWindowHandleEvent(settingsWin *src, SDL_Event *event) {
    if (!event) {
        return SETTINGS_INVALID_GUI_ARGUMENT;
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
                return SETTINGS_QUIT;
            }
            break;
        default:
            return SETTINGS_NONE;
    }
    return SETTINGS_NONE;
}
