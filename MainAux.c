
#include "MainAux.h"

bool undo(GameSession *session) {
    if (session->game == NULL)
        return false;
    if (session->mode == TWO_PLAYER) {
        printf("Undo command not available in 2 players mode\n");
        return false;
    }
    moveNode undoNode;
    CHESS_MESSAGE undoMessage = undoMove(session->game);
    if (undoMessage == INVALID_ARGUMENT)
        return false;
    if (undoMessage == NO_HISTORY) {
        printf("Empty history, move cannot be undone\n");
        return false;
    }
    undoNode.source = session->game->history->moves[session->game->history->actualSize].source;
    undoNode.destination = session->game->history->moves[session->game->history->actualSize].destination;
    char *playerColor = getOtherPlayer(session->game->currentPlayer) == WHITE_PLAYER ? "white" : "black";
    printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n", playerColor, undoNode.destination.row,
           undoNode.destination.column,
           undoNode.source.row, undoNode.source.column);
    changePlayer(session->game);
    return true;
}

void quit(ChessGame *game) {
    if (game != NULL) {
        printf("Exiting...\n");
//        gameDestroy(&game);
    }
}

void resetSession(GameSession *session) {
    if (session != NULL) {
        printf("Restarting...\n");
//        gameDestroy(&(session->game));
//        free(session);
//        settingsState(session);
    }

}

