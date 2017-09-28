
#ifndef CHESS_GUIMANAGER_H
#define CHESS_GUIMANAGER_H

#include "GuiWindows.h"

typedef enum{
    MAIN_WINDOW_ACTIVE,
    SETTINGS_WINDOW_ACTIVE,
    LOAD_GAME_WINDOW_ACTIVE,
    GAME_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
    MANAGER_QUIT,
    MANAGER_NONE,
}MANAGER_EVENET;

typedef struct {
    gameWin* gameWin;
    mainWin* mainWin;
    settingsWin* settingsWin;
    loadGameWin* loadGameWin;
    ACTIVE_WINDOW activeWin;
} GuiManager;

GuiManager* ManagerCreate();

void ManagerDestroy(GuiManager* src);

void ManagerDraw(GuiManager* src, GameSession* session);

MANAGER_EVENET ManagerHandleEvent(GameSession* session,GuiManager* src, SDL_Event* event) ;
MANAGER_EVENET handleManagerDueToMainEvent( GameSession* session, GuiManager *src, EVENT event);

MANAGER_EVENET handleManagerDueToGameEvent(GameSession* session,GuiManager *src, GAME_EVENT event);
#endif //CHESS_GUIMANAGER_H
