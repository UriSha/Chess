
#ifndef CHESS_GUISETTINGSWINDOW_H
#define CHESS_GUISETTINGSWINDOW_H

#include "GuiDefinitions.h"


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

//Settings Window
bool loadImageSettingsWindow(char *path, settingsWin *src, SDL_Texture **texture);

settingsWin *settingsWindowCreate();

void settingsWindowDraw(settingsWin *src);

void settingsWindowDestroy(settingsWin *src);

SETTINGS_EVENT settingsWindowHandleEvent(settingsWin *src, SDL_Event *event);



#endif //CHESS_GUISETTINGSWINDOW_H
