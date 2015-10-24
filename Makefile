CC = mingw32-g++

all:main.o
	$(CC) main.o -o Synecdoche
	
main.o: main.cpp
	$(CC) -c main.cpp -I$(LUA_ROOT)
	
clean:
	del *.o *.exe