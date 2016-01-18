#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>

#include <lua.hpp>
#include "shader.h"

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600
#define CLEAR_COLOR 0.39,0.58,0.92,1.0

class Graphics
{
	public:
		Graphics();
		Graphics(std::map<char,char*> args);
		bool init();
		~Graphics();
		
		GLuint getCurrentShader();
		void setCurrentShader(GLuint shaderID);
	
		void clear();
		void draw();
		void swap();
		bool update();
		
		void setWindowTitle(std::string title);
		double getTime();

		//input callbacks
		void *mMouseButtonCallback;
		void *mCursorCallback;
		void *mScrollCallback;
		void *mKeyCallback;
		void *mCharCallback;
		
		Shader *mShader;
		static Graphics* getInstance();
		
		static Graphics *mInstance;
		static void bindToLua(lua_State *L,Graphics* ptr = NULL);
		
	private:
		GLFWwindow *mWindow;
		int mScreenWidth,mScreenHeight;
		GLuint mCurrentShader;
		std::string mWindowName;
		
};