bool saveGame(char *filePath,  GameSession *session) { //TODO what about saving the history?
    if (session->game == NULL)
        return false;
    FILE *saveFile = NULL;
    char path[MAX_LINE_LENGTH];
    strcpy(path,filePath);
    saveFile = fopen(path, "w+");
    if (saveFile == NULL) {
        printf("File cannot be created or modified\n");
        return false;
    }
    fprintf(saveFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(saveFile, "<game>\n");
    fprintf(saveFile, "\t<current_turn>%d</current_turn>\n", session->game->currentPlayer);
    fprintf(saveFile, "\t<game_mode>%d</game_mode> \n", session->mode);
    if (session->mode == 1) {
        fprintf(saveFile, "\t<difficulty>%d</difficulty>\n", session->difficulty);
        fprintf(saveFile, "\t<user_color>%d</user_color>\n", session->user_color);
    }
    fprintf(saveFile, "\t<board>\n");
    for (int i = GAME_SIZE; i > 0; i--)
        fprintf(saveFile, "\t\t<row_%d>%.8s</row_%d>\n", i, session->game->gameBoard[i - 1], i);
    fprintf(saveFile, "\t</board>\n");
    fprintf(saveFile, "\t<general>\n");
    fprintf(saveFile, "\t\t<score>%d</score>\n", session->game->score);
    fprintf(saveFile, "\t\t<whiteKingPos>%d,%c</whiteKingPos>\n", session->game->whiteKingPos.row,  session->game->whiteKingPos.column);
    fprintf(saveFile, "\t\t<blackKingPos>%d,%c</blackKingPos>\n", session->game->blackKingPos.row,  session->game->blackKingPos.column);
    fprintf(saveFile, "\t\t<rightWhiteRookMoved>%d</rightWhiteRookMoved>\n", session->game->rightWhiteRookMoved);
    fprintf(saveFile, "\t\t<leftWhiteRookMoved>%d</leftWhiteRookMoved>\n", session->game->leftWhiteRookMoved);
    fprintf(saveFile, "\t\t<rightBlackRookMoved>%d</rightBlackRookMoved>\n", session->game->rightBlackRookMoved);
    fprintf(saveFile, "\t\t<leftBlackRookMoved>%d</leftBlackRookMoved>\n", session->game->leftBlackRookMoved);
    fprintf(saveFile, "\t\t<whiteCastle>%d</whiteCastle>\n", session->game->whiteCastle);
    fprintf(saveFile, "\t\t<blackCastle>%d</blackCastle>\n", session->game->blackCastle);
    fprintf(saveFile, "\t</general>\n");
    fprintf(saveFile, "</game>\n");

    fclose(saveFile);
    return true;

}

bool loadGame(char *filePath, GameSession *session) {
    FILE *loadedFile = NULL;
    char path[MAX_LINE_LENGTH];
    strcpy(path,filePath);
    loadedFile = fopen(path, "r+");
    if (loadedFile == NULL) {
        printf("Error: File doesn’t exist or cannot be opened\n");
        return false;
    }
    char *token = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    if(token==NULL)
    {
        printf("%s",MALLOC_ERROR);
        return false;
    }
    gameDestroy(&(session->game));
    session->game = gameCreate(HISTORYSIZE);
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t<current_turn>%d", &(session->game->currentPlayer));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t<game_mode>%d", &(session->mode));
    if (session->mode == ONE_PLAYER) {
        fgets(token, MAX_LINE_LENGTH, loadedFile);
        sscanf(token, "\t<difficulty>%d", &(session->difficulty));
        fgets(token, MAX_LINE_LENGTH, loadedFile);
        sscanf(token, "\t<user_color>%d", &(session->user_color));

    }
    fgets(token, MAX_LINE_LENGTH, loadedFile);

    char currentRow[GAME_SIZE];
    for (int i = GAME_SIZE; i > 0; i--) {
        fgets(token, MAX_LINE_LENGTH, loadedFile);
        sscanf(token, "\t\t<row_%d>%s</row_%d>\n", &i, currentRow, &i);
        for (int j = 0; j < GAME_SIZE; j++)
            session->game->gameBoard[i - 1][j] = currentRow[j];
    }
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    if (strcmp(token, "</game>\r\n")==0){ // for basic xml files (without our implementation's extra information)
        session->game->whiteKingPos = getKingPos(session->game, WHITE_PLAYER);
        session->game->blackKingPos = getKingPos(session->game, BLACK_PLAYER);
        session->game->score = getScore(session->game);
        fclose(loadedFile);
        return true;
    }
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<score>%d</score>\n", &(session->game->score));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<whiteKingPos>%d,%c</whiteKingPos\n", &(session->game->whiteKingPos.row),&(session->game->whiteKingPos.column));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<blackKingPos>%d,%c</blackKingPos\n", &(session->game->blackKingPos.row),&(session->game->blackKingPos.column));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<rightWhiteRookMoved>%d</rightWhiteRookMoved\n", &(session->game->rightWhiteRookMoved));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<leftWhiteRookMoved>%d</leftWhiteRookMoved\n", &(session->game->leftWhiteRookMoved));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<rightBlackRookMoved>%d</rightBlackRookMoved\n", &(session->game->rightBlackRookMoved));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<leftBlackRookMoved>%d</leftBlackRookMoved\n", &(session->game->leftBlackRookMoved));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<whiteCastle>%d</whiteCastle\n", &(session->game->whiteCastle));
    fgets(token, MAX_LINE_LENGTH, loadedFile);
    sscanf(token, "\t\t<blackCastle>%d</blackCastle\n", &(session->game->blackCastle));

    fclose(loadedFile);
    return true;
}

