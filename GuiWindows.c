#include <stdbool.h>
#include "GuiWindows.h"
int isClickOnNew(int x, int y) {
    if ((x >= WINDOW_WIDTH/2-80 && x <= WINDOW_WIDTH/2+82) && (y >= 100 && y <= 150)) {
        return 1;
    }
    return 0;
}
int isClickOnLoad(int x, int y) {
    if ((x >= WINDOW_WIDTH/2-80 && x <=WINDOW_WIDTH/2+82) && (y >= 170 && y <= 220)) {
        return 1;
    }
    return 0;
}
int isClickOnQuit(int x, int y) {
    if ((x >= WINDOW_WIDTH/2-46 && x <= WINDOW_WIDTH/2+46) && (y >= 240 && y <= 290)) {
        return 1;
    }
    return 0;
}

//int is(int x, int y, bool is!player){
//    if (is1Player)
//        return
//}
bool loadImageMainWindow(char* path, mainWin* src,SDL_Texture ** texture){
    SDL_Surface* loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL ) {
        mainWindowDestroy(src);
        printf("couldn't create surface\n");
        return false;
    }
    (*texture) = SDL_CreateTextureFromSurface(src->mainRenderer, loadingSurface);
    if ((*texture) == NULL ) {
        SDL_FreeSurface(loadingSurface);
        mainWindowDestroy(src);
        printf("couldn't create texture\n");
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}
mainWin* mainWindowCreate() {
    mainWin* res = NULL;
    SDL_Surface* loadingSurface = NULL;
    res = (mainWin*) malloc(sizeof(mainWin));
    if (res == NULL ) {//TODO Malloc error
        return NULL ;
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
    if (res->window == NULL ) {
        mainWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL ;
    }
    res->mainRenderer = SDL_CreateRenderer(res->window, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->mainRenderer == NULL ) {
        // In the case that the window could not be made...
        mainWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL ;
    }
    if(!loadImageMainWindow("../images/new.bmp", res,&(res->newTexture)))
         return NULL;
    if(!loadImageMainWindow("../images/load.bmp", res,&(res->loadTexture)))
        return NULL;
    if(!loadImageMainWindow("../images/quit.bmp", res,&(res->quitTexture)))
        return NULL;
    return res;
}

void mainWindowDestroy(mainWin *src) {
    if (!src) {
        return;
    }
    if (src->newTexture != NULL ) {
        SDL_DestroyTexture(src->newTexture);
    }
    if (src->loadTexture != NULL ) {
        SDL_DestroyTexture(src->loadTexture);
    }
    if (src->quitTexture != NULL ) {
        SDL_DestroyTexture(src->quitTexture);
    }
    if (src->mainRenderer != NULL ) {
        SDL_DestroyRenderer(src->mainRenderer);
    }
    if (src->window != NULL ) {
        SDL_DestroyWindow(src->window);
    }
    free(src);
}
void mainWindowDraw(mainWin *src) {
    if(src==NULL){
        return;
    }
    SDL_Rect newR = { .x = WINDOW_WIDTH/2-80, .y = 100, .h = 50, .w = 159 };
    SDL_Rect loadR = { .x = WINDOW_WIDTH/2-80, .y = 170, .h = 50, .w = 162 };
    SDL_Rect quitR = { .x = WINDOW_WIDTH/2-46, .y = 240, .h = 50, .w = 93 };
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
            }
            else if (isClickOnQuit(event->button.x, event->button.y)) {
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
bool loadImageSettingsWindow(char *path, settingsWin *src, SDL_Texture **texture){
    SDL_Surface* loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL ) {
        settingsWindowDestroy(src);
        printf("Couldn't create surface\n");
        return false;
    }
    (*texture) = SDL_CreateTextureFromSurface(src->newRenderer, loadingSurface);
    if ((*texture) == NULL ) {
        SDL_FreeSurface(loadingSurface);
        settingsWindowDestroy(src);
        printf("Couldn't create texture\n");
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}
int isClickOnBack(int x, int y){
    if ((x >= 0 && x <= 148) && (y >= (GAME_HEIGHT-48) && y <= GAME_HEIGHT)) {
        return 1;
    }
    return 0;

}
int isClickOnPlayer1(int x, int y){
    if ((x >=30 && x <= 153) && (y >= 150 && y <= 200)) {
        return 1;
    }
    return 0;
}
int isClickOnPlayer2(int x, int y){
    if ((x >=GAME_WIDTH-163 && x <= GAME_WIDTH-30) && (y >= 150 && y <= 200)) {
        return 1;
    }
    return 0;
}
int isClickOnModerate(int x, int y){
    if ((x >=GAME_WIDTH/2-69 && x <= GAME_WIDTH/2+69) && (y >= 220 && y <= 274)) { // TODO
        return 1;
    }
    return 0;
}
int moderateClicked(int x, int y, bool is1Player){
    if (is1Player) { // TODO
        return isClickOnModerate(x,y);
    }
    return 0;
}

settingsWin *settingsWindowCreate() {
    settingsWin * res = NULL;
    res = (settingsWin *) malloc(sizeof(settingsWin));
    if (res == NULL ) {//TODO Malloc error
        return NULL ;
    }

    // Create an application window with the following settings:
    res->window = SDL_CreateWindow("Chess", // window title
                                   SDL_WINDOWPOS_CENTERED,           // initial x position
                                   SDL_WINDOWPOS_CENTERED,           // initial y position
                                   GAME_WIDTH,                               //
                                   GAME_HEIGHT,                               //
                                   SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->window == NULL ) {
        settingsWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL ;
    }
    res->newRenderer = SDL_CreateRenderer(res->window, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->newRenderer == NULL ) {
        // In the case that the window could not be made...
        settingsWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL ;
    }
    res->is1player=true;
    res->diff=2;
    res->user_color=1;
    if(!loadImageSettingsWindow("../images/back.bmp", res, &(res->backTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/start.bmp", res, &(res->startTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/gameMode.bmp", res, &(res->gameModeTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/difficulty.bmp", res, &(res->difficultyTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/userColor.bmp", res, &(res->userColorTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/white.bmp", res, &(res->whiteTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/whiteFade.bmp", res, &(res->whiteFadeTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/black.bmp", res, &(res->blackTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/blackFade.bmp", res, &(res->blackFadeTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/player1.bmp", res, &(res->player1Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/player2.bmp", res, &(res->player2Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/player1Fade.bmp", res, &(res->player1FadeTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/player2Fade.bmp", res, &(res->player2FadeTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/init.bmp", res, &(res->logoTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/moderateFade.bmp", res, &(res->difficulty3FTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/moderate.bmp", res, &(res->difficulty3Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/noobFade.bmp", res, &(res->difficulty1FTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/noob.bmp", res, &(res->difficulty1Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/easyFade.bmp", res, &(res->difficulty2FTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/easy.bmp", res, &(res->difficulty2Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/hardFade.bmp", res, &(res->difficulty4FTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/hard.bmp", res, &(res->difficulty4Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/expertFade.bmp", res, &(res->difficulty5FTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/expert.bmp", res, &(res->difficulty5Texture)))
        return NULL;
    return res;
}
void settingsWindowDestroy(settingsWin *src) {//TODO finish this function
    if (!src) {
        return;
    }
    if (src->gameModeTexture != NULL ) {
        SDL_DestroyTexture(src->gameModeTexture);
    }if (src->difficultyTexture != NULL ) {
        SDL_DestroyTexture(src->difficultyTexture);
    }if (src->userColorTexture != NULL ) {
        SDL_DestroyTexture(src->userColorTexture);
    }if (src->logoTexture != NULL ) {
        SDL_DestroyTexture(src->logoTexture);
    }if (src->player1Texture != NULL ) {
        SDL_DestroyTexture(src->player1Texture);
    }if (src->player2Texture != NULL ) {
        SDL_DestroyTexture(src->player2Texture);
    }if (src->player2FadeTexture != NULL ) {
        SDL_DestroyTexture(src->player2FadeTexture);
    }if (src->player1FadeTexture != NULL ) {
        SDL_DestroyTexture(src->player1FadeTexture);
    }if (src->difficulty1Texture != NULL ) {
        SDL_DestroyTexture(src->difficulty1Texture);
    }if (src->difficulty2Texture != NULL ) {
        SDL_DestroyTexture(src->difficulty2Texture);
    }if (src->difficulty3Texture != NULL ) {
        SDL_DestroyTexture(src->difficulty3Texture);
    }if (src->difficulty4Texture != NULL ) {
        SDL_DestroyTexture(src->difficulty4Texture);
    }if (src->difficulty5Texture != NULL ) {
        SDL_DestroyTexture(src->difficulty5Texture);
    }if (src->difficulty1FTexture != NULL ) {
        SDL_DestroyTexture(src->difficulty1FTexture);
    }if (src->difficulty2FTexture != NULL ) {
        SDL_DestroyTexture(src->difficulty2FTexture);
    }if (src->difficulty3FTexture != NULL ) {
        SDL_DestroyTexture(src->difficulty3FTexture);
    }if (src->difficulty4FTexture != NULL ) {
        SDL_DestroyTexture(src->difficulty4FTexture);
    }if (src->difficulty5FTexture != NULL ) {
        SDL_DestroyTexture(src->difficulty5FTexture);
    }if (src->whiteTexture != NULL ) {
        SDL_DestroyTexture(src->whiteTexture);
    }if (src->whiteFadeTexture != NULL ) {
        SDL_DestroyTexture(src->whiteFadeTexture);
    }if (src->blackTexture != NULL ) {
        SDL_DestroyTexture(src->blackTexture);
    }if (src->blackFadeTexture != NULL ) {
        SDL_DestroyTexture(src->blackFadeTexture);
    }if (src->startTexture != NULL ) {
        SDL_DestroyTexture(src->startTexture);
    }if (src->backTexture != NULL ) {
        SDL_DestroyTexture(src->backTexture);
    }
    if (src->newRenderer != NULL ) {
        SDL_DestroyRenderer(src->newRenderer);
    }
    if (src->window != NULL ) {
        SDL_DestroyWindow(src->window);
    }
    free(src);
}
void settingsWindowDraw(settingsWin *src) {
    if(src==NULL){
        return;
    }
    SDL_Rect logoR = { .x = GAME_WIDTH/2-100, .y =0, .h = 112, .w =200 };
    SDL_Rect playerHeader = { .x = 30, .y =130, .h = 48, .w =162 };
    SDL_Rect player1R = { .x = 295, .y =130, .h = 54, .w =127 };
    SDL_Rect player2R = { .x = 490, .y =130, .h = 54, .w =137 };
    SDL_Rect diffHeader = { .x = 30, .y =300, .h = 48, .w =135 };
    SDL_Rect diff1R = { .x = 215, .y = 245, .h = 54, .w =95 };
    SDL_Rect diff2R = { .x = 410, .y =245, .h = 54, .w =88 };
    SDL_Rect diff3R = { .x = 595, .y =245, .h = 54, .w =138 };
    SDL_Rect diff4R = { .x = 300, .y =325, .h = 54, .w =91 };
    SDL_Rect diff5R = { .x = 500, .y = 325, .h = 54, .w =108 };
    SDL_Rect colorHeader = { .x = 30, .y =460, .h = 48, .w =147 };
    SDL_Rect color0R = { .x = 295, .y =460, .h = 54, .w =102 };
    SDL_Rect color1R = { .x = 505, .y =460, .h = 54, .w =96 };
    SDL_Rect backR = { .x = 0, .y = (GAME_HEIGHT-48), .h = 48, .w =108 };
    SDL_Rect startR = { .x = GAME_WIDTH-110, .y = (GAME_HEIGHT-48), .h = 48, .w =110 };
//TODO add more difficulties and user_color
    SDL_SetRenderDrawColor(src->newRenderer, 0, 0, 0, 0);
    SDL_RenderClear(src->newRenderer);
    SDL_RenderCopy(src->newRenderer, src->logoTexture, NULL, &logoR);
    SDL_RenderCopy(src->newRenderer, src->gameModeTexture, NULL, &playerHeader);
    SDL_RenderCopy(src->newRenderer, src->player1Texture, NULL, &player1R);
    SDL_RenderCopy(src->newRenderer, src->player2FadeTexture, NULL, &player2R);
    SDL_RenderCopy(src->newRenderer, src->difficultyTexture, NULL, &diffHeader);
    SDL_RenderCopy(src->newRenderer, src->difficulty1FTexture, NULL, &diff1R);
    SDL_RenderCopy(src->newRenderer, src->difficulty2Texture, NULL, &diff2R);
    SDL_RenderCopy(src->newRenderer, src->difficulty3FTexture, NULL, &diff3R);
    SDL_RenderCopy(src->newRenderer, src->difficulty4FTexture, NULL, &diff4R);
    SDL_RenderCopy(src->newRenderer, src->difficulty5FTexture, NULL, &diff5R);
    SDL_RenderCopy(src->newRenderer, src->userColorTexture, NULL, &colorHeader);
    SDL_RenderCopy(src->newRenderer, src->whiteTexture, NULL, &color0R);
    SDL_RenderCopy(src->newRenderer, src->blackFadeTexture, NULL, &color1R);
    SDL_RenderCopy(src->newRenderer, src->backTexture, NULL, &backR);
    SDL_RenderCopy(src->newRenderer, src->startTexture, NULL, &startR);
//    if( src->diff!=3 || src->is1player==false) {
//        SDL_RenderCopy(src->newRenderer, src->difficulty3FTexture, NULL, &diff3R);
//    }
//    else {
//        SDL_RenderCopy(src->newRenderer, src->difficulty3Texture, NULL, &diff3R);
//    }
//    SDL_RenderCopy(src->mainRenderer, src->quitTexture, NULL, &quitR);
    SDL_RenderPresent(src->newRenderer);
}
EVENT settingsWindowHandleEvent(settingsWin *src, SDL_Event *event){
    if (!event) {
        return GUI_INVALID_ARGUMENT;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (isClickOnBack(event->button.x, event->button.y)) {
                return SETTINGS_BACK;}
            if(isClickOnPlayer1(event->button.x, event->button.y)){
                return SETTINGS_1PLAYER;
            }
            if (moderateClicked(event->button.x, event->button.y, src->is1player)){
                src->diff=3;
            }

//            } else if (isClickOnLoad(event->button.x, event->button.y)) {
//                return MAIN_LOAD_GAME;
//            }
//            else if (isClickOnQuit(event->button.x, event->button.y)) {
//                return MAIN_QUIT;
//            }
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
