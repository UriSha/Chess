
#ifndef CHESS_MAINAUX_H
#define CHESS_MAINAUX_H
#include "ChessGame.h"
#define HISTORYSIZE 6
#define ONE_PLAYER 1
#define TWO_PLAYER 2
bool undo(ChessGame* game, int mode);
void quit(ChessGame* game);
void restartGame(ChessGame* game);
bool saveGame(char* filePath ,ChessGame* game,int mode, int difficulty, int userColor);

#endif //CHESS_MAINAUX_H
