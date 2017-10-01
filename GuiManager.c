#include "GuiManager.h"


GuiManager *ManagerCreate() {
    GuiManager *res = (GuiManager *) malloc(sizeof(GuiManager));
    if (res == NULL) {
        return NULL;
    }
    res->mainWin = mainWindowCreate();
    if (res->mainWin == NULL) {
        free(res);
        return NULL;
    }
    res->loadGameWin = NULL;
    res->settingsWin = NULL;
    res->gameWin = NULL;
    res->activeWin = MAIN_WINDOW_ACTIVE;
    return res;
}

void ManagerDestroy(GuiManager *src) {
    if (!src)
        return;
    if (src->activeWin == MAIN_WINDOW_ACTIVE) {
        mainWindowDestroy(src->mainWin);
        src->mainWin = NULL;
    }
    if (src->activeWin == SETTINGS_WINDOW_ACTIVE) {
        settingsWindowDestroy(src->settingsWin);
        src->settingsWin = NULL;
    }
    if (src->activeWin == LOAD_GAME_WINDOW_ACTIVE) {
        loadGameWindowDestroy(src->loadGameWin);
        src->loadGameWin = NULL;
    }
    if (src->activeWin == GAME_WINDOW_ACTIVE) {
        gameWindowDestroy(src->gameWin);
        src->gameWin = NULL;
    }
    free(src);
}

void ManagerDraw(GuiManager *manager, GameSession *session) {
    if (!manager) {
        return;
    }
    if (manager->activeWin == MAIN_WINDOW_ACTIVE) {
        if (manager->mainWin == NULL)
            manager->mainWin = mainWindowCreate();
        mainWindowDraw(manager->mainWin);
    } else if (manager->activeWin == SETTINGS_WINDOW_ACTIVE) {
        if (manager->settingsWin == NULL)
            manager->settingsWin = settingsWindowCreate();
        settingsWindowDraw(manager->settingsWin);
    } else if (manager->activeWin == LOAD_GAME_WINDOW_ACTIVE) {
        if (manager->loadGameWin == NULL)
            manager->loadGameWin = loadGameWindowCreate();
        loadGameWindowDraw(manager->loadGameWin);
    } else if (manager->activeWin == GAME_WINDOW_ACTIVE) {
        if (manager->gameWin == NULL)
            manager->gameWin = gameWindowCreate(manager->gameWin->isSaved);
        gameWindowDraw(manager->gameWin, session);
    }
}

MANAGER_EVENT handleManagerDueToMainEvent(GameSession *session, GuiManager *src, MAIN_EVENT event) {
    if (src == NULL) {
        return MANAGER_NONE;
    }
    if (event == MAIN_NEW_GAME) {
        (*session) = sessionCreate(HISTORYSIZE);
        mainWindowDestroy(src->mainWin);
        src->mainWin = NULL;
        src->settingsWin = settingsWindowCreate();
        if (src->settingsWin == NULL) {
            printf("Couldn't move to settings window\n");
            return MANAGER_QUIT;
        }
        src->activeWin = SETTINGS_WINDOW_ACTIVE;
    }
    if (event == MAIN_LOAD_GAME) {
        (*session) = sessionCreate(HISTORYSIZE);
        mainWindowDestroy(src->mainWin);
        src->mainWin = NULL;
        src->loadGameWin = loadGameWindowCreate();
        src->loadGameWin->fromMainMenu = 1;//TODO do this also in gameWindow with false parameter
        if (src->loadGameWin == NULL) {
            printf("Couldn't move to settings window\n");
            return MANAGER_QUIT;
        }
        src->activeWin = LOAD_GAME_WINDOW_ACTIVE;
    }
    if (event == MAIN_QUIT) {
        return MANAGER_QUIT;
    }
    return MANAGER_NONE;
}
//This function handles the events sent by the user when the active window is the Settings window

