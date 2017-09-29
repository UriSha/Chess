#ifndef CHESS_GUIGAMEWINDOW_H
#define CHESS_GUIGAMEWINDOW_H


#include "GuiDefinitions.h"
#define X_GAME_BUTTONS 550
#define GAME_BUTTONS_HIGHT 53
#define PIXELS_TO_CHANGE_MOTION 20


/**
 * The game Gui window
 * allows the user to play chess
 * has 6 buttons:
 *          undo (only for one player) - undo the last move of the computer and the user
 *          restart game - restarts the game with the same settings
 *          save game - saves the game in the next open slot or runs over the oldest
 *          load game - opens the load window
 *          Main menu game - opens the main menu window
 *          Quit - terminates the program
 */
typedef struct {
    SDL_Window *window;
    SDL_Renderer *gameRenderer;
    SDL_Texture *gameBoardTexture;
    SDL_Texture *restartTexture;
    SDL_Texture *saveTexture;
    SDL_Texture *saveFadeTexture;
    SDL_Texture *loadTexture;
    SDL_Texture *undoFadeTexture;
    SDL_Texture *undoTexture;
    SDL_Texture *mainMenuTexture;
    SDL_Texture *quitTexture;
    SDL_Texture *pawnWhiteTexture;
    SDL_Texture *pawnBlackTexture;
    SDL_Texture *knightWhiteTexture;
    SDL_Texture *knightBlackTexture;
    SDL_Texture *bishopWhiteTexture;
    SDL_Texture *bishopBlackTexture;
    SDL_Texture *rookWhiteTexture;
    SDL_Texture *rookBlackTexture;
    SDL_Texture *queenWhiteTexture;
    SDL_Texture *queenBlackTexture;
    SDL_Texture *kingWhiteTexture;
    SDL_Texture *kingBlackTexture;
    SDL_Rect movingRect;
    Position moveSrc;
    Position moveDest;
    int currentlyDragged;
    int isSaved;
    int getMovesShowing;
    SDL_Texture** movesGrid;
    SDL_Texture* yellow;
    SDL_Texture* red;
    SDL_Texture* green;
    SDL_Texture* purple;
} gameWin;

/**
 * Event that occur in the main menu window
 */
typedef enum{
    GAME_QUIT_SAVED,
    GAME_QUIT_UNSAVED,
    GAME_UNDO,
    GAME_RESTART,
    GAME_MAINMENU_SAVED,
    GAME_MAINMENU_UNSAVED,
    GAME_SAVE,
    GAME_LOAD,
    GAME_MOVE,
    GAME_NONE,
    GAME_INVALID
}GAME_EVENT;

/**
 * Loads and image into an SDL_Texture
 *
 * @param path - the path to the image file
 * @param src - the settings window
 * @param texture - the texture of the image
 * @return
 * true if the loading was successful
 */
bool loadImageGameWindow(char *path, gameWin *src, SDL_Texture **texture);

/**
 * Creates a new game window
 *
 * @return
 * a pointer to the window created
 */
gameWin *gameWindowCreate(GameSession *session, int isAlreadySaved);

/**
 * @param gameWin - the current game window
 * @param soldier - char representing a chess piece
 * @return
 *
 * @return
 * the SDL_Texture that holds the image of the input soldier
 */
SDL_Texture *getTexture(gameWin *gameWin, char soldier);

/**
 * Draws the game window
 */
void gameWindowDraw(gameWin *src, GameSession *session);

/**
 * Destroys the game input window
 */
void gameWindowDestroy(gameWin *src);

/**
 * @return
 * GAME_EVENT according to the event occurred
 */
GAME_EVENT gameWindowHandleEvent(GameSession* session, gameWin *src, SDL_Event *event);

#endif //CHESS_GUIGAMEWINDOW_H
