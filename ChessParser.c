
#include <stdio.h>
#include "ChessParser.h"


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

bool isInFormat(char *token) {
    char *pointer = token;
    if (token == '\0')
        return false;
    if (pointer[0] != '<')
        return false;
    int i = 1;
    if (pointer[i] == '-')
        i++;
    if ((pointer[i] < '0' || pointer[i] > '9'))
        return false;
    while (pointer[i] >= '0' && pointer[i] <= '9')
        i++;
    if (pointer[i] != ',')
        return false;
    i++;
    if (pointer[i] < 'A' || pointer[i] > 'Z')
        return false;
    i++;
    if (pointer[i] != '>')
        return false;
    i++;
    return pointer[i] == '\0';
}

Position getPosition(char *token) {
    Position res;
    res.column = INVALID_COL;
    res.row = INVALID_ROW;
    if (token == NULL || strlen(token) != 5)
        return res;
//    char test = token[3];
    if (token[0] == '<' && token[4] == '>') {
        if ((token[1] >= '1') && (token[1] <= '8')) {

            if (token[2] == 44) {
                if ((token[3] >= 'A') && (token[3] <= 'H')) {
                    res.column = token[3];
                    res.row = token[1] - '0';
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
        return RESET;
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
    if (strcmp(token, "castle") == 0) {
        return CASTLE;
    }

    return INVALID_LINE;

}


ChessCommand parseLine(const char *str) {
    char str2[MAX_LINE_LENGTH];
    strcpy(str2, str);
    char *token = strtok(str2, DELIMITER);
    ChessCommand result;
    result.cmd = getChessCommand(token);
    result.validArg = false;
    token = strtok(NULL, DELIMITER);

    if (token == '\0') {
        if ((result.cmd == QUIT) || (result.cmd == DEFAULT) ||
            (result.cmd == START) || (result.cmd == PRINT_SETTING) || (result.cmd == UNDO_MOVE) ||
            (result.cmd == RESET)) {
            result.validArg = true;
        } else {
            result.validArg = false;
        }
    } else if (isInt(token)) {
        int tokenInt = atoi(token);
        if ((result.cmd == DIFFICULTY) && (1 <= tokenInt && tokenInt <= 5)) {
            result.validArg = true;
            result.argument = tokenInt;
        } else if (result.cmd == GAME_MODE && (tokenInt == 1 || tokenInt == 2)) {
            result.argument = tokenInt;
            result.validArg = true;
        } else if (result.cmd == USER_COLOR && (tokenInt == 0 || tokenInt == 1)) {
            result.argument = tokenInt;
            result.validArg = true;
        }
    } else if ((result.cmd == SAVE) || (result.cmd == LOAD)) {
        result.validArg = true;
        result.path = token;
    } else if (result.cmd == INVALID_LINE) {
        result.validArg = false;
    } else if (result.cmd == GET_MOVES || result.cmd == CASTLE) {
        result.isNotInFormat = false;
        if (!isInFormat(token)) {
            result.isNotInFormat = true;
            result.validArg = false;
        } else {
            Position pos = getPosition(token);
            if (pos.row == INVALID_ROW) //don't need to check INVALID_COL
                result.validArg = false;
            else {
                result.source = pos;
                result.validArg = true;

            }
        }
    } else if (result.cmd == MOVE) {
        result.isNotInFormat = false;
        if (!isInFormat(token)) {
            result.isNotInFormat = true;
            result.validArg = false;
        } else {
            Position source = getPosition(token);
            token = strtok(NULL, DELIMITER);
            if (token == '\0'){
                result.isNotInFormat = true;
                result.validArg = false;
            }
            else if (strcmp(token, "to") != 0) {
                result.isNotInFormat = true;
                result.validArg = false;
            } else {
                token = strtok(NULL, DELIMITER);
                if (!isInFormat(token)) {
                    result.isNotInFormat = true;
                    result.validArg = false;
                } else {
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
        }
    }
    return result;
}
