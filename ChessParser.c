#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ChessParser.h"

bool spParserIsInt(const char* str){
    if (str[0] != 45 && (str[0] < 48 || str[0] > 57))
        return false;
    if (str[0] == 45 && str[1]=='\0')
        return false;

    for(int i=1;str[i] != '\0';i++){
        if (str[i] < 48 || str[i] > 57){
            return false;
        }
    }
    return true;
}

