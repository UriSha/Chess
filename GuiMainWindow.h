#ifndef CHESS_GUIMAINWINDOW_H
#define CHESS_GUIMAINWINDOW_H


#include "GuiDefinitions.h"

/**
 * The main menu Gui window, first thing the user sees in Gui mode
 * has 3 buttons:
 *          new game - the settings window opens
 *          load game - the settings window opens
 *          quit - terminates the program
 */
typedef struct {
    SDL_Window *window;
    SDL_Renderer *mainRenderer;
    SDL_Texture *newTexture;
    SDL_Texture *loadTexture;
    SDL_Texture *quitTexture;
} mainWin;

/**
 * Event that occur in the main menu window
 */
typedef enum {
    MAIN_QUIT,
    MAIN_NEW_GAME,
    MAIN_LOAD_GAME,
    MAIN_INVALID_GUI_ARGUMENT,
    MAIN_NONE,
} MAIN_EVENT;

/**
 * Loads and image into an SDL_Texture
 *
 * @param path - the path to the image file
 * @param src - the main menu window
 * @param texture - the texture of the image
 * @return
 * true if the loading was successful
 */
bool loadImageMainWindow(char *path, mainWin *src, SDL_Texture **texture);

/**
 * Creates a new main menu window
 *
 * @return
 * a pointer to the window created
 */
mainWin *mainWindowCreate();

/**
 * Draws the main menu window
 */
void mainWindowDraw(mainWin *src);

/**
 * Destroys the main menu input window
 */
void mainWindowDestroy(mainWin *src);

/**
 * @return
 * MAIN_EVENT according to the event occurred
 */
MAIN_EVENT mainWindowHandleEvent(SDL_Event *event);

#endif //CHESS_GUIMAINWINDOW_H
