#include <iostream>
#include <lua.hpp>
#include "graphics.h"

int main(int argc, char* argv[])
{
	for(int i = 0 ; i < argc ; i++)
		std::cout << argv[i] << std::endl;
	
	//bind modules
	Gfx::bindToLua();
	
	//set up modules
	const char ** const_argv = const_cast<const char**>(argv);
	Gfx::Graphics *gfxModule = new Gfx::Graphics(argc,const_argv);
	
	return 0;
}