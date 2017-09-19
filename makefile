FLAGS = -c -std=c99 -pedantic-errors -Wall -Werror -g $(CFLAGS) 
HFILES = ChessParser.h  ChessHistory.h MiniMax.h MainAux.h MainAux.h
OBJECTS = ChessHistory.o ChessGame.o main.o MainAux.o MiniMax.o ChessParser.o
all: chessprog



clean:
	rm -r $(OBJECTS) chessprog

chessprog: $(OBJECTS)
	gcc -o chessprog $(OBJECTS) -std=c99 -Wall -Wextra -Werror -pedantic-errors -g
	
ChessParser.o: ChessParser.c $(HFILES)
	gcc $(FLAGS) ChessParser.c -o ChessParser.o

ChessHistory.o: ChessHistory.c $(HFILES)
	gcc $(FLAGS) ChessHistory.c -o ChessHistory.o

ChessGame.o: ChessGame.c $(HFILES)
	gcc $(FLAGS) ChessGame.c -o ChessGame.o

MiniMax.o: MiniMax.c $(HFILES)
	gcc $(FLAGS) MiniMax.c -o MiniMax.o

MainAux.o: MainAux.c $(HFILES)
	gcc $(FLAGS) MainAux.c -o MainAux.o

main.o: main.c $(HFILES)
	gcc $(FLAGS) main.c -o main.o