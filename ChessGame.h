

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
    int rightWhiteRookMoved;
    int leftWhiteRookMoved;
    int rightBlackRookMoved;
    int leftBlackRookMoved;
    int whiteCastle;
    int blackCastle;
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
/**
 * It's a help function that scans across diagonal and horizontal areas for threats
 * Starts from a specific location
 * We will call this function with different parameters in order to scan the whole area
 * For threats from the opponent
 * @param game  - The ChessGame
 * @param rowPlusMinus - Will be either 1 , 0 or -1, it depends which function called this function
 * @param colPlusMinus - Will be either 1 , 0 or -1, it depends which function called this function
 * @param curRow - Which row we need to start search for threats
 * @param curCol - Which col we need to start search for threats
 * @return
 * True - if there's a threat at the area we are looking, for the Position
 * False - otherwise
 */
bool diagonalOrHorizontalThreat(ChessGame *game, int rowPlusMinus, int colPlusMinus, int curRow, int curCol);
/**
 * This function checks if there's an opponent queen, bishop or rook that threats our specific Position
 * This fuction gets help from the other help functions above
 * @param game
 * @param row
 * @param col
 * @return
 */
bool QBRThreatsPosition(ChessGame *game, int row, int col);
/**
 * This is the main function that checks for a specific location, if there's any danger for him
 * From other soldiers of the opponent.
 * @param game  - The ChessGame
 * @param pos   - The position we want to check
 * @return
 * True - If there's an actual threat
 * False - otherwise
 */
bool myPositionUnderThreat(ChessGame *game, Position pos);
/**
 * Checks if the castling move we are trying to do is legal
 * @param game -  The ChessGame
 * @param src  - The source position of the king
 * @param dest   - The destination position of the king
 * @param isRightCastling - a flag that is true if the castling move is right castling
 * @return
 * True - If this specific castling move is legal
 * False - otherwise
 */
bool legalCastling(ChessGame *game, Position src, Position dest, bool isRightCastling);
/**
 * Returns true if the move from the source Position to destination Position is legal for a king
 * @param game - The ChessGame
 * @param src  - The source Position
 * @param dest - The destination Position
 * @return
 * True - if the move is legal
 * False - otherwise
 */
bool isValidMove_King(ChessGame *game, Position src, Position dest);
/**
 * Returns true if the move from the source Position to destination Position is legal for a queen
 * @param game - The ChessGame
 * @param src  - The source Position
 * @param dest - The destination Position
 * @return
 * True - if the move is legal
 * False - otherwise
 */
bool isValidMove_Queen(ChessGame *game, Position src, Position dest);
/**
 * Returns true if the move from the source Position to destination Position is legal for a knight
 * @param game - The ChessGame
 * @param src  - The source Position
 * @param dest - The destination Position
 * @return
 * True - if the move is legal
 * False - otherwise
 */
bool isValidMove_Knight(ChessGame *game, Position src, Position dest);
/**
 * Returns true if the move from the source Position to destination Position is legal for a bishop
 * @param game - The ChessGame
 * @param src  - The source Position
 * @param dest - The destination Position
 * @return
 * True - if the move is legal
 * False - otherwise
 */
bool isValidMove_Bishop(ChessGame *game, Position src, Position dest);
/**
 * Returns true if the move from the source Position to destination Position is legal for a rook
 * @param game - The ChessGame
 * @param src  - The source Position
 * @param dest - The destination Position
 * @return
 * True - if the move is legal
 * False - otherwise
 */
bool isValidMove_Rook(ChessGame *game, Position src, Position dest);
/**
 * Returns true if the move from the source Position to destination Position is legal for a pawn
 * @param game - The ChessGame
 * @param src  - The source Position
 * @param dest - The destination Position
 * @return
 * True - if the move is legal
 * False - otherwise
 */
bool isValidMove_Pawn(ChessGame *game, Position src, Position dest);
/**
 * Returns true if the move from the source Position to destination Position is legal
 * First, checks what kind of soldier we have in the square and uses one of the above functions
 * @param game - The ChessGame
 * @param src  - The source Position
 * @param dest - The destination Position
 * @return
 * True - if the move is legal
 * False - otherwise
 */
