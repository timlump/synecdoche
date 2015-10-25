#pragma once
#include <iostream>
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>

namespace Gfx
{
	class Graphics
	{
		public:
			Graphics(int argc, const char* argv[]);
		private:
		
	};
	
	inline void bindToLua()
	{
		std::cout << "*Binding GFX Module to LUA" << std::endl;
	}
}