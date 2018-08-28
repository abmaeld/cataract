
CC = g++
STD = c++11
OPT = -mfpmath=sse -Ofast -march=native
FLAGS = -std=$(STD) -Wall -Wextra $(OPT)
LIBS = -pthread
PROGRAM = Cataract
OBJS = Image.o Hough.o Processing.o Analysis.o Interface.o Main.o

ifeq ($(OS),Windows_NT)
    
    RM = del
    MV = move

else
    
    RM = rm
    MV = mv

endif

$(PROGRAM): $(OBJS)

	$(CC) $(FLAGS) $(OBJS) $(LIBS) -o bin/$(PROGRAM)
	$(MV) $(OBJS) build/

Image.o:

	$(CC) $(FLAGS) -c src/Image.cpp

Hough.o:

	$(CC) $(FLAGS) -c src/Hough.cpp -pthread

Processing.o:

	$(CC) $(FLAGS) -c src/Processing.cpp

Analysis.o:

	$(CC) $(FLAGS) -c src/Analysis.cpp 	

Interface.o:

	$(CC) $(FLAGS) -c src/Interface.cpp

Main.o:

	$(CC) $(FLAGS) -c src/Main.cpp 

clean:

	$(RM) build/*.o
