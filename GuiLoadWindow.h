#ifndef CHESS_GUILOADWINDOW_H
#define CHESS_GUILOADWINDOW_H

#include "GuiDefinitions.h"


/**
 * The load game Gui window
 * allows the user to load a game from his previous saved games
 * the user can choose from MAX_NUM_OF_SLOTS recent saved game
 */
typedef struct {
    SDL_Window *window;
    SDL_Renderer *loadRenderer;
    SDL_Texture *logoTexture;
    SDL_Texture *headerTexture;
    SDL_Texture *load1Texture;
    SDL_Texture *load1FadeTexture;
    SDL_Texture *load2Texture;
    SDL_Texture *load2FadeTexture;
    SDL_Texture *load3Texture;
    SDL_Texture *load3FadeTexture;
    SDL_Texture *load4Texture;
    SDL_Texture *load4FadeTexture;
    SDL_Texture *load5Texture;
    SDL_Texture *load5FadeTexture;
    SDL_Texture *startTexture;
    SDL_Texture *backTexture;
    int chosenSlot;
    int availableSlots;
    int fromMainMenu;
    int isCurrentGameSaved;
} loadGameWin;

/**
 * Event that occur in the load window
 */
typedef enum {
    LOAD_1SLOT,
    LOAD_2SLOT,
    LOAD_3SLOT,
    LOAD_4SLOT,
    LOAD_5SLOT,
    LOAD_BACK,
    LOAD_START,
    LOAD_QUIT,
    LOAD_INVALID_GUI_ARGUMENT,
    LOAD_NONE,
} LOAD_EVENT;

/**
 * Loads and image into an SDL_Texture
 *
 * @param path - the path to the image file
 * @param src - the main menu window
 * @param texture - the texture of the image
 * @return
 * true if the loading was successful
 */
bool loadImageLoadWindow(char *path, loadGameWin *src, SDL_Texture **texture);

/**
 * Creates a new load window
 *
 * @return
 * a pointer to the window created
 */
loadGameWin *loadGameWindowCreate();

/**
 * Draws the load window
 */
void loadGameWindowDraw(loadGameWin *src);

/**
 * Destroys the load input window
 */
void loadGameWindowDestroy(loadGameWin *src);

/**
 * @return
 * LOAD_EVENT according to the event occurred
 */
LOAD_EVENT loadGameWindowHandleEvent(loadGameWin *src, SDL_Event *event);


#endif //CHESS_GUILOADWINDOW_H
