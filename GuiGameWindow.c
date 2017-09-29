#include "GuiGameWindow.h"


bool loadImageGameWindow(char *path, gameWin *src, SDL_Texture **texture) {
    SDL_Surface *loadingSurface = NULL;
    loadingSurface = SDL_LoadBMP(path);
    if (loadingSurface == NULL) {
        gameWindowDestroy(src);
        printf("Couldn't create surface\n");
        return false;
    }
    (*texture) = SDL_CreateTextureFromSurface(src->gameRenderer, loadingSurface);
    if ((*texture) == NULL) {
        SDL_FreeSurface(loadingSurface);
        gameWindowDestroy(src);
        printf("Couldn't create texture\n");
        return false;
    }
    SDL_FreeSurface(loadingSurface);
    return true;
}

int isClickedOnUndo(int x, int y, GameSession *session) {
    if (session == NULL)
        return 0;
    if (session->game->history->actualSize > 0) {
        if ((x >= 550 && x <= 651) && (y >= GAMEBOARD_Y + 10 && y <= GAMEBOARD_Y + 63)) {
            return 1;
        }
    }
    return 0;
}

int isClickedOnRestartGame(int x, int y) {
    if ((x >= 550 && x <= 723) && (y >= GAMEBOARD_Y + 90 && y <= GAMEBOARD_Y + 143)) {
        return 1;
    }
    return 0;
}

int isClickedOnSaveGame(int x, int y) {
    if ((x >= 550 && x <= 701) && (y >= GAMEBOARD_Y + 170 && y <= GAMEBOARD_Y + 223)) {
        return 1;
    }

    return 0;
}

int isClickedOnLoadGame(int x, int y) {
    if ((x >= 550 && x <= 705) && (y >= GAMEBOARD_Y + 250 && y <= GAMEBOARD_Y + 283)) {
        return 1;
    }
    return 0;
}

int isClickedOnMainMenu(int x, int y) {
    if ((x >= 550 && x <= 705) && (y >= GAMEBOARD_Y + 330 && y <= GAMEBOARD_Y + 383)) {
        return 1;
    }
    return 0;
}

int isClickedOnQuitGame(int x, int y) {
    if ((x >= 550 && x <= 643) && (y >= GAMEBOARD_Y + 410 && y <= GAMEBOARD_Y + 463)) {
        return 1;
    }
    return 0;
}

