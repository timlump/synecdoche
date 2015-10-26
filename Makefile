CC = mingw32-g++

HEADERS = -I$(LUA_ROOT) -I$(GLFW_ROOT)\include -I$(GLEW_ROOT)\include
LIBRARIES = -L$(GLFW_ROOT)\build\src -L$(GLEW_ROOT)\build\lib
LIB_FILES = $(GLFW_ROOT)\build\src\glfw3dll.a \
 $(GLEW_ROOT)\build\lib\libglew.a \
 $(GLEW_ROOT)\build\lib\libglewmx.a \
 $(GLEW_ROOT)\build\lib\liblibglew_shared.dll.a \
 $(GLEW_ROOT)\build\lib\liblibglewmx_shared.dll.a \
 -lglfw3 -lopengl32 -lglew -lglewmx

all: main.o graphics.o
	$(CC) main.o graphics.o -o Synecdoche $(LIBRARIES) $(LIB_FILES)
	
main.o: main.cpp
	$(CC) -c main.cpp $(HEADERS) $(LIBRARIES)
	
graphics.o: graphics.cpp
	$(CC) -c graphics.cpp $(HEADERS) $(LIBRARIES)
	
clean:
	del *.o *.exe