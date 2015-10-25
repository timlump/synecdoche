CC = mingw32-g++

all: main.o graphics.o
	$(CC) main.o graphics.o -o Synecdoche
	
main.o: main.cpp
	$(CC) -c main.cpp -I$(LUA_ROOT)
	
graphics.o: graphics.cpp
	$(CC) -c graphics.cpp
	
clean:
	del *.o *.exe