CC = mingw32-g++

HEADERS = -I$(LUA_ROOT) -I$(GLFW_ROOT)\include -I$(GLEW_ROOT)\include -I$(IRRKLANG_ROOT)\include
LIBRARIES = -L$(GLFW_ROOT)\build\src -L$(GLEW_ROOT)\build\lib -L$(IRRKLANG_ROOT)\lib\Win32-gcc
LIB_FILES = $(GLFW_ROOT)\build\src\glfw3dll.a \
 $(GLEW_ROOT)\build\lib\libglew.a \
 $(GLEW_ROOT)\build\lib\libglewmx.a \
 $(GLEW_ROOT)\build\lib\liblibglew_shared.dll.a \
 $(GLEW_ROOT)\build\lib\liblibglewmx_shared.dll.a \
 $(IRRKLANG_ROOT)\lib\Win32-gcc\libirrKlang.a \
 -lglfw3 -lopengl32 -lglew -lglewmx -lirrKlang

all: main.o graphics.o
	$(CC) main.o graphics.o -o Synecdoche $(LIBRARIES) $(LIB_FILES)
	
main.o: main.cpp
	$(CC) -c main.cpp $(HEADERS)
	
graphics.o: graphics.cpp
	$(CC) -c graphics.cpp $(HEADERS)
	
sound.o: sounds.cpp
	$(CC) -c sound.cpp $(HEADERS)
	
clean:
	del *.o *.exe