bool processCommandSettings(GameSession *session, ChessCommand command) {
    if (session == NULL)
        return false;
    switch (command.cmd) {

        case QUIT:
            if (command.validArg) {
                return true;
            }

        case LOAD:
            if (command.validArg) {
                if (loadGame(command.path, session))
                    return false;
            }
        case GAME_MODE:
            if (command.validArg) {
                session->mode = command.argument;
                char *howManyPlayers = command.argument == ONE_PLAYER ? "1 player" : "2 players";
                printf("Game mode is set to %s\n", howManyPlayers);
            } else
                printf("Wrong game mode\n");
            return false;
        case DIFFICULTY:
            if (command.validArg) {
                if (session->mode == ONE_PLAYER) {
                    session->difficulty = command.argument;
                    printf("Difficulty is set to %d\n", command.argument);
                }
            } else if (session->mode == ONE_PLAYER)
                printf("Wrong difficulty level. The value should be between 1 to 5\n");
            else
                printf("Invalid command\n");
            return false;
        case USER_COLOR:
            if (command.validArg && session->mode == ONE_PLAYER) {
                session->user_color = command.argument;
                char *userColor = session->user_color == WHITE_PLAYER ? "white" : "black";
                printf("User color is set to %s\n", userColor);
            } else
                printf("Invalid command\n");
            return false;

        case DEFAULT:
            if (command.validArg) {
                session->mode = ONE_PLAYER;
                session->difficulty = 2;
                session->user_color = WHITE_PLAYER;
                printf("Settings are set to default\n");
                return false;

            }
        case PRINT_SETTING:
            if (command.validArg) {
                printf("SETTINGS:\n");
                printf("GAME_MODE: %d\n", session->mode);
                if (session->mode == ONE_PLAYER) {
                    printf("DIFFICULTY_LVL: %d\n", session->difficulty);
                    char *playerColor;
                    playerColor = session->user_color == WHITE_PLAYER ? "WHITE" : "BLACK";
                    printf("USER_CLR: %s\n", playerColor);
                }
                return false;
            }
        case START:
            if (command.validArg) {
                return true;
            }
        default:
            printf("Invalid command\n");
            return false;


    }

}

