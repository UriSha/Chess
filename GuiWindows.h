

#ifndef CHESS_GUIMAINWINDOW_H
#define CHESS_GUIMAINWINDOW_H

#include <SDL.h>
#include <stdbool.h>
#include <SDL_video.h>

#define GAME_WIDTH 800
#define GAME_HEIGHT 600
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

typedef enum {
    MAIN_QUIT, MAIN_NEW_GAME, MAIN_LOAD_GAME, GUI_INVALID_ARGUMENT, NONE,
    SETTINGS_BACK, SETTINGS_START, SETTINGS_1PLAYER, SETTINGS_2PLAYER, SETTINGS_1DIFF,  SETTINGS_2DIFF,
    SETTINGS_3DIFF, SETTINGS_4DIFF, SETTINGS_5DIFF, SETTINGS_USERCOLOR_0, SETTINGS_USERCOLOR_1, LOAD_1SLOT,
    LOAD_2SLOT, LOAD_3SLOT, LOAD_4SLOT, LOAD_5SLOT, LOAD_BACK,
} EVENT;
typedef struct {
    SDL_Window *window;
    SDL_Renderer *mainRenderer;
    SDL_Texture *newTexture;
    SDL_Texture *loadTexture;
    SDL_Texture *quitTexture;
} mainWin;
typedef struct {
    SDL_Window *window;
    SDL_Renderer *newRenderer;
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
    SDL_Texture *load1Texture;
    SDL_Texture *load2Texture;
    SDL_Texture *load3Texture;
    SDL_Texture *load4Texture;
    SDL_Texture *load5Texture;
    SDL_Texture *backTexture;
} loadGameWin;

//Main Window
bool loadImageMainWindow(char* path, mainWin* src,SDL_Texture ** texture);

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
loadGameWin *loadGameWindowCreate();

void loadGamemainWindowDraw(loadGameWin *src);

void loadGameWindowDestroy(loadGameWin *src);

EVENT loadGameWindowHandleEvent(loadGameWin *src, SDL_Event *event);

#endif //CHESS_GUIMAINWINDOW_H
