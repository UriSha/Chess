
#include "MainAux.h"

bool undo(ChessGame* game,int mode){
    if(game==NULL)
        return false;
    if(mode==TWO_PLAYER){
        printf("Undo command not available in 2 players mode\n");
        return false;
    }
    HistoryNode undoNode;
    CHESS_MESSAGE undoMessage=undoMove(game);
    if(undoMessage==INVALID_ARGUMENT)
        return false;
    if (undoMessage==NO_HISTORY) {
        printf("Empty history, move cannot be undone\n");
        return false;
    }
    undoNode.source=game->history->moves[game->history->actualSize].source;
    undoNode.destination=game->history->moves[game->history->actualSize].destination;
    char* playerColor=getOtherPlayer(game->currentPlayer)==WHITE_PLAYER ? "white" : "black";
    printf("Undo move for player %s : <%d,%c> -> <%d,%c>\n",playerColor,undoNode.destination.row,undoNode.destination.column,
           undoNode.source.row,undoNode.source.column);
    changePlayer(game);
    return true;
}
void quit(ChessGame* game){
    if(game!=NULL){
        printf("Exiting...\n");
        gameDestroy(&game);
        exit(0);
    }
}
void restartGame(ChessGame* game){
    if(game!=NULL){
        printf("Restarting...\n");
        gameDestroy(&game);
        game=gameCreate(HISTORYSIZE);
    }

}
bool saveGame(char* filePath ,ChessGame* game,int mode, int difficulty, int userColor){
    if(game==NULL)
        return false;
    FILE *saveFile=NULL;
    saveFile=fopen(filePath,"w");
    if(saveFile==NULL) {
        printf("File cannot be created or modified\n");
        return false;
    }
    fprintf(saveFile,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(saveFile,"<game>\n");
    fprintf(saveFile,"\t<current_turn>%d</current_turn>\n",game->currentPlayer);
    fprintf(saveFile,"\t<game_mode>%d</game_mode> \n",mode);
    if(mode==1) {
        fprintf(saveFile, "\t<difficulty>%d</difficulty>\n", difficulty);
        fprintf(saveFile, "\t<user_color>%d</user_color>\n", userColor);
    }
    fprintf(saveFile,"\t<board>\n");
    for(int i=GAME_SIZE;i>0;i--)
        fprintf(saveFile, "\t\t<row_%d>%.8s</row_%d>\n",i,game->gameBoard[i-1],i);
    fprintf(saveFile,"\t</board>\n");
    fprintf(saveFile,"</game>\n");

    fclose(saveFile);
    return true;

}
bool loadGame(char* filePath,GameSession* gameSession){// TODO is sscanf problematic?
    FILE* loadedFile=NULL;
    loadedFile=fopen(filePath,"r");
    if(loadedFile==NULL)
    {
        printf("Error: File doesn’t exist or cannot be opened\n");
        return false;
    }
    char* token=(char*)malloc(MAX_LINE_LENGTH*sizeof(char));
    gameSession->game=gameCreate(HISTORYSIZE);
    fgets(token,MAX_LINE_LENGTH,loadedFile);
    fgets(token,MAX_LINE_LENGTH,loadedFile);
    fgets(token,MAX_LINE_LENGTH,loadedFile);
    sscanf(token, "\t<current_turn>%d", &(gameSession->game->currentPlayer));
    fgets(token,MAX_LINE_LENGTH,loadedFile);
    sscanf(token,"\t<game_mode>%d",&(gameSession->mode));
    if(gameSession->mode==ONE_PLAYER)
    {
        fgets(token,MAX_LINE_LENGTH,loadedFile);
        sscanf(token, "\t<difficulty>%d", &(gameSession->difficulty));
        fgets(token,MAX_LINE_LENGTH,loadedFile);
        sscanf(token,"\t<user_color>%d",&(gameSession->userColor));

    }
    fgets(token,MAX_LINE_LENGTH,loadedFile);

    char currentRow[GAME_SIZE];
    for(int i=GAME_SIZE;i>0;i--)
    {
        fgets(token,MAX_LINE_LENGTH,loadedFile);
        sscanf(token,"\t\t<row_%d>%s</row_%d>\n",&i,currentRow,&i);
        for(int j=0;j<GAME_SIZE;j++)
            gameSession->game->gameBoard[i-1][j]=currentRow[j];
    }

    return true;
}
bool processCommand(GameSession* sesssion, ChessCommand command)
{
    if(sesssion==NULL)
        return false;
    switch(command.cmd)
    {
        case UNDO_MOVE:
            if(command.validArg)
            {
                if(sesssion->mode!=ONE_PLAYER) {
                    printf("Undo command not available in 2 players mode\n");
                    return false;
                }
                undoMove(sesssion->game);
                undoMove(sesssion->game);
                return true;
            }
            return false;
        case MOVE:
            if(!command.validArg){
                printf("Invalid position on the board\n");
                return false;
            }
            if(getPlayer(sesssion->game->gameBoard[GET_ROW(command.source)][GET_COLUMN(command.source)])!=sesssion->game->currentPlayer){
                printf("The specified position does not contain your piece\n");
                return false;
            }
            if(setMove(sesssion->game,command.source,command.destination)!=SUCCESS){
                printf("Illegal move\n");
                return false;
            }
            changePlayer(sesssion->game);
            return true;
        case GET_MOVES:
            return true;//TODO continue from here


    }

}