MANAGER_EVENT handleManagerDueToSettingsEvent(GameSession *session, GuiManager *src, SETTINGS_EVENT event) {
    if (src == NULL) {
        return MANAGER_NONE;
    }
    if (event == SETTINGS_BACK) {
        gameDestroy(&(session->game));
        settingsWindowDestroy(src->settingsWin);
        src->settingsWin = NULL;
        src->mainWin = mainWindowCreate();
        src->activeWin = MAIN_WINDOW_ACTIVE;
    }
    if (event == SETTINGS_START) {
        settingsWindowDestroy(src->settingsWin);
        src->settingsWin = NULL;
        src->gameWin = gameWindowCreate( 0);
        if (src->gameWin == NULL) {
            printf("ERROR: Couldn't move to game window\n");
            return MANAGER_QUIT;
        }
        src->activeWin = GAME_WINDOW_ACTIVE;
        if (session->user_color == 0) {// The computer starts
            moveNode move = bestMove(session->game, session->difficulty, session->difficulty == 5);
            setMove(session->game, move.source, move.destination);
            changePlayer(session->game);
        }
    }
    if (event == SETTINGS_1PLAYER) {
        session->mode = ONE_PLAYER;
        src->settingsWin->is1player = true;
    }
    if (event == SETTINGS_2PLAYER) {
        session->mode = TWO_PLAYER;
        src->settingsWin->is1player = false;
    }
    if (event == SETTINGS_1DIFF) {
        session->difficulty = 1;
        src->settingsWin->diff = 1;
    }
    if (event == SETTINGS_2DIFF) {
        session->difficulty = 2;
        src->settingsWin->diff = 2;
    }
    if (event == SETTINGS_3DIFF) {
        session->difficulty = 3;
        src->settingsWin->diff = 3;
    }
    if (event == SETTINGS_4DIFF) {
        session->difficulty = 4;
        src->settingsWin->diff = 4;
    }
    if (event == SETTINGS_5DIFF) {
        session->difficulty = 5;
        src->settingsWin->diff = 5;
    }
    if (event == SETTINGS_USERCOLOR_0) {
        session->user_color = BLACK_PLAYER;
        src->settingsWin->user_color = 0;
    }
    if (event == SETTINGS_USERCOLOR_1) {
        session->user_color = WHITE_PLAYER;
        src->settingsWin->user_color = 1;
    }
    if (event == SETTINGS_QUIT) {
        gameDestroy(&(session->game));
        return MANAGER_QUIT;
    }

    return MANAGER_NONE;
}

