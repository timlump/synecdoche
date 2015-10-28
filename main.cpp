#include <iostream>
#include <lua.hpp>
#include <oolua.h>
#include <map>
#include <cstring>

#include "graphics.h"
#include "sound.h"

class TestClass
{
	
};

OOLUA_PROXY(TestClass)
OOLUA_PROXY_END

OOLUA_EXPORT_NO_FUNCTIONS(TestClass)

lua_State *L;

void testLuaFunc()
{
	std::cout<<"Lua binding succeeded" << std::endl;
}

OOLUA_CFUNC(testLuaFunc,l_test)

std::map<char, char*> parseArguments(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	//parse command line arguments
	std::map<char,char*> args = parseArguments(argc,argv);
	
	//get game lua script if specified in arguments
	std::map<char,char*>::iterator it;
	std::string scriptName = "scripts/default.lua";
	if((it = args.find('s'))!=args.end())
	{
		scriptName = std::string(it->second);
	}
	
	//initialize lua
	L = luaL_newstate();
	luaL_openlibs(L);
	
	//setup oolua
	OOLUA::setup_user_lua_state(L);
	
	OOLUA::set_global(L,"test",l_test);
	OOLUA::register_class<TestClass>(L);
	
	if(luaL_loadfile(L,scriptName.c_str()))
	{
		std::cout << "Can't load " << scriptName << std::endl;
		return -1;
	}
	
	//bind modules
	Gfx::bindToLua(L);
	Snd::bindToLua(L);
	
	//set up modules
	Gfx::Graphics *gfxModule = new Gfx::Graphics(args);
	Snd::Sound *sndModule = new Snd::Sound(args);
	
	//initialize modules
	if(!gfxModule->init())
	{
		return -1;
	}
	
	//game loop
	while(true)
	{
		//before script execution
		gfxModule->clear();
		//update modules
		if(!gfxModule->update())
		{
			break;
		}
		
		//load & execute script
		if(luaL_loadfile(L,scriptName.c_str()))
		{
			std::cout << "Failed to reload " << scriptName << std::endl;
			return -1;
		}
		if(lua_pcall(L,0,0,0))
		{
			std::cout << "Failed to execute " << scriptName << std::endl;
			std::cout << lua_tostring(L,-1);//print error msg
			lua_pop(L,1);
			return -1;
		}
		
		//after script execution
		gfxModule->draw();
	}
	
	//clean up
	delete gfxModule;
	delete sndModule;
	
	lua_close(L);
	
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