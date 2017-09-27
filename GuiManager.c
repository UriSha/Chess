#include "GuiManager.h"
#include "GuiWindows.h"

GuiManager *ManagerCreate() {
    GuiManager *res = (GuiManager *) malloc(sizeof(GuiManager));
    if (res == NULL) {
        return NULL;
    }
    res->mainWin = mainWindowCreate();
    if (res->mainWin == NULL) {
        free(res);
        return NULL;
    }
//    res->gameWin = NULL;
    res->activeWin = MAIN_WINDOW_ACTIVE;
    return res;
}

void ManagerDestroy(GuiManager *src) { // TODO find useges
    if (!src)
        return;
//    if (src->activeWin == MAIN_WINDOW_ACTIVE)
//        mainWindowDestroy(src->mainWin);
//    if (src->activeWin == SETTINGS_WINDOW_ACTIVE)
//        settingsWindowDestroy(src->settingsWin);
//    if (src->activeWin == LOAD_GAME_WINDOW_ACTIVE)
//        loadGameWindowDestroy(src->loadGameWin);
//    mainWindowDestroy(src->mainWin);
    free(src);
}

void ManagerDraw(GuiManager *manager, GameSession* session) {
    if (!manager) {
        return;
    }
    if (manager->activeWin == MAIN_WINDOW_ACTIVE) {
        mainWindowDraw(manager->mainWin);
    } else if (manager->activeWin == SETTINGS_WINDOW_ACTIVE) {
        settingsWindowDraw(manager->settingsWin);
    } else if (manager->activeWin == LOAD_GAME_WINDOW_ACTIVE) {
        loadGameWindowDraw(manager->loadGameWin);
    } else if (manager->activeWin == GAME_WINDOW_ACTIVE) {
        gameWindowDraw(manager->gameWin,session);
    }
}

