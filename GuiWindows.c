#include <stdbool.h>
#include "GuiWindows.h"
int isClickOnNew(int x, int y) {
    if ((x >= 75 && x <= 234) && (y >= 100 && y <= 150)) {
        return 1;
    }
    return 0;
}
int isClickOnLoad(int x, int y) {
    if ((x >= 75 && x <= 237) && (y >= 170 && y <= 220)) {
        return 1;
    }
    return 0;
}
int isClickOnQuit(int x, int y) {
    if ((x >= 75 && x <= 168) && (y >= 240 && y <= 290)) {
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
//    loadingSurface = SDL_LoadBMP("../images/new.bmp");
//    if (loadingSurface == NULL ) {
//        mainWindowDestroy(res);
//        printf("couldn't create new.bmp surface\n");
//        return NULL ;
//    }
//    res->newTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
//                                                     loadingSurface);
//    if (res->newTexture == NULL ) {
//        SDL_FreeSurface(loadingSurface);
//        mainWindowDestroy(res);
//        printf("couldn't create new.bmp texture\n");
//        return NULL ;
//    }
//    SDL_FreeSurface(loadingSurface);
//
//    loadingSurface = SDL_LoadBMP("../images/load.bmp");
//    if (loadingSurface == NULL ) {
//        mainWindowDestroy(res);
//        printf("couldn't create load.bmp surface\n");
//        return NULL ;
//    }
//    res->loadTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
//                                                    loadingSurface);
//    if (res->loadTexture == NULL ) {
//        SDL_FreeSurface(loadingSurface);
//        mainWindowDestroy(res);
//        printf("couldn't create load.bmp texture\n");
//        return NULL ;
//    }
//    SDL_FreeSurface(loadingSurface);
//    loadingSurface = SDL_LoadBMP("../images/quit.bmp");
//    if (loadingSurface == NULL ) {
//        mainWindowDestroy(res);
//        printf("couldn't create quit.bmp surface\n");
//        return NULL ;
//    }
//    res->quitTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
//                                                    loadingSurface);
//    if (res->quitTexture == NULL ) {
//        SDL_FreeSurface(loadingSurface);
//        mainWindowDestroy(res);
//        printf("couldn't create quit.bmp texture\n");
//        return NULL ;
//    }
//    SDL_FreeSurface(loadingSurface);
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
    SDL_Rect newR = { .x = 75, .y = 100, .h = 50, .w = 159 };
    SDL_Rect loadR = { .x = 75, .y = 170, .h = 50, .w = 162 };
    SDL_Rect quitR = { .x = 75, .y = 240, .h = 50, .w = 93 };
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
    if(!loadImageSettingsWindow("../images/new.bmp", res, &(res->difficulty1Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/back.bmp", res, &(res->backTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/player1.bmp", res, &(res->player1Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/player2.bmp", res, &(res->player2Texture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/init.bmp", res, &(res->initTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/moderateFade.bmp", res, &(res->difficulty3FTexture)))
        return NULL;
    if(!loadImageSettingsWindow("../images/moderate.bmp", res, &(res->difficulty3Texture)))
        return NULL;//TODO load all the rest
    return res;
}
void settingsWindowDestroy(settingsWin *src) {//TODO finish this function
    if (!src) {
        return;
    }
    if (src->difficulty1Texture != NULL ) {
        SDL_DestroyTexture(src->difficulty1Texture);
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
    SDL_Rect backR = { .x = 0, .y = (GAME_HEIGHT-48), .h = 48, .w =108 };
    SDL_Rect player1R = { .x = 200, .y =150, .h = 50, .w =123 };
    SDL_Rect player2R = { .x = 400, .y =150, .h = 50, .w =133 };
    SDL_Rect logoR = { .x = GAME_WIDTH/2-100, .y =0, .h = 112, .w =200 };
//    SDL_Rect diff1R = { .x = 0, .y = (GAME_WIDTH-50), .h = 50, .w =110 };
//    SDL_Rect diff2R = { .x = 75, .y =240, .h = 50, .w =123 };
    SDL_Rect diff3R = { .x = GAME_WIDTH/2-69, .y =220, .h = 54, .w =138 };
//    SDL_Rect diff4R = { .x = 200, .y =0, .h = 112, .w =200 };
//    SDL_Rect diff5R = { .x = 0, .y = (GAME_WIDTH-50), .h = 50, .w =110 };
//    SDL_Rect color0R = { .x = 75, .y =240, .h = 50, .w =123 };
//    SDL_Rect color1R = { .x = 75, .y =310, .h = 50, .w =133 };
//TODO add more difficulties and user_color
    SDL_SetRenderDrawColor(src->newRenderer, 0, 0, 0, 0);
    SDL_RenderClear(src->newRenderer);
    SDL_RenderCopy(src->newRenderer, src->backTexture, NULL, &backR);
    SDL_RenderCopy(src->newRenderer, src->player1Texture, NULL, &player1R);
    SDL_RenderCopy(src->newRenderer, src->player2Texture, NULL, &player2R);
    if( src->diff!=3 || src->is1player==false)
        SDL_RenderCopy(src->newRenderer, src->difficulty3FTexture, NULL, &diff3R);
    else
        SDL_RenderCopy(src->newRenderer, src->difficulty3Texture, NULL, &diff3R);
    SDL_RenderCopy(src->newRenderer, src->initTexture, NULL, &logoR);
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
