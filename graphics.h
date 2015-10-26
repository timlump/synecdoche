#include <iostream>
#include <map>
//#include<GL\glew.h>
#define GLFW_DLL
#include<GLFW\glfw3.h>

namespace Gfx
{
	class Graphics
	{
		public:
			Graphics(std::map<char,char*> args);
			bool init();
			~Graphics();
		private:
			GLFWmonitor *mMonitor;
			GLFWwindow *mWindow;
		
	};
	
	inline void bindToLua()
	{
		std::cout << "*Binding GFX Module to LUA" << std::endl;
	}
}