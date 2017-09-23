
#ifndef CHESS_MAINAUX_H
#define CHESS_MAINAUX_H
#include "ChessGame.h"
#include "MiniMax.h"

/**
 *MainAux Summary:
 *  this module contains the GameSession struct and functions that manage the process of the game
 *  Some of the key functions :
 *
 * bool undo(GameSession* session);                         - undo the last move
 * void quit(ChessGame* game);                              - prints the exiting message
 * void resetSession(GameSession *session);                 - prints the restart message
 * bool saveGame(char* filePath ,GameSession* session);     - saves the current game
 * bool loadGame(char* filePath,GameSession* session);      - loads the game from filePath into session
 * bool processCommandSettings(GameSession* session, ChessCommand command); - handling the commands at setting state
 * bool processCommandGame(GameSession* session,ChessCommand command);  - handling the commands at game state
 * GameSession sessionCreate(int historySize);              - creates new session with the default values
 * int settingState(GameSession *session);                  - processing the setting state
 * void gameStatus(CHESS_MESSAGE msg,GameSession* session); - prints a message according the state of the game
 * CHESS_MESSAGE gameState(GameSession *session);           - processing the game state
*/

//Definitions
#define HISTORYSIZE 6
#define ONE_PLAYER 1
#define TWO_PLAYER 2

/**
 *  A struct that we use to represent a game session
 *  it hold a game, the mode (one or two player), the difficulty and the user color
 */
typedef struct game_session{
    ChessGame* game;
    int mode;
    int difficulty;
    int user_color;
}GameSession;

/**
 * Uses undeMove() to undo the most recent move, prints a message to the user.
 *
 * @param session - the session its game's last move will be undone
 * @return
 * true if the move was succesfully undone, false otherwise.
 */
bool undo(GameSession* session);

/**
 * prints the quitting message
 * @param game
 */
void quit(ChessGame* game);

/**
 * prints the restarting message
 * @param game
 */
void resetSession(GameSession *session);

/**
 * saves the current state of the session to an xml file
 *
 * @param filePath - the path to the file
 * @param session - the current game session
 * @return
 * true if the session was successfully saved, false otherwise.
 */
bool saveGame(char *filePath,  GameSession *session);

/**
 * loads a game from an xml file
 *
 * @param filePath - the path to the file
 * @param session - the session the saved game will be loaded into
 * @return
 * true if the session was successfully loaded, false otherwise.
 */
bool loadGame(char *filePath, GameSession *session);

/**
 * processing user input at settings state
 * prints a message to the user according to their input
 *
 * @param session - the current game session
 * @param command - the command of the user
 * @return
 * true if the game should go on to game state (depending on the type of the command), false otherwise
 */
bool processCommandSettings(GameSession* session, ChessCommand command);

/**
 * processing user input at game state
 * prints a message to the user according to their input
 *
 * @param session - the current game session
 * @param command - the command of the user
 * @return
 * true if the game should go on to another phase (other player move, quit, etc..), false if it is still the user's turn
 * (save game, get moves, illegal command, etc)
 */
bool processCommandGame(GameSession* session,ChessCommand command);

/**
 * creates a new game session
 *
 * @param historySize - the number of moves that will be kept in history
 * @return
 * a new GameSession with the default values
 */
GameSession sessionCreate(int historySize);

/**
 * proccesing the setting state. i.e initializing the current session fields and using processCommandSettings()
 *
 * @param session - the current game session
 * @return
 * 1 if we should go to game state and 0 if we should quit
 */
int settingState(GameSession *session);

/**
 * print a message to the user according to the state of the game and the current player
 *
 * @param session - the current game session
 * @param msg - the state of the game i.e mate, check, tie, or continue
 */
void gameStatus(CHESS_MESSAGE msg,GameSession* session);

/**
 * simulates the game state
 *
 * @param session - the current game session
 * @return
 * CHESS_MESSAGE indicates if the games ended in a mate, tie, quit or reset
 */
CHESS_MESSAGE gameState(GameSession *session);

#endif //CHESS_MAINAUX_H
