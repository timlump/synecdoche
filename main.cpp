#include <iostream>
#include <lua.hpp>
#include <map>
#include <cstring>
#include "graphics.h"

bool running = true;

std::map<char, char*> parseArguments(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	//parse command line arguments
	std::map<char,char*> args = parseArguments(argc,argv);
	
	//bind modules
	Gfx::bindToLua();
	
	//set up modules
	Gfx::Graphics *gfxModule = new Gfx::Graphics(args);
	
	//initialize modules
	gfxModule->init();
	
	//loop
	while(running)
	{
		
	}
	
	//clean up
	delete gfxModule;
	
	return 0;
}

std::map<char, char*> parseArguments(int argc, char* argv[])
{
	std::map<char,char*> result;
	
	//discard the first argument as it will just be the name of the program
	for(int i = 1 ; i < argc ; i++)
	{
		if(argv[i][0] == '-' && strlen(argv[i]) == 2)
		{
			i++;//skip ahead once index to get the argument value
			if(i < argc)
			{
				result[argv[i-1][1]] = argv[i];
			}
		}
	}
	
	return std::map<char,char*>(result);
}