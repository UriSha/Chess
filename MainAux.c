
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
    fprintf(saveFile,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(saveFile,"<game>\n");
    fprintf(saveFile,"\t<current_turn>%d</current_turn>\n",game->currentPlayer);
    if(mode==1) {
        fprintf(saveFile, "\t<difficulty>%d</difficulty>\n", difficulty);
        fprintf(saveFile, "\t<user_color>%d</user_color>\n", userColor);
    }
    fprintf(saveFile,"\t<board>\n");
    for(int i=GAME_SIZE;i>0;i--)
        fprintf(saveFile, "\t\t<row_%d>%s</row_%d>\n",i,game->gameBoard[i-1],i);
    fprintf(saveFile,"\t</board>\n");
    fprintf(saveFile,"</game>\n");

    fclose(saveFile);
    return true;

}

