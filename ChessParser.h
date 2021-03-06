#ifndef CHESS_CHESSPARSER_H
#define CHESS_CHESSPARSER_H

#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Definitions
#define MALLOC_ERROR "Error: malloc has failed\n"
#define MAX_LINE_LENGTH 1024
#define DELIMITER " \t\r\n"
#define INVALID_ROW 100
#define INVALID_COL '\0'

//a type used to represent a Game State or Setting State command
typedef enum {
    UNDO_MOVE,
    MOVE,
    GET_MOVES,
    SAVE,
    QUIT,
    RESET,
    LOAD,
    GAME_MODE,
    DIFFICULTY,
    USER_COLOR,
    DEFAULT,
    PRINT_SETTING,
    START,
    INVALID_LINE,
    CASTLE,
} CHESS_COMMAND;


//a type used to represent a chess game board position
typedef struct board_position {
    char column;  // A to H
    int row;     // 1 to 8
} Position;

//a new type that is used to encapsulate a parsed line of a game state
typedef struct command_game {
    CHESS_COMMAND cmd;
    Position source;
    Position destination;
    bool validArg;
    int argument;
    char* path;
    bool isNotInFormat;
} ChessCommand;



/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool isInt(const char* str);
/**
 * Checks if a token we got from a user is printed "by the rules"
 * @param token - the string we got from the user
 * @return
 * True - if the format is right
 * False - otherwise
 */
bool isInFormat(char* token);
/**
 * parses a Position from a string input
 *
 * @return
 * board Position
 */
Position getPosition(char *token);

/**
 * Given a string, returns the matching enum
 *
 * @return
 * chess command according to the input string
 */
CHESS_COMMAND getChessCommand (char* token);

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field argument, if it has
 * board positions then they are parsed and saved as source and destination and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   source, destination - board Positions
 *   validArg - is set to true if the command is a legal one and the integer or positions arguments
 *              are valid
 *   argument  - the integer argument in case validArg is set to true
 *   path - path to a file, used for the saved games of the user
 */
ChessCommand parseLine(const char* str);


#endif
