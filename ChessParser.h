#ifndef CHESS_CHESSPARSER_H
#define CHESS_CHESSPARSER_H

#include <stdbool.h>

#define MAX_LINE_LENGTH 1024

//a type used to represent a Game State command
typedef enum {
    UNDO_MOVE,
    MOVE,
    GET_MOVES,
    SAVE,
    G_QUIT,
    RESTART,
    G_INVALID_LINE,
} GAMESTATE_COMMAND;

//a type used to represent a Setting State command
typedef enum {
    LOAD,
    GAME_MODE,
    DIFFICULTY,
    USER_COLOR,
    DEFAULT,
    PRINT_SETTING,
    S_QUIT,
    START,
    S_INVALID_LINE,
} SETTINGSTATE_COMMAND;

typedef struct board_position {
    char column;
    int row;
} Position;

//a new type that is used to encapsulate a parsed line of a game state
typedef struct command_game {
    GAMESTATE_COMMAND cmd;
    Position source;
    Position Destination;
    bool validArg;
} GCommand;

//a new type that is used to encapsulate a parsed line of a setting state
typedef struct command_setting {
    SETTINGSTATE_COMMAND cmd;
    int argument;
    bool validArg; //is set to true if the line contains a valid argument
} SCommand;

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool spParserIsInt(const char* str);




#endif
