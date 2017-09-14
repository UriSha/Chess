
#ifndef CHESS_MAINAUX_H
#define CHESS_MAINAUX_H
#include "ChessGame.h"
#include "MiniMax.h"
#define HISTORYSIZE 6
#define ONE_PLAYER 1
#define TWO_PLAYER 2

typedef struct game_session{
    ChessGame* game;
    int mode;
    int difficulty;
    int userColor;
}GameSession;
bool undo(ChessGame* game, int mode);
void quit(ChessGame* game);
void resetSession(GameSession *session);
bool saveGame(char* filePath ,ChessGame* game,int mode, int difficulty, int userColor);
bool loadGame(char* filePath,GameSession* gameSession);
bool processCommandSettings(GameSession* session, ChessCommand command);
bool processCommandGame(GameSession* session,ChessCommand command);
int gameState(GameSession *session);
void settingState(GameSession* session);
#endif //CHESS_MAINAUX_H
