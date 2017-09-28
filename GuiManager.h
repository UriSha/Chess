
#ifndef CHESS_GUIMANAGER_H
#define CHESS_GUIMANAGER_H

#include "GuiWindows.h"

#define MAX_NUM_OF_SLOTS 5

typedef enum {
    MAIN_WINDOW_ACTIVE,
    SETTINGS_WINDOW_ACTIVE,
    LOAD_GAME_WINDOW_ACTIVE,
    GAME_WINDOW_ACTIVE
} ACTIVE_WINDOW;

typedef enum {
    MANAGER_QUIT,
    MANAGER_NONE,
} MANAGER_EVENET;

typedef struct {
    gameWin *gameWin;
    mainWin *mainWin;
    settingsWin *settingsWin;
    loadGameWin *loadGameWin;
    ACTIVE_WINDOW activeWin;
} GuiManager;

GuiManager *ManagerCreate();

void ManagerDestroy(GuiManager *src);

void ManagerDraw(GuiManager *src, GameSession *session);

MANAGER_EVENET ManagerHandleEvent(GameSession *session, GuiManager *src, SDL_Event *event);

MANAGER_EVENET handleManagerDueToMainEvent(GameSession *session, GuiManager *src, EVENT event);

MANAGER_EVENET handleManagerDueToSettingsEvent(GameSession *session, GuiManager *src, EVENT event);

MANAGER_EVENET handleManagerDueToLoadEvent(GameSession *session, GuiManager *src, EVENT event);

MANAGER_EVENET handleManagerDueToGameEvent(GameSession *session, GuiManager *src, GAME_EVENT event);

bool saveFromGameWindow(GameSession *session, gameWin *gameWin);

#endif //CHESS_GUIMANAGER_H
