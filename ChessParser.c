#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ChessParser.h"

#define MAX_LINE_LENGTH 1024
#define DELIMITER " \t\r\n"
#define INVALID_ROW 100
#define INVALID_COL '\0'


bool isInt(const char *str) {
    if (str[0] != 45 && (str[0] < 48 || str[0] > 57))
        return false;
    if (str[0] == 45 && str[1] == '\0')
        return false;

    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] < 48 || str[i] > 57) {
            return false;
        }
    }
    return true;
}

Position getPosition(char *token) {
    Position res;
    res.column = INVALID_COL;
    res.row = INVALID_ROW;
    if (token == NULL || strlen(token) != 5)
        return res;
    if (token[0] == '<' && token[4] == '>') {
        if ((token[1] > 64) && (token[1] < 73)) {

            if (token[2] == 44) {
                if ((token[3] > 48) && (token[3] < 57)) {
                    res.column = token[1];
                    res.row = token[3] - 48;
                }
            }
        }
    }
    return res;


}

CHESS_COMMAND getChessCommand(char *token) {
    if (strcmp(token, "undo") == 0) {
        return UNDO_MOVE;
    }
    if (strcmp(token, "move") == 0) {
        return MOVE;

    }
    if (strcmp(token, "get_moves") == 0) {
        return GET_MOVES;
    }
    if (strcmp(token, "quit") == 0) {
        return QUIT;
    }
    if (strcmp(token, "reset") == 0) {
        return RESTART;
    }
    if (strcmp(token, "save") == 0) {
        return SAVE;
    }
    if (strcmp(token, "load") == 0) {
        return LOAD;
    }
    if (strcmp(token, "game_mode") == 0) {
        return GAME_MODE;
    }
    if (strcmp(token, "difficulty") == 0) {
        return DIFFICULTY;
    }
    if (strcmp(token, "user_color") == 0) {
        return USER_COLOR;
    }
    if (strcmp(token, "default") == 0) {
        return DEFAULT;
    }
    if (strcmp(token, "print_setting") == 0) {
        return PRINT_SETTING;
    }
    if (strcmp(token, "start") == 0) {
        return START;
    }

    return INVALID_LINE;

}


ChessCommand parseLine(const char *str) {
    char str2[MAX_LINE_LENGTH];
    strcpy(str2, str);
    char *token = strtok(str2, DELIMITER);
    ChessCommand result;
    result.cmd = getChessCommand(token);
    token = strtok(NULL, DELIMITER);

    if (token == '\0') {
        if ((result.cmd == QUIT) || (result.cmd == DEFAULT) ||
            (result.cmd == START) || (result.cmd == PRINT_SETTING) || (result.cmd == UNDO_MOVE) ||
            (result.cmd == RESTART)) {
            result.validArg = true;
        } else {
            result.validArg = false;
        }
    } else if (isInt(token)) {
        if ((result.cmd == DIFFICULTY) || (result.cmd == GAME_MODE) || (result.cmd == USER_COLOR)) {
            result.validArg = true;
        }
    } else if ((result.cmd == SAVE) || (result.cmd == LOAD)) {
        result.validArg = true;
        result.path = token;
    } else if (result.cmd == INVALID_LINE) {
        result.validArg = false;
    } else if (result.cmd == GET_MOVES) {
        Position pos = getPosition(token);
        if (pos.row==INVALID_ROW) //don't need to check INVALID_COL
            result.validArg = false;
        else{
            result.source = pos;
            result.validArg = true;

        }
    }
    else //result.cmd==MOVE
    {
        Position source = getPosition(token);
        token=strtok(NULL,DELIMITER);
        if (strcmp(token, "to") != 0)
            result.validArg =false;
        else {
            token = strtok(NULL, DELIMITER);
            Position destination = getPosition(token);

            if (source.row == INVALID_ROW || destination.row == INVALID_ROW) //don't need to check INVALID_COL
                result.validArg = false;
            else {
                result.source = source;
                result.destination = destination;
                result.validArg = true;
            }
        }
    }
    return result;
}
