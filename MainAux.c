
#include "MainAux.h"

bool undo(ChessGame* game){
    if(game==NULL)
        return false;
    HistoryNode* lastMove=removeRecentMove(game->history);


}
