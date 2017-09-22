

#ifndef CHESS_CHESSGAME_H
#define CHESS_CHESSGAME_H

#include "ChessHistory.h"
#include "ChessParser.h"
#include <ctype.h>
/**
 *ChessGame Summary:
 *  A module that contains the game struct, all the functions that are connected straight to the game
 *  And of course some help functions to obey the ChessGame rules
 *  Some of the key functions :
 *
 *  ChessGame *gameCreate              - Creates a new game board and initialize the flags
 *  ChessGame *gameCopy                - Copies an existing game and flags
 *  void gameDestroy                   - Free all resources connected to the game struct
 *  CHESS_MESSAGE printBoard           - Prints the board
 *  int getPlayer                      - Returns the player number
 *  CHESS_MESSAGE movePiece            - Naively moves the piece according to the src and dest
 *  char getSoldier                    - Returns the soldier character
 *  char getOtherXXX                   - Returns the other player's soldier (king, queen, knight, pawn, rook or bishop)
 *  bool knightThreatsPosition         - Returns true if the other knight threat the Position
 *  bool kingThreatsPosition           - Returns true if the other king threat the Position
 *  bool diagonalOrHorizontalThreat    - Help function for QBRThreatsPosition
 *  bool QBRThreatsPosition            - Checks for bishops,rooks and queens that threat the position
 *  bool myPositionUnderThreat         - Checks, thanks to the above functions, if my Position is under threat
 *  bool legalCastling                 - Returns true if the current castling is legal
 *  bool isValidMove_XXX               - Help functions for isValidMove
 *  bool isValidMove                   - Checks if the current move is valid
 *  void updateScore                   - Updates the game score
 *  CHESS_MESSAGE setMove              - Setting a move in the game
 *  void changePlayer                  - Change the player's turn
 *  bool areThereAnyMoves              - Check if the player has legal moves
 *  CHESS_MESSAGE checkStatus          - Checks if there's a winner, a tie or check
 *  char *getStringFromPosition        - Returns a string according to Position
 *  CHESS_MESSAGE undoMove             - Placing a move backwards
 *  char *getSoldierName               - Returns the name of the soldier
 *  Position getKingPos                - Returns the position of the current player's king
 *
 *  // bonus functions
 *
 *  int getMoves                       - Help function for printMoves
 *  void printMoves                    - Prints the available moves for a soldier
 *  Position *isCastling               - Help function for printMoves, about castling move
 */

//Definitions
#define GAME_SIZE 8
#define WHITE_PLAYER 1
#define BLACK_PLAYER 0
#define EMPTY_SQUARE (-1)
#define EMPTY_ENTRY '_'
#define PAWN_WHITE 'm'
#define PAWN_BLACK 'M'
#define BISHOP_WHITE 'b'
#define BISHOP_BLACK 'B'
#define ROOK_WHITE 'r'
#define ROOK_BLACK 'R'
#define KNIGHT_WHITE 'n'
#define KNIGHT_BLACK 'N'
#define QUEEN_WHITE 'q'
#define QUEEN_BLACK 'Q'
#define KING_WHITE 'k'
#define KING_BLACK 'K'
#define KING_INITIAL_COL_CHAR 'E'
#define KING_INITIAL_COL_NUM 4
#define WHITE_INITIAL_ROW 1
#define BLACK_INITIAL_ROW 8
//Function Definitions
#define GET_COLUMN(x) ((x).column-65) //Only for Position struct
#define GET_ROW(x) ((x).row-1) // Only for Position struct
/**
 *  A struct that we use to represent the game itself
 *  We carry here the gameBoard, the current turn, the current score according to the white player,
 *  the last history for the undo moves, the positions of the kings and the flags for the castling move
 */
typedef struct chess_struct {
    char gameBoard[GAME_SIZE][GAME_SIZE];
    int currentPlayer;
    ChessHistory *history;
    int score;
    Position whiteKingPos;
    Position blackKingPos;
    bool rightWhiteRookMoved;
    bool leftWhiteRookMoved;
    bool rightBlackRookMoved;
    bool leftBlackRookMoved;
    bool whiteCastle;
    bool blackCastle;
} ChessGame;

/**
 * Creates a new game with a specified history size. The history size is a
 * parameter which specifies the number of previous moves to store. If the number
 * of moves played so far exceeds this parameter, then first moves stored will
 * be discarded in order for new moves to be stored.
 *
 * @historySize - The total number of moves to undo,
 *                a player can undo at most historySizeMoves turns.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new ChessGame instant is returned.
 */
ChessGame *gameCreate(int historySize);
/**
 *	Creates a copy of a given ChessGame.
 *	The new copy has the same status as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source ChessGame is returned.
 */
ChessGame *gameCopy(ChessGame *src);
/**
 * Frees all memory allocation associated with a given ChessGame. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void gameDestroy(ChessGame **src);
/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing. The character '_' represent
 * the empty entries
 * Capital letters are the black player's soldiers
 * The lowerCase letters are the white player's soldiers
 * @param src - the target game
 * @return
 * INVALID_ARGUMENT - if src==NULL
 * SUCCESS - otherwise
 */
CHESS_MESSAGE printBoard(ChessGame *src);
/**
 * Returns the current player according to the square that is passed to the function
 * @param soldier - gameBoard square
 * @return
 * -1 if the square is an empty entry
 * 0 if the soldier belongs to the Black player
 * 1 if the soldier belongs to the White player
 */
