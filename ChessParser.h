#ifndef CHESS_CHESSPARSER_H
#define CHESS_CHESSPARSER_H

#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MALLOC_ERROR "Error: malloc has failed\n"
#define MAX_LINE_LENGTH 1024
#define DELIMITER " \t\r\n"
#define INVALID_ROW 100
#define INVALID_COL '\0'

//a type used to represent a Game State command
typedef enum {
    UNDO_MOVE,
    MOVE,
    GET_MOVES,
    SAVE,
    QUIT,
    RESTART,
    LOAD,
    GAME_MODE,
    DIFFICULTY,
    USER_COLOR,
    DEFAULT,
    PRINT_SETTING,
    START,
    INVALID_LINE,
} CHESS_COMMAND;



typedef struct board_position {
    char column;
    int row;
} Position;

//a new type that is used to encapsulate a parsed line of a game state
typedef struct command_game {
    CHESS_COMMAND cmd;
    Position source;
    Position destination;
    bool validArg;
    int argument;
    char* path;
} ChessCommand;



/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool isInt(const char* str);

Position getPosition(char *token);

CHESS_COMMAND getChessCommand (char* token);

ChessCommand parseLine(const char* str);





#endif
