
#include "MainAux.h"


bool undo(ChessGame *game, int mode) {
    if (game == NULL)
        return false;
    if (mode == TWO_PLAYER) {
        printf("Undo command not available in 2 players mode\n");
        return false;
    }
    HistoryNode undoNode;
    CHESS_MESSAGE undoMessage = undoMove(game);
    if (undoMessage == INVALID_ARGUMENT)
        return false;
    if (undoMessage == NO_HISTORY) {
        printf("Empty history, move cannot be undone\n");
        return false;
    }
    undoNode.source = game->history->moves[game->history->actualSize].source;
    undoNode.destination = game->history->moves[game->history->actualSize].destination;
    char *playerColor = getOtherPlayer(game->currentPlayer) == WHITE_PLAYER ? "white" : "black";
    printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n", playerColor, undoNode.destination.row,
           undoNode.destination.column,
           undoNode.source.row, undoNode.source.column);
    changePlayer(game);
    return true;
}

void quit(ChessGame *game) {
    if (game != NULL) {
        printf("Exiting...\n");
        gameDestroy(&game);
    }
}

void resetSession(GameSession *session) {
    if (session != NULL) {
        printf("Restarting...\n");
        gameDestroy(&(session->game));
        free(session);
//        settingsState(session);
    }

}

bool saveGame(char *filePath, ChessGame *game, int mode, int difficulty, int userColor) {
    if (game == NULL)
        return false;
    FILE *saveFile = NULL;
    saveFile = fopen(filePath, "w");
    if (saveFile == NULL) {
        printf("File cannot be created or modified\n");
        return false;
    }
    fprintf(saveFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(saveFile, "<game>\n");
    fprintf(saveFile, "\t<current_turn>%d</current_turn>\n", game->currentPlayer);
    fprintf(saveFile, "\t<game_mode>%d</game_mode> \n", mode);
    if (mode == 1) {
        fprintf(saveFile, "\t<difficulty>%d</difficulty>\n", difficulty);
        fprintf(saveFile, "\t<user_color>%d</user_color>\n", userColor);
    }
    fprintf(saveFile, "\t<board>\n");
    for (int i = GAME_SIZE; i > 0; i--)
        fprintf(saveFile, "\t\t<row_%d>%.8s</row_%d>\n", i, game->gameBoard[i - 1], i);
    fprintf(saveFile, "\t</board>\n");
    fprintf(saveFile, "</game>\n");

    fclose(saveFile);
    return true;

}

bool loadGame(char *filePath, GameSession *gameSession) {// TODO is sscanf problematic?
    FILE *loadedFile = NULL;
    loadedFile = fopen(filePath, "r");
    if (loadedFile == NULL) {
        printf("Error: File doesn’t exist or cannot be opened\n");
        return false;
    }
    char *token = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    gameDestroy(&(gameSession->game));
    gameSession->game = gameCreate(HISTORYSIZE);
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t<current_turn>%d", &(gameSession->game->currentPlayer));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t<game_mode>%d", &(gameSession->mode));
    if (gameSession->mode == ONE_PLAYER) {
        fgets(token, MAX_LINE_LENGTH, loadedFile);
        sscanf(token, "\t<difficulty>%d", &(gameSession->difficulty));
        fgets(token, MAX_LINE_LENGTH, loadedFile);
        sscanf(token, "\t<user_color>%d", &(gameSession->userColor));

    }
    fgets(token, MAX_LINE_LENGTH, loadedFile);

    char currentRow[GAME_SIZE];
    for (int i = GAME_SIZE; i > 0; i--) {
        fgets(token, MAX_LINE_LENGTH, loadedFile);
        sscanf(token, "\t\t<row_%d>%s</row_%d>\n", &i, currentRow, &i);
        for (int j = 0; j < GAME_SIZE; j++)
            gameSession->game->gameBoard[i - 1][j] = currentRow[j];
    }

    return true;
}

bool processCommandSettings(GameSession *session, ChessCommand command) {
    if (session == NULL)
        return false;
    switch (command.cmd) {

        case QUIT:
            if (command.validArg) {
                quit(session->game);
                free(session);
                exit(0);
            }

        case LOAD:
            if (command.validArg) {
                if (loadGame(command.path, session));
                return false;
            }
        case GAME_MODE:
            if (command.validArg) {
                session->mode = command.argument;
                return false;
            }
        case DIFFICULTY:
            if (command.validArg) {
                if (session->mode == ONE_PLAYER) {
                    session->difficulty = command.argument;
                    return false;
                }

            }
        case USER_COLOR:
            if (command.validArg) {
                if (session->mode == ONE_PLAYER) {
                    session->userColor = command.argument;
                    return false;
                }

            }
        case DEFAULT:
            if (command.validArg) {
                session->mode = 1;
                session->difficulty = 2;
                session->userColor = 1;
                return false;
            }
        case PRINT_SETTING:
            if (command.validArg) {
                printf("SETTINGS:\n");
                printf("GAME_MODE: %d\n", session->mode);
                if (session->mode == ONE_PLAYER) {
                    printf("DIFFICULTY_LVL: X\n", session->difficulty);
                    char *playerColor;
                    playerColor = session->game->currentPlayer == WHITE_PLAYER ? "WHITE" : "BLACK";
                    printf("USER_CLR: %s\n", playerColor);
                }
                return false;
            }
        case START:
            if (command.validArg) {
//                gameState(session);
                return true;
            }
        default:
            printf("Invalid Command\n");
            return false;


    }

}

