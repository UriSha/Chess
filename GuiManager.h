
#ifndef CHESS_GUIMANAGER_H
#define CHESS_GUIMANAGER_H

//#include "GuiWindows.h"
#include "GuiSettingsWindow.h"
#include "GuiLoadWindow.h"
#include "GuiGameWindow.h"
#include "GuiMainWindow.h"


typedef enum {
    MAIN_WINDOW_ACTIVE,
    SETTINGS_WINDOW_ACTIVE,
    LOAD_GAME_WINDOW_ACTIVE,
    GAME_WINDOW_ACTIVE
} ACTIVE_WINDOW;

typedef enum {
    MANAGER_QUIT,
    MANAGER_NONE,
//    MANAGER_CHECK,
//    MANAGER_TIE,
//    MANAGER_MATE,
} MANAGER_EVENT;

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

MANAGER_EVENT ManagerHandleEvent(GameSession *session, GuiManager *src, SDL_Event *event);

MANAGER_EVENT handleManagerDueToMainEvent(GameSession *session, GuiManager *src, MAIN_EVENT event);

MANAGER_EVENT handleManagerDueToSettingsEvent(GameSession *session, GuiManager *src, SETTINGS_EVENT event);

MANAGER_EVENT handleManagerDueToLoadEvent(GameSession *session, GuiManager *src, LOAD_EVENT event);

MANAGER_EVENT handleManagerDueToGameEvent(GameSession *session, GuiManager *src, GAME_EVENT event);

bool saveFromGameWindow(GameSession *session);
int askWhetherToSave(GameSession *session,gameWin* src);

#endif //CHESS_GUIMANAGER_H
