CC = mingw32-g++

HEADERS = -I$(LUA_ROOT) -I$(GLFW_ROOT)\include -I$(GLEW_ROOT)\include
LIBRARIES = -L$(GLFW_ROOT)\build\src\

all: main.o graphics.o
	$(CC) main.o graphics.o -o Synecdoche $(LIBRARIES) $(GLFW_ROOT)\build\src\glfw3dll.a -lglfw3 -lopengl32
	
main.o: main.cpp
	$(CC) -c main.cpp $(HEADERS) $(LIBRARIES)
	
graphics.o: graphics.cpp
	$(CC) -c graphics.cpp $(HEADERS) $(LIBRARIES)
	
clean:
	del *.o *.exe