bool processCommandGame(GameSession *session, ChessCommand command) {
    if (session == NULL)
        return false;
    char soldier;
    switch (command.cmd) {
        case UNDO_MOVE:
            if (command.validArg) {
                if (undo(session))
                    undo(session);
            }
            printBoard(session->game);
            return false;
        case MOVE:
            if (!command.validArg ) {
                if(command.isNotInFormat) {
                    printf("Invalid command\n");
                    return false;
                }
                printf("Invalid position on the board\n");
                return false;
            }
            if (getPlayer(session->game->gameBoard[GET_ROW(command.source)][GET_COLUMN(command.source)]) !=
                session->game->currentPlayer) {
                printf("The specified position does not contain your piece\n");
                return false;
            }
            if (isCastleMove(session->game,command.source,command.destination)){
                printf("Illegal move\n");
                return false;
            }
            else if (setMove(session->game, command.source, command.destination) != SUCCESS) {
                printf("Illegal move\n");
                return false;
            }
            return true;
        case CASTLE:
            if (!command.validArg) {
                if(command.isNotInFormat)
                {
                    printf("Invalid command\n");
                    return false;
                }
                printf("Wrong position for a rook\n");
                return false;
            }
            soldier = session->game->gameBoard[GET_ROW(command.source)][GET_COLUMN(command.source)];
            char myRook = (char) (session->game->currentPlayer == WHITE_PLAYER ? ROOK_WHITE : ROOK_BLACK);
            if (soldier != myRook) {
                printf("Wrong position for a rook\n");
                return false;
            }
            Position kingPos = session->game->currentPlayer == WHITE_PLAYER ? session->game->whiteKingPos
                                                                            : session->game->blackKingPos;

            if (!isCastleMove(session->game,command.source,kingPos)){
                printf("Illegal castling move\n");
                return false;
            }
            if (setMove(session->game, kingPos, command.source) == SUCCESS)
                return true;
            break;

        case GET_MOVES:
            if (!command.validArg) {
                if(command.isNotInFormat)
                {
                    printf("Invalid command\n");
                    return false;
                }
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
            if(session->difficulty>2){
                printf("Error: Computer level is higher than \"Easy\"\n");
                return false;
            }
            printMoves(session->game, command.source);
            return false;
        case SAVE:
            if (command.validArg) {
                saveGame(command.path, session);
                return false;
            }

        case RESET:
            if (command.validArg) {
                resetSession(session);
                return true;
            }
        case QUIT:
            if (command.validArg) {
                quit(session->game);
                return true;
            }
        default:
            printf("Invalid Command\n");
            return false;
    }
    return false;
}

GameSession sessionCreate(int historySize) {
    GameSession session;
    session.game = gameCreate(historySize);
    session.difficulty = 2;
    session.mode = ONE_PLAYER;
    session.user_color=WHITE_PLAYER;
    return session;
}

int settingState(GameSession *session) {
    printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
    ChessCommand command;
    (*session) = sessionCreate(HISTORYSIZE);
    char commandLine[MAX_LINE_LENGTH];
    do {
        fgets(commandLine, MAX_LINE_LENGTH, stdin);
        command = parseLine(commandLine);
    } while (!processCommandSettings(session, command));
    if (command.cmd == QUIT) {
        quit(session->game);
        return 0;
    }
    return 1; // gameState
}

void gameStatus(CHESS_MESSAGE msg, GameSession *session) {
    char *playerColor;
    playerColor = session->game->currentPlayer== WHITE_PLAYER ? "black" : "white"; // the opposite player
    char *threatenColor = strcmp(playerColor, "white")==0 ? "black" : "white";
    switch (msg) {
        case MATE:
            printf("Checkmate! %s player wins the game\n", playerColor);
            return;
        case CHECK:
            if (session->user_color==session->game->currentPlayer)
                printf("Check!\n");
            else
                printf("Check: %s King is threatened!\n", threatenColor);
            return;
        case TIE:
            if (session->user_color==session->game->currentPlayer)
                printf("The game ends in a tie\n");
            else
                printf("The game is tied\n");
            return;
        default:
            break;
    }
    return;
}

CHESS_MESSAGE gameState(GameSession *session) {
    if (session == NULL)
        return INVALID_ARGUMENT;
    bool gameStop = false;
    char commandLine[MAX_LINE_LENGTH];
    ChessCommand command;
    CHESS_MESSAGE msg = INVALID_ARGUMENT;
    char *playerColor;

    while (!gameStop) {
        if ( session->mode == TWO_PLAYER ||session->user_color == session->game->currentPlayer )  {
            printBoard(session->game);
            do {
                playerColor = session->game->currentPlayer == WHITE_PLAYER ? "white" : "black";
                printf("%s player - enter your move:\n", playerColor);
                fgets(commandLine, MAX_LINE_LENGTH, stdin);
                command = parseLine(commandLine);
            } while (!processCommandGame(session, command));
            if (command.cmd == MOVE || command.cmd == CASTLE)
                changePlayer(session->game);
            else if (command.cmd == RESET)
                return RESET_GAME;
            else if (command.cmd == QUIT)
                return EXIT_GAME;
            msg = checkStatus(session->game);
            gameStatus(msg, session);
            if (msg == TIE || msg == MATE)
                return msg;
        }
        if (session->mode == ONE_PLAYER)//computer's turn
        {
            moveNode move = bestMove(session->game, session->difficulty, session->difficulty == 5);
            Position *positions = isCastling(move);
            setMove(session->game, move.source, move.destination);
            if (positions[0].row == INVALID_ROW) {
                char *computerSoldier = getSoldierName(
                        session->game->gameBoard[GET_ROW(move.destination)][GET_COLUMN(move.destination)]);
                printf("Computer: move %s at <%d,%c> to <%d,%c>\n", computerSoldier, move.source.row,
                       move.source.column, move.destination.row, move.destination.column);
            } else {
                Position kingPos = session->game->currentPlayer == WHITE_PLAYER ? session->game->whiteKingPos
                                                                                : session->game->blackKingPos;
                Position rookPosition;
                rookPosition.row = session->game->currentPlayer == WHITE_PLAYER ? WHITE_INITIAL_ROW : BLACK_INITIAL_ROW;
                rookPosition.column = (char) (kingPos.column == 'C' ? 'D' : 'F');
                printf("Computer: castle King at <%d,%c> and Rook at <%d,%c>\n", kingPos.row, kingPos.column,
                       rookPosition.row, rookPosition.column);
            }
            free(positions);
            changePlayer(session->game);
            msg = checkStatus(session->game);
            gameStatus(msg, session);
            if (msg == TIE || msg == MATE)
                gameStop = true;
        }
    }
    return msg;
}