//This function handles the events sent by the user when the active window is the Load window
MANAGER_EVENT handleManagerDueToLoadEvent(GameSession *session, GuiManager *src, LOAD_EVENT event) {
    if (event == LOAD_BACK) {
        if (src->loadGameWin->fromMainMenu == 1) {
            gameDestroy(&(session->game));
            loadGameWindowDestroy(src->loadGameWin);
            src->loadGameWin = NULL;
            src->mainWin = mainWindowCreate();
            src->activeWin = MAIN_WINDOW_ACTIVE;
        } else {
            int isSaved = src->loadGameWin->isCurrentGameSaved;
            loadGameWindowDestroy(src->loadGameWin);
            src->loadGameWin = NULL;
            src->gameWin = gameWindowCreate( isSaved);
            src->activeWin = GAME_WINDOW_ACTIVE;
        }
    }
    if (event == LOAD_1SLOT) {
        src->loadGameWin->chosenSlot = 1;

    }
    if (event == LOAD_2SLOT) {
        src->loadGameWin->chosenSlot = 2;
    }
    if (event == LOAD_3SLOT) {
        src->loadGameWin->chosenSlot = 3;
    }
    if (event == LOAD_4SLOT) {
        src->loadGameWin->chosenSlot = 4;
    }
    if (event == LOAD_5SLOT) {
        src->loadGameWin->chosenSlot = 5;
    }
    if (event == LOAD_START) {
        char path[6];
        sprintf(path, "%d.xml", (src->loadGameWin->availableSlots - src->loadGameWin->chosenSlot + 1));
        loadGame(path, session);
        loadGameWindowDestroy(src->loadGameWin);
        src->loadGameWin = NULL;
        src->gameWin = gameWindowCreate(0);
        if (src->gameWin == NULL) {
            printf("ERROR: Couldn't move to game window\n");
            return MANAGER_QUIT;
        }
        src->activeWin = GAME_WINDOW_ACTIVE;
    }
    if (event == LOAD_QUIT) {
        gameDestroy(&(session->game));
        return MANAGER_QUIT;
    }
    return MANAGER_NONE;
}
//This function performs the save function during GUI mode
bool saveFromGameWindow(GameSession *session) {
    FILE *numOfSlots = NULL;
    numOfSlots = fopen("numOfSlots.xml", "r+");
    int validSlots;
    char *filePath = (char *) malloc(sizeof(char) * 6);
    char *token = (char *) malloc(MAX_LINE_LENGTH * sizeof(char));
    if (token == NULL) {
        printf("%s", MALLOC_ERROR);
        return false;
    }
    fgets(token, MAX_LINE_LENGTH, numOfSlots);
    fscanf(numOfSlots, "<validSlots>%d", &validSlots);
    if (validSlots < MAX_NUM_OF_SLOTS) {
        sprintf(filePath, "%d.xml", validSlots + 1);
    } else {
        char *secondPath = (char *) malloc(sizeof(char) * 6);
        for (int i = 1; i < MAX_NUM_OF_SLOTS; i++) {
            sprintf(filePath, "%d.xml", i + 1);
            sprintf(secondPath, "%d.xml", i);
            rename(filePath, secondPath);
        }
        sprintf(filePath, "%d.xml", MAX_NUM_OF_SLOTS);
        free(secondPath);
    }
    saveGame(filePath, session);
    FILE *newSlotsFile = NULL;
    newSlotsFile = fopen("newSlotsFile.xml", "w+");
    fprintf(newSlotsFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(newSlotsFile, "<validSlots>%d</validSlots>",
            validSlots == MAX_NUM_OF_SLOTS ? MAX_NUM_OF_SLOTS : validSlots + 1);
    fclose(newSlotsFile);
    rename("newSlotsFile.xml", "numOfSlots.xml");
    free(filePath);
    free(token);

    fclose(numOfSlots);
    return true;
}
//This function sends the Massage box, when the user wants to quit or go to main menu without saving first
int askWhetherToSave(GameSession *session, gameWin *src) {
    const SDL_MessageBoxButtonData buttons[] = {
            {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes"},
            {0,                                       1, "No"},
            {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel"},
    };
    const SDL_MessageBoxColorScheme colorScheme = {
            {
                    /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
                    {192, 192, 192},
                    /* [SDL_MESSAGEBOX_COLOR_TEXT] */
                    {0, 0, 0},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
                    {0, 0, 0},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
                    {192, 192, 192},
                    /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
                    {90, 139, 199}
            }
    };
    const SDL_MessageBoxData messageBoxData = {
            SDL_MESSAGEBOX_INFORMATION,
            NULL,
            "You are about to quit the game", /* .title */
            "Do you want to save the current game?", /* .message */
            SDL_arraysize(buttons), /* .numOfButtons */
            buttons, /* .buttons */
            &colorScheme /* .colorScheme */
    };
    int buttonID;
    if (SDL_ShowMessageBox(&messageBoxData, &buttonID) < 0) {
        SDL_Log("Error displaying message box");
        return 0;
    }
    switch (buttonID) {
        case 0:
            if (saveFromGameWindow(session))
                src->isSaved = true;

            return 1;
        case 1:
            return 1;
        case 2:
            return 0;
        default:
            break;
    }
    return 0;
}

//This function handles the events sent by the user when the active window is the Game window
MANAGER_EVENT handleManagerDueToGameEvent(GameSession *session, GuiManager *src, GAME_EVENT event) {
    if (event == GAME_LOAD) {
        int isSaved = src->gameWin->isSaved;
        gameWindowDestroy(src->gameWin);
        src->gameWin = NULL;
        src->loadGameWin = loadGameWindowCreate();
        src->loadGameWin->fromMainMenu = 0;
        src->loadGameWin->isCurrentGameSaved = isSaved;
        src->activeWin = LOAD_GAME_WINDOW_ACTIVE;
    }
    if (event == GAME_UNDO) {
        if (undoMove(session->game) == SUCCESS)
            undoMove(session->game);
        src->gameWin->isSaved = false;
    }
    if (event == GAME_SAVE) {
        if (saveFromGameWindow(session))
            src->gameWin->isSaved = true;
    }
    if (event == GAME_MAINMENU_SAVED) {
        gameDestroy(&(session->game));
        (*session) = sessionCreate(HISTORYSIZE);
        gameWindowDestroy(src->gameWin);
        src->gameWin = NULL;
        src->mainWin = mainWindowCreate();
        src->activeWin = MAIN_WINDOW_ACTIVE;
    }
    if (event == GAME_MAINMENU_UNSAVED) {
        if (askWhetherToSave(session, src->gameWin)) {
            gameDestroy(&(session->game));
            (*session) = sessionCreate(HISTORYSIZE);
            gameWindowDestroy(src->gameWin);
            src->gameWin = NULL;
            src->mainWin = mainWindowCreate();
            src->activeWin = MAIN_WINDOW_ACTIVE;
        }
    }
    if (event == GAME_RESTART) {
        gameDestroy(&(session->game));
        session->game = gameCreate(HISTORYSIZE);
        src->gameWin->isSaved = false;
        if (session->user_color == 0) {// The computer starts
            moveNode move = bestMove(session->game, session->difficulty, session->difficulty == 5);
            setMove(session->game, move.source, move.destination);
            changePlayer(session->game);
        }
    }
    if (event == GAME_QUIT_UNSAVED) {
        if (askWhetherToSave(session, src->gameWin)) {
            gameDestroy((&(session->game)));
            return MANAGER_QUIT;
        }
    }
    if (event == GAME_QUIT_SAVED) {
        gameDestroy((&(session->game)));
        return MANAGER_QUIT;
    }
    if (event == GAME_MOVE) {
        if (setMove(session->game, src->gameWin->moveSrc, src->gameWin->moveDest) == SUCCESS) {
            changePlayer(session->game);
            CHESS_MESSAGE msg = checkStatus(session->game);
            if (msg == TIE) {
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tie",
                                         "The game is tied!", src->gameWin->window);
                return MANAGER_QUIT;
            }
            if (msg == MATE) {
                char *playerColor;
                playerColor = session->game->currentPlayer == WHITE_PLAYER ? "Black" : "White";
                char message[MAX_LINE_LENGTH];
                sprintf(message, "Checkmate! %s player wins the game", playerColor);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Mate",
                                         message, src->gameWin->window);
                return MANAGER_QUIT;
            }
            if (msg == CHECK) {
                char *playerColor;
                playerColor = session->game->currentPlayer == WHITE_PLAYER ? "White" : "Black";
                char message[MAX_LINE_LENGTH];
                sprintf(message, "Check: %s King is threatened!", playerColor);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check",
                                         message, src->gameWin->window);

            }

            if (session->mode == ONE_PLAYER) {
                moveNode move = bestMove(session->game, session->difficulty, session->difficulty == 5);
                setMove(session->game, move.source, move.destination);
                changePlayer(session->game);
                CHESS_MESSAGE msg = checkStatus(session->game);
                if (msg == TIE) {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Tie",
                                             "The game is tied!", src->gameWin->window);
                    return MANAGER_QUIT;
                }
                if (msg == MATE) {
                    char *playerColor;
                    playerColor = session->game->currentPlayer == WHITE_PLAYER ? "Black" : "White";
                    char message[MAX_LINE_LENGTH];
                    sprintf(message, "Checkmate! %s player wins the game", playerColor);
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Mate",
                                             message, src->gameWin->window);
                    return MANAGER_QUIT;
                }
                if (msg == CHECK) {

                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Check",
                                             "Check!", src->gameWin->window);
                }
            }
        }
    }
    return MANAGER_NONE;
}

MANAGER_EVENT ManagerHandleEvent(GameSession *session, GuiManager *src, SDL_Event *event) {
    if (src == NULL || event == NULL) {
        return MANAGER_NONE;
    }
    if (src->activeWin == MAIN_WINDOW_ACTIVE) {
        MAIN_EVENT mainEvent = mainWindowHandleEvent(event);
        return handleManagerDueToMainEvent(session, src, mainEvent);
    }
    if (src->activeWin == SETTINGS_WINDOW_ACTIVE) {
        SETTINGS_EVENT settingsEvent = settingsWindowHandleEvent(src->settingsWin, event);
        return handleManagerDueToSettingsEvent(session, src, settingsEvent);
    }
    if (src->activeWin == LOAD_GAME_WINDOW_ACTIVE) {
        LOAD_EVENT loadEvent = loadGameWindowHandleEvent(src->loadGameWin, event);
        return handleManagerDueToLoadEvent(session, src, loadEvent);
    }
    if (src->activeWin == GAME_WINDOW_ACTIVE) {
        GAME_EVENT gameEvent = gameWindowHandleEvent(session, src->gameWin, event);
        return handleManagerDueToGameEvent(session, src, gameEvent);
    }
    return MANAGER_NONE;
}
