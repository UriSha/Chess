
#ifndef CHESS_GUISETTINGSWINDOW_H
#define CHESS_GUISETTINGSWINDOW_H

#include "GuiDefinitions.h"

/**
 * The settings Gui window
 * Has 3 functionalities:
 *          choosing game mode - one or two players
 *          choosing difficulty (only in one player mode) - noob, easy, moderate, hard or expert
 *          choosing user color (only in one player mode) - white or black
 */
typedef struct {
    SDL_Window *window;
    SDL_Renderer *settingsRenderer;
    SDL_Texture *gameModeTexture;
    SDL_Texture *difficultyTexture;
    SDL_Texture *userColorTexture;
    SDL_Texture *logoTexture;
    SDL_Texture *player1Texture;
    SDL_Texture *player2Texture;
    SDL_Texture *player2FadeTexture;
    SDL_Texture *player1FadeTexture;
    SDL_Texture *difficulty1Texture;
    SDL_Texture *difficulty2Texture;
    SDL_Texture *difficulty3Texture;
    SDL_Texture *difficulty4Texture;
    SDL_Texture *difficulty5Texture;
    SDL_Texture *difficulty1FTexture;
    SDL_Texture *difficulty2FTexture;
    SDL_Texture *difficulty3FTexture;
    SDL_Texture *difficulty4FTexture;
    SDL_Texture *difficulty5FTexture;
    SDL_Texture *whiteTexture;
    SDL_Texture *whiteFadeTexture;
    SDL_Texture *blackTexture;
    SDL_Texture *blackFadeTexture;
    SDL_Texture *startTexture;
    SDL_Texture *backTexture;
    bool is1player;
    int diff;
    int user_color;
} settingsWin;

/**
 * Event that occur in the main menu window
 */
typedef enum {
    SETTINGS_INVALID_GUI_ARGUMENT,
    SETTINGS_NONE,
    SETTINGS_BACK,
    SETTINGS_START,
    SETTINGS_1PLAYER,
    SETTINGS_2PLAYER,
    SETTINGS_1DIFF,
    SETTINGS_2DIFF,
    SETTINGS_3DIFF,
    SETTINGS_4DIFF,
    SETTINGS_5DIFF,
    SETTINGS_USERCOLOR_0,
    SETTINGS_USERCOLOR_1,
    SETTINGS_QUIT,

} SETTINGS_EVENT;

/**
 * Loads and image into an SDL_Texture
 *
 * @param path - the path to the image file
 * @param src - the settings window
 * @param texture - the texture of the image
 * @return
 * true if the loading was successful
 */
bool loadImageSettingsWindow(char *path, settingsWin *src, SDL_Texture **texture);

/**
 * Creates a new settings window
 *
 * @return
 * a pointer to the window created
 */
settingsWin *settingsWindowCreate();

/**
 * Draws the settings window
 */
void settingsWindowDraw(settingsWin *src);

/**
 * Destroys the main menu input window
 */
void settingsWindowDestroy(settingsWin *src);

/**
 * @return
 * SETTINGS_EVENT according to the event occurred
 */
SETTINGS_EVENT settingsWindowHandleEvent(settingsWin *src, SDL_Event *event);



#endif //CHESS_GUISETTINGSWINDOW_H
