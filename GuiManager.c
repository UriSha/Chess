#include "GuiManager.h"
#include "GuiWindows.h"

GuiManager* ManagerCreate() {
    GuiManager* res = (GuiManager*) malloc(sizeof(GuiManager));
    if (res == NULL ) {
        return NULL ;
    }
    res->mainWin = mainWindowCreate();
    if (res->mainWin == NULL ) {
        free(res);
        return NULL ;
    }
//    res->gameWin = NULL;
    res->activeWin = MAIN_WINDOW_ACTIVE;
    return res;
}
void ManagerDestroy(GuiManager* src) {
    if (!src) {
        return;
    }
//    if (src->activeWin == GAME_WINDOW_ACTIVE) {
//        spGameWindowDestroy(src->gameWin);
//    }
    mainWindowDestroy(src->mainWin);
    free(src);
}
void ManagerDraw(GuiManager* manager) {
    if (!manager) {
        return;
    }
    if (manager->activeWin == MAIN_WINDOW_ACTIVE) {
        mainWindowDraw(manager->mainWin);
    }else if(manager->activeWin == SETTINGS_WINDOW_ACTIVE){
        settingsWindowDraw(manager->settingsWin);
    }
}
MANAGER_EVENET handleManagerDueToMainEvent(GameSession* session,GuiManager* src, EVENT event) {
    if (src == NULL ) {
        return MANAGER_NONE;
    }
    if (event == MAIN_NEW_GAME) {
        (*session)=sessionCreate(HISTORYSIZE);
        windowHide(src->mainWin->window);
        src->settingsWin = settingsWindowCreate();
        if (src->settingsWin == NULL ) {
            printf("Couldn't move to settings window\n");
            return MANAGER_QUTT;
        }
        src->activeWin = SETTINGS_WINDOW_ACTIVE;
    }
    else if(event==SETTINGS_BACK)
    {
        windowHide(src->settingsWin->window);
        windowShow(src->mainWin->window);
        src->activeWin=MAIN_WINDOW_ACTIVE;
    }
    if(event==SETTINGS_1PLAYER)
    {
        session->mode=ONE_PLAYER;
        src->settingsWin->is1player=true;
//        openRestOfSettings();//TODO open the rest of the settings function
    }
    if (event==SETTINGS_2PLAYER){

    }
    if (event == MAIN_QUIT) {
        return MANAGER_QUTT;
    }
    return MANAGER_NONE;
}

//MANAGER_EVENET handleManagerDueToGameEvent(GuiManager* src){//,SP_GAME_EVENT event) {
//    if (event == SP_GAME_EVENT_NONE || src == NULL ) {
//        return SP_MANAGER_NONE;
//    }
//    if (event == SP_GAME_EVENT_X_WON) {
//        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "X won",
//                                 NULL );
//    } else if (event == SP_GAME_EVENT_O_WON) {
//        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "O won",
//                                 NULL );
//    } else if (event == SP_GAME_EVENT_TIE) {
//        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
//                                 "it's a tie", NULL );
//    }
//    spGameWindowDestroy(src->gameWin);
//    src->gameWin = NULL;
//    src->activeWin = MAIN_WINDOW_ACTIVE;
//    windowShow(src->mainWin->window);
//    return MANAGER_NONE;
//}

MANAGER_EVENET ManagerHandleEvent(GameSession* session,GuiManager* src, SDL_Event* event) {
    if (src == NULL || event == NULL ) {
        return MANAGER_NONE;
    }
    if (src->activeWin == MAIN_WINDOW_ACTIVE) {
        EVENT mainEvent = mainWindowHandleEvent(src->mainWin, event);
        return handleManagerDueToMainEvent(session,src, mainEvent);
    } if(src->activeWin == SETTINGS_WINDOW_ACTIVE){
        EVENT gameEvent = settingsWindowHandleEvent(src->settingsWin, event);
//        ManagerDraw(src);
        return handleManagerDueToMainEvent(session,src, gameEvent);
    }
    return MANAGER_NONE;
}

