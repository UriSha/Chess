

#ifndef CHESS_GUIMAINWINDOW_H
#define CHESS_GUIMAINWINDOW_H

#include <SDL.h>
#include <stdbool.h>
#include <SDL_video.h>
#include "MainAux.h"

#define GAME_WIDTH 800
#define GAME_HEIGHT 600
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define GAMEBOARD_X 20
#define GAMEBOARD_Y 40


typedef enum {
    MAIN_QUIT,
    MAIN_NEW_GAME,
    MAIN_LOAD_GAME,
    GUI_INVALID_ARGUMENT,
    NONE,
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
    SEETINGS_QUIT,
    LOAD_1SLOT,
    LOAD_2SLOT,
    LOAD_3SLOT,
    LOAD_4SLOT,
    LOAD_5SLOT,
    LOAD_BACK,
    LOAD_START,
    LOAD_QUIT,
} EVENT;
typedef enum{
    GAME_QUIT,
    GAME_UNDO,
    GAME_RESTART,
    GAME_MAINMENU,
    GAME_SAVE,
    GAME_LOAD,
    GAME_MOVE,
    GAME_NONE,
    GAME_INVALID
}GAME_EVENT;
typedef struct {
    SDL_Window *window;
    SDL_Renderer *mainRenderer;
    SDL_Texture *newTexture;
    SDL_Texture *loadTexture;
    SDL_Texture *quitTexture;
} mainWin;
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
} loadGameWin;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *gameRenderer;
    SDL_Texture *gameBoardTexture;
    SDL_Texture *restartTexture;
    SDL_Texture *saveTexture;
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
} gameWin;

//Main Window
bool loadImageMainWindow(char *path, mainWin *src, SDL_Texture **texture);

mainWin *mainWindowCreate();

void mainWindowDraw(mainWin *src);

void mainWindowDestroy(mainWin *src);

void windowHide(SDL_Window *srcWindow);

void windowShow(SDL_Window *srcWindow);

EVENT mainWindowHandleEvent(mainWin *src, SDL_Event *event);

//Settings Window
bool loadImageSettingsWindow(char *path, settingsWin *src, SDL_Texture **texture);

settingsWin *settingsWindowCreate();

void settingsWindowDraw(settingsWin *src);

void settingsWindowDestroy(settingsWin *src);

EVENT settingsWindowHandleEvent(settingsWin *src, SDL_Event *event);

//Load Game Window
bool loadImageLoadWindow(char *path, loadGameWin *src, SDL_Texture **texture);

loadGameWin *loadGameWindowCreate();

void loadGameWindowDraw(loadGameWin *src);

void loadGameWindowDestroy(loadGameWin *src);

EVENT loadGameWindowHandleEvent(loadGameWin *src, SDL_Event *event);

//Game Window
bool loadImageGameWindow(char *path, gameWin *src, SDL_Texture **texture);

gameWin *gameWindowCreate(GameSession *session);

SDL_Texture *getTexture(gameWin *gameWin, char soldier);

void gameWindowDraw(gameWin *src, GameSession *session);

void gameWindowDestroy(gameWin *src);

GAME_EVENT gameWindowHandleEvent(GameSession* session, gameWin *src, SDL_Event *event);

#endif //CHESS_GUIMAINWINDOW_H
