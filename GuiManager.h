
#ifndef CHESS_GUIMANAGER_H
#define CHESS_GUIMANAGER_H

#include "GuiSettingsWindow.h"
#include "GuiLoadWindow.h"
#include "GuiGameWindow.h"
#include "GuiMainWindow.h"

/**
 * This module is built for managing all the windows in the GUI Mode.
 * The key functions of this module are:
 * GuiManager *ManagerCreate - Creates the GuiManager struct and initialize the main window
 * void ManagerDestroy - Destroys all the windows and frees sll resources
 * void ManagerDraw  - Draws the desired window, according to other functions
 * MANAGER_EVENT ManagerHandleEvent - Handles and sending commands to the other functions :
 * According to the user input and gestures
 */

// This enum is designed for deciding which window should be active
typedef enum {
    MAIN_WINDOW_ACTIVE,
    SETTINGS_WINDOW_ACTIVE,
    LOAD_GAME_WINDOW_ACTIVE,
    GAME_WINDOW_ACTIVE
} ACTIVE_WINDOW;

//This enum is built for the event handler
typedef enum {
    MANAGER_QUIT,
    MANAGER_NONE,
} MANAGER_EVENT;

//The main struct for GUI mode, controls all the windows and the data inside
typedef struct {
    gameWin *gameWin;
    mainWin *mainWin;
    settingsWin *settingsWin;
    loadGameWin *loadGameWin;
    ACTIVE_WINDOW activeWin;
} GuiManager;

/**
 * This function creates the main struct, initialize the main window as the first window to be opened
 * Also this function initialize all the other windows.
 * @return GuiManager pointer, the main struct
 */
GuiManager *ManagerCreate();

/**
 * Destroys the main struct, and frees all resources
 * @param src - Guimanager pointer, the main struct
 */
void ManagerDestroy(GuiManager *src);

/**
 * This function draws the window that is active right now - according to the event handler
 * @param src - The GuiManager
 * @param session  - The GameSession: all the data of the game stored here
 */
void ManagerDraw(GuiManager *src, GameSession *session);

/**
 * This function controls the event sent by the user. it calls other functions and manages the game and the windows
 * @param session - The GameSession: all the data of the game stored here
 * @param src - The GuiManager
 * @param event - The event that was done by the user
 * @return
 * MANAGER_QUIT : if the user wants to quit
 * MANAGER_NON : otherwise
 */
MANAGER_EVENT ManagerHandleEvent(GameSession *session, GuiManager *src, SDL_Event *event);


#endif //CHESS_GUIMANAGER_H