int getPlayer(char soldier);
/**
 * Naively moves the piece that is in the src Position to the dest Position, also performs castling if asked
 * @param game - ChessGame
 * @param src - Position of the source soldier
 * @param dest  - Position of the destination
 * @return
 * INVALID_ARGUMENT - if the game is NULL
 * SUCCESS - otherwise
 */
CHESS_MESSAGE movePiece(ChessGame *game, Position src, Position dest);
/**
 * Returns the soldier that is located in this specific location
 * @param board - The game board
 * @param row   - The row number, starts from 0
 * @param col   - The col number, starts from 0
 * @return
 * '\0' - if it's a wrong position or the game is NULL
 * Capital letter of one of the Black player's soldiers OR
 * LowerCase letter of one of the White player's soldiers
 */
char getSoldier(char board[GAME_SIZE][GAME_SIZE], int row, int col);
/**
 * Return the letter of the other knight, according to the player
 * @param player - will be wither WHITE_PLAYER or BLACK_PLAYER
 * @return
 * Capital letter of one of the Black player's soldiers OR
 * LowerCase letter of one of the White player's soldiers
 */
char getOtherKnight(int player);
/**
 * Return the letter of the other king, according to the player
 * @param player - will be wither WHITE_PLAYER or BLACK_PLAYER
 * @return
 * Capital letter of one of the Black player's soldiers OR
 * LowerCase letter of one of the White player's soldiers
 */
char getOtherKing(int player);
/**
 * Return the letter of the other queen, according to the player
 * @param player - will be wither WHITE_PLAYER or BLACK_PLAYER
 * @return
 * Capital letter of one of the Black player's soldiers OR
 * LowerCase letter of one of the White player's soldiers
 */
char getOtherQueen(int player);
/**
 * Return the letter of the other bishop, according to the player
 * @param player - will be wither WHITE_PLAYER or BLACK_PLAYER
 * @return
 * Capital letter of one of the Black player's soldiers OR
 * LowerCase letter of one of the White player's soldiers
 */
char getOtherBishop(int player);
/**
 * Return the letter of the other rook, according to the player
 * @param player - will be wither WHITE_PLAYER or BLACK_PLAYER
 * @return
 * Capital letter of one of the Black player's soldiers OR
 * LowerCase letter of one of the White player's soldiers
 */
char getOtherRook(int player);
/**
 * Return the letter of the other pawn, according to the player
 * @param player - will be wither WHITE_PLAYER or BLACK_PLAYER
 * @return
 * Capital letter of one of the Black player's soldiers OR
 * LowerCase letter of one of the White player's soldiers
 */
char getOtherPawn(int player);
/**
 * Return the letter of the other knight, according to the player
 * @param player - will be wither WHITE_PLAYER or BLACK_PLAYER
 * @return
 * 0 if the player is WHITE_PLAYER
 * 1 if the player is BLACK_PLAYER
 */
int getOtherPlayer(int player);
/**
 * Checks if one of the other player's knights threatens the current player's position
 * @param game - the ChessGame we play
 * @param row - row number of the gameBoard, starts from 0
 * @param col - col number of the gameBoard, starts from 0
 * @return
 * True - if there's a knight threatening the position
 * False - otherwise
 */
bool knightThreatsPosition(ChessGame *game, int row, int col);
/**
 * Checks if  the other player's king threatens the current player's position
 * @param game - the ChessGame we play
 * @param row - row number of the gameBoard, starts from 0
 * @param col - col number of the gameBoard, starts from 0
 * @return
 * True - if the  king is threatening the position
 * False - otherwise
 */
bool kingThreatsPosition(ChessGame *game, int row, int col);

bool diagonalOrHorizontalThreat(ChessGame *game, int rowPlusMinus, int colPlusMinus, int curRow, int curCol);

bool QBRThreatsPosition(ChessGame *game, int row, int col);

bool myPositionUnderThreat(ChessGame *game, Position pos);

bool legalCastling(ChessGame *game, Position src, Position dest, bool isRightCastling);

bool isValidMove_King(ChessGame *game, Position src, Position dest);

bool isValidMove_Queen(ChessGame *game, Position src, Position dest);

bool isValidMove_Knight(ChessGame *game, Position src, Position dest);

bool isValidMove_Bishop(ChessGame *game, Position src, Position dest);

bool isValidMove_Rook(ChessGame *game, Position src, Position dest);

bool isValidMove_Pawn(ChessGame *game, Position src, Position dest);

bool isValidMove(ChessGame *game, Position src, Position dest);

void updateScore(char soldierDied, ChessGame *game);

CHESS_MESSAGE setMove(ChessGame *game, Position src, Position dest);

void changePlayer(ChessGame *game);

//int getSoldierColor(char soldier); we have that function already!

bool areThereAnyMoves(ChessGame *game);

CHESS_MESSAGE checkStatus(ChessGame *game);

char *getStringFromPosition(Position dest);

CHESS_MESSAGE undoMove(ChessGame *game);

char *getSoldierName(char soldier);

Position getKingPos(ChessGame *game, bool isWhiteKing);

// bonus functions

int getMoves(ChessGame *game, Position *result, Position pos);

void printMoves(ChessGame *game, Position pos);

Position *isCastling(ChessGame *game, moveNode move);



#endif //CHESS_CHESSGAME_H