bool processCommandGame(GameSession *session, ChessCommand command) {
    if (session == NULL)
        return false;
    switch (command.cmd) {
        case UNDO_MOVE:
            if (command.validArg) {
                if (session->mode != ONE_PLAYER) {
                    printf("Undo command not available in 2 players mode\n");
                    return false;
                }
                undoMove(session->game);
                undoMove(session->game);
            }
            return false;
        case MOVE:
            if (!command.validArg) {
                printf("Invalid position on the board\n");
                return false;
            }
            if (getPlayer(session->game->gameBoard[GET_ROW(command.source)][GET_COLUMN(command.source)]) !=
                session->game->currentPlayer) {
                printf("The specified position does not contain your piece\n");
                return false;
            }
            if (setMove(session->game, command.source, command.destination) != SUCCESS) {
                printf("Illegal move\n");
                return false;
            }
//            changePlayer(session->game);
            return true;
        case GET_MOVES:
            if (!command.validArg) {
                printf("Invalid position on the board\n");
                return false;
            }
            if (getPlayer(session->game->gameBoard[GET_ROW(command.source)][GET_COLUMN(command.source)]) !=
                session->game->currentPlayer) {
                char *playerColor;
                playerColor = session->game->currentPlayer == WHITE_PLAYER ? "white" : "black";
                printf("The specified position does not contain %s player piece\n", playerColor);
                return false;
            }
            printMoves(session->game, command.source);
            return false;
        case SAVE:
            if (command.validArg) {
                saveGame(command.path, session->game, session->mode, session->difficulty, session->userColor);
                return false;
            }

        case RESET:
            if (command.validArg) {
                resetSession(session);
                return true;//TODO check how to start
            }
        case QUIT:
            if (command.validArg) {
                quit(session->game);
                free(session);
                return true;//TODO check how to exit
//                exit(0);
            }
        default:
            printf("Invalid Command\n");
            return false;
    }
}

GameSession *sessionCreate(int historySize) {
    GameSession *session = (GameSession *) malloc(sizeof(GameSession));
    if (session == NULL) {
        printf(MALLOC_ERROR);
        return NULL;
    }
    session->game = gameCreate(historySize);
    session->difficulty = 2;
    session->mode = ONE_PLAYER;
    session->userColor = WHITE_PLAYER;
    return session;
}

void settingState(GameSession *session) {
    printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
    ChessCommand command;
    session = sessionCreate(HISTORYSIZE);
    char commandLine[MAX_LINE_LENGTH];
    do {
        fgets(commandLine, MAX_LINE_LENGTH, stdin);
        command = parseLine(commandLine);
    } while (!processCommandSettings(session, command));
//    int winner=gameState(session);
}

int gameState(GameSession *session) {
    if (session == NULL)
        return -100;
    char *playerColor;
    bool gameStop = false;
    char commandLine[MAX_LINE_LENGTH];
    ChessCommand command;
    CHESS_MESSAGE msg;
    while (!gameStop) {
        printBoard(session->game);
        playerColor = session->game == WHITE_PLAYER ? "white" : "black";
        do {
            printf("%s player - enter your move:\n", playerColor);
            fgets(commandLine, MAX_LINE_LENGTH, stdin);
            command = parseLine(commandLine);
        } while (!processCommandGame(session, command));
        if (command.cmd == MOVE) //TODO what about reset or quit?
            changePlayer(session->game);
        msg = checkStatus(session->game);
        switch (msg) {
            case MATE:
                printf("Checkmate! %s player wins the game\n",playerColor);
                gameDestroy(session->game);
                free(session);
                exit(0);
            case CHECK:
                printf("Check!\n");
                break;
            case TIE:
                printf("The game ends in a tie\n");
                gameDestroy(session->game);
                free(session);
                exit(0);
            default:
                break;
        }
        if (session->mode == ONE_PLAYER)//computer's turn
        {
            if(session->difficulty==5)
                computerMove(session->game,session->difficulty,true);//TODO maybe change the system of difficulty
            else
                computerMove(session->game,session->difficulty,false);

        }
    }
    return -1;

}

