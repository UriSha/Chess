CC = gcc
OBJS = main.o ChessParser.o ChessHistory.o \
ChessGame.o MiniMax.o MainAux.o GuiManager.o \
GuiMainWindow.o GuiSettingsWindow.o GuiLoadWindow.o \
GuiGameWindow.o
 
EXEC = chessprog
COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@ -lm
main.o: main.c GuiManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessParser.o: ChessParser.c ChessParser.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessHistory.o: ChessHistory.c ChessHistory.h ChessParser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ChessGame.o: ChessGame.c ChessGame.h ChessParser.h ChessHistory.h  
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MiniMax.o: MiniMax.c MiniMax.h ChessGame.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MainAux.o: MainAux.c MainAux.h ChessGame.h MiniMax.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GuiMainWindow.o: GuiMainWindow.c GuiMainWindow.h GuiDefinitions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GuiSettingsWindow.o: GuiSettingsWindow.c GuiSettingsWindow.h GuiDefinitions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GuiLoadWindow.o: GuiLoadWindow.c GuiLoadWindow.h GuiDefinitions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GuiGameWindow.o: GuiGameWindow.c GuiGameWindow.h GuiDefinitions.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GuiManager.o: GuiManager.c GuiManager.h GuiMainWindow.h GuiSettingsWindow.h GuiLoadWindow.h GuiGameWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c 
clean:
	rm -f *.o $(EXEC)