bool isValidMove(ChessGame *game, Position src, Position dest);
/**
 * Updates the ChessGame score integer, in case soldier gets "killed" - for the scoring function
 * @param soldierDied - will be one of the soldiers in the game, or an empty square
 * @param game - The ChessGame
 */
void updateScore(char soldierDied, ChessGame *game);
/**
 * This function uses a lot of help functions, and placing the actual move in the game
 * If the move is legal, the function moves the soldier from the source to destination Positions
 * It also updates the score, updates the castling flags and adds the move to history
 * @param game - The ChessGame
 * @param src  - The source Position
 * @param dest - The destination Position
 * @return
 * INVALID_ARGUMENT - If the game is NULL
 * ILLEGAL_MOVE - If the move we are trying to do is illegal
 * SUCCESS - otherwise
 */
CHESS_MESSAGE setMove(ChessGame *game, Position src, Position dest);
/**
 * a simple function that changes the current player inside the struct
 * @param game - The ChessGame
 */
void changePlayer(ChessGame *game);

/**
 * Returns true if there is a legal move for the current player.
 * Gets help from the other functions, such as isValidMove and threats checking
 * @param game - The ChessGame
 * @return
 * True - If there is a legal move to the current player
 * False - otherwise
 */
bool areThereAnyMoves(ChessGame *game);
/**
 * Scanning the gameBoard and returns the appropriate message according to the gameBoard status
 * @param game - The ChessGame
 * @return
 * INVALID_ARGUMENT - If the game is NULL
 * CHECK - if the king of the current player is threatened
 * MATE - if the king of the current player is threatened, and there are no legal moves
 * TIE - if there are no legal moves for the current player, but the king is safe
 * CONTINUE - if the king of the current player is safe, and there is at least one legal move
 */
CHESS_MESSAGE checkStatus(ChessGame *game);
/**
 * This function gets as a parameter a Position and returns a string, according to the format
 * The format is <Int,Char>, the Int would be 1-8 and the Char would be A-H
 * @param dest - The Position we are checking
 * @return
 * A string contains the right format according to the game
 */
char *getStringFromPosition(Position dest);
/**
 * Placing a move backwards, if the history is not empty.
 * Takes the last move and just do it backwards, reviving a soldier that died if it needs to.
 * @param game
 * @return
 * INVALID_ARGUMENT - If the game is NULL
 * NO_HISTORY - if the history is empty (or the player did undoMove for 3 times in a row)
 * SUCCESS - otherwise
 */
CHESS_MESSAGE undoMove(ChessGame *game);
/**
 * THis function gets as a parameter the char in the gameBoard and returns a string that contains
 * The full name of the soldier, i.e 'M' == "Pawn"
 * @param soldier - the char in the gameBoard
 * @return
 * A string that contains the soldier name
 */
char *getSoldierName(char soldier);
/**
 * This function returns the position of the current player's King
 * @param game - The ChessGame
 * @param isWhiteKing - a flag that indicates if the current player is WHITE_PLAYER or BLACK_PLAYER
 * @return
 * Position of the current player's King
 */
Position getKingPos(ChessGame *game, bool isWhiteKing);

// bonus functions
/**
 * A help function that gets a Position and returns all the legal moves it can do
 * @param game - THe ChessGame
 * @param result - The list of legal moves
 * @param pos - Position of the soldier we are checking
 * @return
 * a Position array with all the legal moves
 */
int getMoves(ChessGame *game, Position *result, Position pos);
/**
 * This function gets as a parameter a desired Position and
 * Prints a list of all legal moves this soldier can do, according to the game rules and the gameBoard
 * @param game - The ChessGame
 * @param pos - A desired Position
 */
void printMoves(ChessGame *game, Position pos);
/**
 * This function gets a moveNode - a move that was played during the game, and checks if this move was
 * Castling move. if yes:
 * It returns the Position of the rook and the Position of the king, after the Castling move
 * @param game - The ChessGame
 * @param move - moveNode with a move that was played during the game
 * @return
 * an array of two Positions - that contains either invalid data or the Positions of the rook and king
 */
Position *isCastling(ChessGame *game, moveNode move);

/**
 * calculates the score of a given game
 *
 * @param game
 * @return the score of the game
 */
int getScore(ChessGame *game);
#endif //CHESS_CHESSGAME_H
