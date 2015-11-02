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
	
		void clear();
		void draw();
		bool update();
		
		void setWindowTitle(std::string title);
		double getTime();
		
		GLuint mVAO,mVBO,mEBO,mTBO,mTBTEX;
		GLint mMaxTBOSize;
		Shader *mShader;
		static Graphics* getInstance();
		
		static Graphics *mInstance;
		static void bindToLua(lua_State *L,Graphics* ptr = NULL);
		
	private:
		GLFWwindow *mWindow;
		int mScreenWidth,mScreenHeight;
		std::string mWindowName;
		
};