MANAGER_EVENET handleManagerDueToMainEvent(GameSession *session, GuiManager *src, EVENT event) {
    if (src == NULL) {
        return MANAGER_NONE;
    }
    if (event == MAIN_NEW_GAME) {
        (*session) = sessionCreate(HISTORYSIZE);
        mainWindowDestroy(src->mainWin);
        src->settingsWin = settingsWindowCreate();
        if (src->settingsWin == NULL) {
            printf("Couldn't move to settings window\n");
            return MANAGER_QUIT;
        }
        src->activeWin = SETTINGS_WINDOW_ACTIVE;
    }
    if (event == MAIN_LOAD_GAME) {
        (*session) = sessionCreate(HISTORYSIZE);
        mainWindowDestroy(src->mainWin);
        src->loadGameWin = loadGameWindowCreate();
        src->loadGameWin->fromMainMenu = true;//TODO do this also in gameWindow with false parameter
        if (src->loadGameWin == NULL) {
            printf("Couldn't move to settings window\n");
            return MANAGER_QUIT;
        }
        src->activeWin = LOAD_GAME_WINDOW_ACTIVE;
    }
    if (event == LOAD_BACK) {
        if(src->loadGameWin->fromMainMenu)
        {
            gameDestroy(&(session->game));
            free(session);
        }
        loadGameWindowDestroy(src->loadGameWin);
        src->mainWin = mainWindowCreate();
        src->activeWin = MAIN_WINDOW_ACTIVE;
    }
    if (event == LOAD_1SLOT) {
        src->loadGameWin->chosenSlot = 1;

    }
    if (event == LOAD_2SLOT) {
        src->loadGameWin->chosenSlot = 2;
    }
    if (event == LOAD_3SLOT) {
        src->loadGameWin->chosenSlot = 3;
    }
    if (event == LOAD_4SLOT) {
        src->loadGameWin->chosenSlot = 4;
    }
    if (event == LOAD_5SLOT) {
        src->loadGameWin->chosenSlot = 5;
    }
    if (event == LOAD_START) {
        char path[6];
        sprintf(path, "%d.xml", src->loadGameWin->chosenSlot);
        loadGame(path, session);
        loadGameWindowDestroy(src->loadGameWin);
        src->gameWin = gameWindowCreate(session);
        if (src->gameWin == NULL) {
            printf("ERROR: Couldn't move to game window\n");
            return MANAGER_QUIT;
        }
        src->activeWin = GAME_WINDOW_ACTIVE;
    }
    if (event == SETTINGS_BACK) {
        gameDestroy(&(session->game));
        free(session);
        settingsWindowDestroy(src->settingsWin);
        src->mainWin = mainWindowCreate();
        src->activeWin = MAIN_WINDOW_ACTIVE;
    }
    if (event == SETTINGS_START) {
        settingsWindowDestroy(src->settingsWin);
        src->gameWin = gameWindowCreate(session);
        if (src->gameWin == NULL) {
            printf("ERROR: Couldn't move to game window\n");
            return MANAGER_QUIT;
        }
        src->activeWin = GAME_WINDOW_ACTIVE;
    }
    if (event == SETTINGS_1PLAYER) {
        session->mode = ONE_PLAYER;
        src->settingsWin->is1player = true;
    }
    if (event == SETTINGS_2PLAYER) {
        session->mode = TWO_PLAYER;
        src->settingsWin->is1player = false;
    }
    if (event == SETTINGS_1DIFF) {
        session->difficulty = 1;
        src->settingsWin->diff = 1;
    }
    if (event == SETTINGS_2DIFF) {
        session->difficulty = 2;
        src->settingsWin->diff = 2;
    }
    if (event == SETTINGS_3DIFF) {
        session->difficulty = 3;
        src->settingsWin->diff = 3;
    }
    if (event == SETTINGS_4DIFF) {
        session->difficulty = 4;
        src->settingsWin->diff = 4;
    }
    if (event == SETTINGS_5DIFF) {
        session->difficulty = 5;
        src->settingsWin->diff = 5;
    }
    if (event == SETTINGS_USERCOLOR_0) {
        session->user_color = BLACK_PLAYER;
        src->settingsWin->user_color = 0;
    }
    if (event == SETTINGS_USERCOLOR_1) {
        session->user_color = WHITE_PLAYER;
        src->settingsWin->user_color = 1;
    }
    if (event == MAIN_QUIT) {
        return MANAGER_QUIT;
    }
    return MANAGER_NONE;
}

MANAGER_EVENET handleManagerDueToGameEvent(GuiManager *src, EVENT event) {
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
//    gameWindowDestroy(src->gameWin);
//    src->gameWin = NULL;
//    src->activeWin = MAIN_WINDOW_ACTIVE;
//    windowShow(src->mainWin->window);
    if (event == GAME_QUIT)
        return MANAGER_QUIT;
    return MANAGER_NONE;
}

MANAGER_EVENET ManagerHandleEvent(GameSession *session, GuiManager *src, SDL_Event *event) {
    if (src == NULL || event == NULL) {
        return MANAGER_NONE;
    }
    if (src->activeWin == MAIN_WINDOW_ACTIVE) {
        EVENT mainEvent = mainWindowHandleEvent(src->mainWin, event);
        return handleManagerDueToMainEvent(session, src, mainEvent);
    }
    if (src->activeWin == SETTINGS_WINDOW_ACTIVE) {
        EVENT gameEvent = settingsWindowHandleEvent(src->settingsWin, event);
//        ManagerDraw(src);
        return handleManagerDueToMainEvent(session, src, gameEvent);
    }
    if (src->activeWin == LOAD_GAME_WINDOW_ACTIVE) {
        EVENT gameEvent = loadGameWindowHandleEvent(src->loadGameWin, event);
        return handleManagerDueToMainEvent(session, src, gameEvent);
    }
    if (src->activeWin == GAME_WINDOW_ACTIVE) {
        EVENT gameEvent = gameWindowHandleEvent(src->gameWin, event);
        return handleManagerDueToGameEvent(src, gameEvent);
    }
    return MANAGER_NONE;
}

