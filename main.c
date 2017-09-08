#include <stdio.h>
#include <ctype.h>
#include "ChessParser.h"
//#include "ChessHistory.h"
//#include "ChessGame.h"
#include "tester.h"


int main() {
    ChessCommand cmd;
    cmd = parseLine("game_mode 0");
    if (cmd.validArg!=false) { printf("Error 1\n"); }

    cmd = parseLine("game_mode 1");
    if (cmd.cmd != GAME_MODE || cmd.argument != 1) { printf("Error 2\n"); }

    cmd = parseLine("difficulty 5");
    if (cmd.validArg==false) { printf("Error 3\n"); }

    cmd = parseLine("difficulty 0");
    if (cmd.validArg!=false) { printf("Error 4\n"); }

    cmd = parseLine("difficulty 3");
    if (cmd.cmd != DIFFICULTY || cmd.argument != 3) { printf("Error 5\n"); }

    cmd = parseLine("user_color 3");
    if (cmd.validArg!=false) { printf("Error 6\n"); }

    cmd = parseLine("user_color 1");
    if (cmd.cmd != USER_COLOR || cmd.argument != 1) { printf("Error 7\n"); }

    cmd = parseLine("default 1");
    if (cmd.validArg!=false) { printf("Error 8\n"); }

    cmd = parseLine("default");
    if (cmd.cmd != DEFAULT) { printf("Error 9\n"); }

    cmd = parseLine("quit 1");
    if (cmd.validArg!=false) { printf("Error 10\n"); }

    cmd = parseLine("quit");
    if (cmd.cmd != QUIT) { printf("Error 11\n"); }

    cmd = parseLine("start 1");
    if (cmd.validArg!=false) { printf("Error 12\n"); }

    cmd = parseLine("start");
    if (cmd.cmd != START) { printf("Error 13\n"); }

    cmd = parseLine("move <8,A> <4,B>");
    if (cmd.validArg!=false) { printf("Error 14\n"); }

    cmd = parseLine("move <9,A> to <4,B>");
    if (cmd.validArg!=false) { printf("Error 15\n"); }

    cmd = parseLine("move <8,I> to <4,B>");
    if (cmd.validArg!=false) { printf("Error 16\n"); }

    cmd = parseLine("move <8,A> to <9,B>");
    if (cmd.validArg!=false) { printf("Error 17\n"); }

    cmd = parseLine("move <8,A> to <5,K>");
    if (cmd.validArg!=false) { printf("Error 18\n"); }

    cmd = parseLine("move <8,A> to <5,A)");
    if (cmd.validArg!=false) { printf("Error 19\n"); }

    cmd = parseLine("move <8,A> to <5.A>");
    if (cmd.validArg!=false) { printf("Error 20\n"); }

    cmd = parseLine("move <8,A> to <5,C>");
    if (cmd.cmd != MOVE || cmd.source.row != 8 || cmd.destination.row != 5
        || cmd.source.column != 'A' || cmd.destination.column != 'C') { printf("Error 21\n"); }

    cmd = parseLine("move <5,H> to <5,A>");
    if (cmd.cmd != MOVE || cmd.source.row != 5 || cmd.destination.row != 5
        || cmd.source.column != 'H' || cmd.destination.column != 'A') { printf("Error 22\n"); }

    cmd = parseLine("reset 1");
    if (cmd.validArg!=false) { printf("Error 23\n"); }

    cmd = parseLine("reset");
    if (cmd.cmd != RESTART) { printf("Error 24\n"); }

    testGame();
}