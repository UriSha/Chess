#include <stdio.h>
#include "ChessParser.h"

int main() {
    printf("Hello, World! %d\n",isInt("b"));
    printf("Hello, World!\n");


    char str[1024];
    fgets(str,1024,stdin);

    ChessCommand cmd = parseLine(str);

    int d = 5;


    return 1;

}