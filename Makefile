CC = mingw32-g++

HEADERS = -I$(LUA_ROOT) -I$(GLFW_ROOT)\include -I$(GLEW_ROOT)\include -I$(IRRKLANG_ROOT)\include -I$(OOLUA_ROOT)\include -I$(SDL_ROOT)\include -I$(GLM_ROOT)
LIBRARIES = -L$(GLFW_ROOT)\build\src -L$(GLEW_ROOT)\build\lib -L$(IRRKLANG_ROOT)\lib\Win32-gcc \
-L$(LUA_ROOT) -L$(OOLUA_ROOT)\bin\release -L$(SDL_ROOT)\lib
LIB_FILES = $(GLFW_ROOT)\build\src\glfw3dll.a \
 $(GLEW_ROOT)\build\lib\libglew.a \
 $(GLEW_ROOT)\build\lib\libglewmx.a \
 $(GLEW_ROOT)\build\lib\liblibglew_shared.dll.a \
 $(GLEW_ROOT)\build\lib\liblibglewmx_shared.dll.a \
 -lglfw3 -lopengl32 -lglew -lglewmx -lirrKlang -llua -loolua

all: main.o graphics.o sound.o shader.o entity.o
	$(CC) main.o graphics.o sound.o shader.o entity.o -o Synecdoche $(LIBRARIES) $(LIB_FILES)
	
main.o: main.cpp
	$(CC) -c main.cpp $(HEADERS)
	
graphics.o: graphics.cpp shader.cpp
	$(CC) -c graphics.cpp shader.cpp $(HEADERS)
	
sound.o: sound.cpp
	$(CC) -c sound.cpp $(HEADERS)

entity.o: entity.cpp
	$(CC) -c entity.cpp $(HEADERS)
	
clean:
	del *.o *.exe