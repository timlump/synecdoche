#include<iostream>
#include<map>
#include<stdlib.h>
#include<string>

#include<GL\glew.h>
#define GLFW_DLL
#include<GLFW\glfw3.h>

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600

namespace Gfx
{
	class Graphics
	{
		public:
			Graphics(std::map<char,char*> args);
			bool init();
			~Graphics();
			
			void clear();
			void draw();
			bool update();
		private:
			GLFWmonitor *mMonitor;
			GLFWwindow *mWindow;
			int mScreenWidth,mScreenHeight;
			std::string mWindowName;
		
	};
	
	inline void bindToLua()
	{
		std::cout << "*Binding GFX Module to LUA" << std::endl;
	}
}