gameWin *gameWindowCreate(GameSession *session, int isAlreadySaved) {
    gameWin *res = NULL;
    res = (gameWin *) malloc(sizeof(gameWin));
    if (res == NULL) {
        printf("%s", MALLOC_ERROR);
        return NULL;
    }

    // Create an application window with the following settings:
    res->window = SDL_CreateWindow("Blood and Honor", // window title
                                   SDL_WINDOWPOS_CENTERED,           // initial x position
                                   SDL_WINDOWPOS_CENTERED,           // initial y position
                                   GAME_WIDTH,                               //
                                   GAME_HEIGHT,                               //
                                   SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (res->window == NULL) {
        gameWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    res->gameRenderer = SDL_CreateRenderer(res->window, -1,
                                           SDL_RENDERER_ACCELERATED);
    if (res->gameRenderer == NULL) {
        // In the case that the window could not be made...
        gameWindowDestroy(res);
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    res->movesGrid = (SDL_Texture **) calloc(GAME_SIZE * GAME_SIZE, sizeof(SDL_Texture *));
    res->movingRect.w = TILE_SIZE;
    res->movingRect.h = TILE_SIZE;
    if (!loadImageGameWindow("../images/board.bmp", res, &(res->gameBoardTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whitePawn.bmp", res, &(res->pawnWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackPawn.bmp", res, &(res->pawnBlackTexture)))//
        return NULL;
    if (!loadImageGameWindow("../images/whiteBishop.bmp", res, &(res->bishopWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackBishop.bmp", res, &(res->bishopBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whiteKnight.bmp", res, &(res->knightWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackKnight.bmp", res, &(res->knightBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whiteRook.bmp", res, &(res->rookWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackRook.bmp", res, &(res->rookBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whiteQueen.bmp", res, &(res->queenWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackQueen.bmp", res, &(res->queenBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/whiteKing.bmp", res, &(res->kingWhiteTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/blackKing.bmp", res, &(res->kingBlackTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/gameUndo.bmp", res, &(res->undoTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/gameUndoFade.bmp", res, &(res->undoFadeTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/gameRestart.bmp", res, &(res->restartTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/gameSave.bmp", res, &(res->saveTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/gameSaveFade.bmp", res, &(res->saveFadeTexture)))
        return NULL;

    if (!loadImageGameWindow("../images/gameLoad.bmp", res, &(res->loadTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/gameMenu.bmp", res, &(res->mainMenuTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/gameQuit.bmp", res, &(res->quitTexture)))
        return NULL;
    if (!loadImageGameWindow("../images/yellow.bmp", res, &(res->yellow)))
        return NULL;

    if (!loadImageGameWindow("../images/red.bmp", res, &(res->red)))
        return NULL;
    if (!loadImageGameWindow("../images/green.bmp", res, &(res->green)))
        return NULL;
    if (!loadImageGameWindow("../images/purple.bmp", res, &(res->purple)))
        return NULL;
    res->isSaved = isAlreadySaved;
    res->getMovesShowing = 0;
    return res;
}

void gameWindowDestroy(gameWin *src) {
    if (!src) {
        return;
    }
    if (src->gameBoardTexture != NULL) {
        SDL_DestroyTexture(src->gameBoardTexture);
    }
    if (src->pawnWhiteTexture != NULL) {
        SDL_DestroyTexture(src->pawnWhiteTexture);
    }
    if (src->pawnBlackTexture != NULL) {
        SDL_DestroyTexture(src->pawnBlackTexture);
    }
    if (src->knightWhiteTexture != NULL) {
        SDL_DestroyTexture(src->knightWhiteTexture);
    }
    if (src->knightBlackTexture != NULL) {
        SDL_DestroyTexture(src->knightBlackTexture);
    }
    if (src->bishopWhiteTexture != NULL) {
        SDL_DestroyTexture(src->bishopWhiteTexture);
    }
    if (src->bishopBlackTexture != NULL) {
        SDL_DestroyTexture(src->bishopBlackTexture);
    }
    if (src->rookWhiteTexture != NULL) {
        SDL_DestroyTexture(src->rookWhiteTexture);
    }
    if (src->rookBlackTexture != NULL) {
        SDL_DestroyTexture(src->rookBlackTexture);
    }
    if (src->queenWhiteTexture != NULL) {
        SDL_DestroyTexture(src->queenWhiteTexture);
    }
    if (src->queenBlackTexture != NULL) {
        SDL_DestroyTexture(src->queenBlackTexture);
    }
    if (src->kingWhiteTexture != NULL) {
        SDL_DestroyTexture(src->kingWhiteTexture);
    }
    if (src->kingBlackTexture != NULL) {
        SDL_DestroyTexture(src->kingBlackTexture);
    }
    if (src->undoTexture != NULL) {
        SDL_DestroyTexture(src->undoTexture);
    }
    if (src->undoFadeTexture != NULL) {
        SDL_DestroyTexture(src->undoFadeTexture);
    }
    if (src->restartTexture != NULL) {
        SDL_DestroyTexture(src->restartTexture);
    }
    if (src->saveTexture != NULL) {
        SDL_DestroyTexture(src->saveTexture);
    }
    if (src->yellow != NULL) {
        SDL_DestroyTexture(src->yellow);
    }
    if (src->red != NULL) {
        SDL_DestroyTexture(src->red);
    }
    if (src->green != NULL) {
        SDL_DestroyTexture(src->green);
    }
    if (src->purple != NULL) {
        SDL_DestroyTexture(src->purple);
    }
    if (src->saveFadeTexture != NULL) {
        SDL_DestroyTexture(src->saveFadeTexture);
    }
    if (src->loadTexture != NULL) {
        SDL_DestroyTexture(src->loadTexture);
    }
    if (src->mainMenuTexture != NULL) {
        SDL_DestroyTexture(src->mainMenuTexture);
    }

    if (src->quitTexture != NULL) {
        SDL_DestroyTexture(src->quitTexture);
    }
    if (src->movesGrid != NULL) {
        free(src->movesGrid);
    }
    if (src->gameRenderer != NULL) {
        SDL_DestroyRenderer(src->gameRenderer);
    }
    if (src->window != NULL) {
        SDL_DestroyWindow(src->window);
    }

    free(src);
    src = NULL;
}

SDL_Texture *getTexture(gameWin *gameWin,
                        char soldier) {
    switch (soldier) {
        case KING_BLACK:
            return gameWin->kingBlackTexture;
        case KING_WHITE:
            return gameWin->kingWhiteTexture;
        case QUEEN_BLACK:
            return gameWin->queenBlackTexture;
        case QUEEN_WHITE:
            return gameWin->queenWhiteTexture;
        case ROOK_BLACK:
            return gameWin->rookBlackTexture;
        case ROOK_WHITE:
            return gameWin->rookWhiteTexture;
        case BISHOP_BLACK:
            return gameWin->bishopBlackTexture;
        case BISHOP_WHITE:
            return gameWin->bishopWhiteTexture;
        case KNIGHT_BLACK:
            return gameWin->knightBlackTexture;
        case KNIGHT_WHITE:
            return gameWin->knightWhiteTexture;
        case PAWN_BLACK:
            return gameWin->pawnBlackTexture;
        case PAWN_WHITE:
            return gameWin->pawnWhiteTexture;
        default:
            return NULL;
    }

}

void drawGetMoves(gameWin *src) {
    SDL_Rect rect;
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            rect.x = GAMEBOARD_X + (j * TILE_SIZE);
            rect.y = ACTUAL_BOARD_SIZE - ((i + 1) * TILE_SIZE) + GAMEBOARD_Y;
            rect.w = TILE_SIZE;
            rect.h = TILE_SIZE;
            if (src->getMovesShowing == 1) {
                SDL_RenderCopy(src->gameRenderer, (src->movesGrid[i * sizeof(SDL_Texture *) + j]), NULL, &rect);
            } else {
                src->movesGrid[i * sizeof(SDL_Texture *) + j] = NULL;
            }
        }
    }
}

void gameWindowDraw(gameWin *src, GameSession *session) {
    if (src == NULL) {
        return;
    }
    SDL_Rect boardR = {.x = GAMEBOARD_X, .y = GAMEBOARD_Y, .h = 480, .w = 480};
    SDL_Rect soldiers[8][8];
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            soldiers[i][j].x = GAMEBOARD_X + (j * TILE_SIZE);
            soldiers[i][j].y = GAMEBOARD_Y + (i * TILE_SIZE);
            soldiers[i][j].h = TILE_SIZE;
            soldiers[i][j].w = TILE_SIZE;
        }
    }
    SDL_Rect undoR = {.x =X_GAME_BUTTONS, .y = GAMEBOARD_Y + 10, .h = GAME_BUTTONS_HIGHT, .w =101};
    SDL_Rect restartR = {.x =X_GAME_BUTTONS, .y = GAMEBOARD_Y + 90, .h = GAME_BUTTONS_HIGHT, .w = 173};
    SDL_Rect saveR = {.x =X_GAME_BUTTONS, .y = GAMEBOARD_Y + 170, .h = GAME_BUTTONS_HIGHT, .w = 151};
    SDL_Rect loadR = {.x =X_GAME_BUTTONS, .y = GAMEBOARD_Y + 250, .h = GAME_BUTTONS_HIGHT, .w = 155};
    SDL_Rect mainMenuR = {.x =X_GAME_BUTTONS, .y = GAMEBOARD_Y + 330, .h = GAME_BUTTONS_HIGHT, .w = 155};
    SDL_Rect quitR = {.x =X_GAME_BUTTONS, .y = GAMEBOARD_Y + 410, .h = GAME_BUTTONS_HIGHT, .w = 93};
    SDL_SetRenderDrawColor(src->gameRenderer, 0, 0, 0, 0);
    SDL_RenderClear(src->gameRenderer);
    SDL_RenderCopy(src->gameRenderer, src->gameBoardTexture, NULL, &boardR);
    for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
            if (session->game->gameBoard[i][j] != EMPTY_ENTRY) {
                if (GET_ROW(src->moveSrc) == i && GET_COLUMN(src->moveSrc) == j) {
                    SDL_RenderCopy(src->gameRenderer, getTexture(src, session->game->gameBoard[i][j]),
                                   NULL, &src->movingRect);
                } else {
                    SDL_RenderCopy(src->gameRenderer, getTexture(src, session->game->gameBoard[i][j]),
                                   NULL, &soldiers[7 - i][j]);
                }
            }
        }
    }


    drawGetMoves(src);

    if (session->mode == ONE_PLAYER) {
        if (session->game->history->actualSize > 0)
            SDL_RenderCopy(src->gameRenderer, src->undoTexture, NULL, &undoR);
        else
            SDL_RenderCopy(src->gameRenderer, src->undoFadeTexture, NULL, &undoR);

    }
    SDL_RenderCopy(src->gameRenderer, src->restartTexture, NULL, &restartR);
    if (src->isSaved)
        SDL_RenderCopy(src->gameRenderer, src->saveFadeTexture, NULL, &saveR);
    else
        SDL_RenderCopy(src->gameRenderer, src->saveTexture, NULL, &saveR);

    SDL_RenderCopy(src->gameRenderer, src->loadTexture, NULL, &loadR);
    SDL_RenderCopy(src->gameRenderer, src->mainMenuTexture, NULL, &mainMenuR);
    SDL_RenderCopy(src->gameRenderer, src->quitTexture, NULL, &quitR);
    SDL_RenderPresent(src->gameRenderer);
}

bool isClickedOnBoard(int x, int y) {
    if (x >= GAMEBOARD_X && x <= GAMEBOARD_X + ACTUAL_BOARD_SIZE)
        return (y >= GAMEBOARD_Y && y <= GAMEBOARD_Y + ACTUAL_BOARD_SIZE);
    return false;
}


int getClickRow(int y) {
    if (y >= GAMEBOARD_Y && y <= GAMEBOARD_Y + ACTUAL_BOARD_SIZE) {
        return GAME_SIZE - ((y - GAMEBOARD_Y) / TILE_SIZE);
    }
    return INVALID_ROW;
}

char getClickCol(int x) {
    if (x >= GAMEBOARD_X && x <= GAMEBOARD_X + ACTUAL_BOARD_SIZE) {
        return (char) ('A' + ((x - GAMEBOARD_X) / TILE_SIZE));
    }
    return INVALID_COL;
}

double getDistance(int x1, int y1, int x2, int y2) {
    return pow((y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2), 0.5);
}

void drag(SDL_Event *event, gameWin *src) {
    int srcX = src->movingRect.x + (TILE_SIZE / 2);
    int srcY = src->movingRect.y + (TILE_SIZE / 2);

    double distance = getDistance(srcX, srcY, event->button.x, event->button.y);

    if (distance > PIXELS_TO_CHANGE_MOTION) {
        src->movingRect.x = event->button.x - (TILE_SIZE / 2);
        src->movingRect.y = event->button.y - (TILE_SIZE / 2);
    }

}

bool isCastlingGameWindow(GameSession *session, Position source, Position dest, int myRow) {
    if (dest.column == source.column && dest.row == source.row)
        return true;
    if (source.row - 1 == myRow && source.column == KING_INITIAL_COL_CHAR) {
        if (dest.row - 1 == myRow) {
            if (dest.column == 'C' || dest.column == 'G')
                return true;
        }
    }
    return false;


}

bool showGetMovesGameWin(GameSession *session, gameWin *src, SDL_Event *event) {
    int row = getClickRow(event->button.y);
    char col = getClickCol(event->button.x);

    char soldier = session->game->gameBoard[row - 1][col - 'A'];
    if (session->user_color != getPlayer(soldier))
        return false;

    Position srcPos;
    srcPos.row = row;
    srcPos.column = col;
    Position movesList[GAME_SIZE * GAME_SIZE];
    int numOfMoves = getMoves(session->game, movesList, srcPos);

    Position curDest;
    char soldierAtSite;

    ChessGame *copy = gameCopy(session->game);

    for (int i = 0; i < numOfMoves; i++) {
        curDest = movesList[i];

        int myRow = session->user_color == WHITE_PLAYER ? WHITE_INITIAL_ROW - 1 : BLACK_INITIAL_ROW - 1;
        if (isCastlingGameWindow(session, srcPos, curDest, myRow)) {
            if (soldier == KING_BLACK || soldier == KING_WHITE) {
                int column = curDest.column == 'C' ? 0 : GAME_SIZE - 1;
                src->movesGrid[GET_ROW(curDest) * sizeof(SDL_Texture *) + column] = src->purple;
            } else {

                src->movesGrid[myRow * sizeof(SDL_Texture *) + KING_INITIAL_COL_NUM] = src->purple;
            }

        } else {
            src->movesGrid[GET_ROW(curDest) * sizeof(SDL_Texture *) + GET_COLUMN(curDest)] = src->yellow;
            soldierAtSite = session->game->gameBoard[GET_ROW(curDest)][GET_COLUMN(curDest)];
            if (soldierAtSite != EMPTY_ENTRY)
                src->movesGrid[GET_ROW(curDest) * sizeof(SDL_Texture *) + GET_COLUMN(curDest)] = src->green;
            setMove(copy, srcPos, curDest);
            if (myPositionUnderThreat(copy, curDest))
                src->movesGrid[GET_ROW(curDest) * sizeof(SDL_Texture *) + GET_COLUMN(curDest)] = src->red;
        }
        undoMove(copy);

    }
    gameDestroy(&copy);
    return true;


}

GAME_EVENT gameWindowHandleEvent(GameSession *session, gameWin *src, SDL_Event *event) {
    if (!event) {
        return GAME_INVALID;
    }
    switch (event->type) {
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT) {
                src->getMovesShowing = 0;
                if (isClickedOnUndo(event->button.x, event->button.y, session))
                    return GAME_UNDO;
                if (isClickedOnRestartGame(event->button.x, event->button.y))
                    return GAME_RESTART;
                if (isClickedOnSaveGame(event->button.x, event->button.y))
                    if (src->isSaved == 0)
                        return GAME_SAVE;
                if (isClickedOnLoadGame(event->button.x, event->button.y))
                    return GAME_LOAD;
                if (isClickedOnMainMenu(event->button.x, event->button.y)) {
                    if (src->isSaved)
                        return GAME_MAINMENU_SAVED;
                    return GAME_MAINMENU_UNSAVED;
                }
                if (isClickedOnQuitGame(event->button.x, event->button.y)) {
                    if (src->isSaved)
                        return GAME_QUIT_SAVED;
                    return GAME_QUIT_UNSAVED;
                }
                if (isClickedOnBoard(event->button.x, event->button.y) && src->currentlyDragged) {
                    src->currentlyDragged = 0;
                    src->moveDest.row = getClickRow(event->button.y);
                    src->moveDest.column = getClickCol(event->button.x);
                    src->isSaved = 0;
                    return GAME_MOVE;

                }
            } else if (event->button.button == SDL_BUTTON_RIGHT) {
                if (isClickedOnBoard(event->button.x, event->button.y)) {
                    if (session->difficulty <= 2 && session->mode == ONE_PLAYER) {
                        if (src->getMovesShowing)
                            src->getMovesShowing = 0;
                        else {
                            if (showGetMovesGameWin(session, src, event))
                                src->getMovesShowing = 1;
                        }
                    }
                } else {
                    src->getMovesShowing = 0;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (isClickedOnBoard(event->button.x, event->button.y)) {
                    char soldier = session->game->gameBoard[getClickRow(event->button.y) - 1][
                            getClickCol(event->button.x) - 'A'];
                    if (getPlayer(soldier) == session->game->currentPlayer) {
                        src->moveSrc.row = getClickRow(event->button.y);
                        src->moveSrc.column = getClickCol(event->button.x);
                        src->currentlyDragged = 1;
                        src->movingRect.x = event->button.x - (TILE_SIZE / 2);
                        src->movingRect.y = event->button.y - (TILE_SIZE / 2);
                    }
                } else
                    src->currentlyDragged = 0;
            }
            break;
        case SDL_MOUSEMOTION:
            if (src->currentlyDragged && isClickedOnBoard(event->button.x, event->button.y))
                drag(event, src);
            else {
                src->currentlyDragged = 0;
                src->moveSrc.row = INVALID_ROW;
                src->moveSrc.column = INVALID_COL;

            }


        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
                if (src->isSaved)
                    return GAME_QUIT_SAVED;
                return GAME_QUIT_UNSAVED;
            }
            break;
        default:
            return GAME_NONE;
    }
    return GAME_NONE;
}
