#include <iostream>
#include <lua.hpp>
#include <oolua.h>
#include <map>
#include <vector>
#include <cstring>
#include <sstream>

#include "graphics.h"
#include "sound.h"
#include "entity.h"

#define FPS_TRACK_DELAY 0.5

//global variables
struct Variables
{
	bool isSetupPhase;
} GVar;

lua_State *L;

std::vector<Entity*> ENTITIES;

std::map<char, char*> parseArguments(int argc, char* argv[]);
void bindToLua();

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
	
	bindToLua();
	
	if(luaL_loadfile(L,scriptName.c_str()))
	{
		std::cout << "Can't load " << scriptName << std::endl;
		return -1;
	}
	
	//set up modules
	Graphics *gfxModule = new Graphics(args);
	gfxModule->bindToLua(L,gfxModule);
	
	//Snd::Sound *sndModule = new Snd::Sound(args);
	
	//initialize modules
	if(!gfxModule->init())
	{
		return -1;
	}
	
	//game loop
	double lastTime = gfxModule->getTime();
	double currentTime = lastTime;
	double timeSinceUpdateFPS = FPS_TRACK_DELAY;
	
	//in case we want to run some setup code in the lua script
	GVar.isSetupPhase = true;
	OOLUA::set_global(L,"isSetupPhase",GVar.isSetupPhase);
	
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
		
		//so that we don't repeat any setup code
		if(GVar.isSetupPhase)
		{
			GVar.isSetupPhase = false;
			OOLUA::set_global(L,"isSetupPhase",GVar.isSetupPhase);
		}
		
		//after script execution
		gfxModule->draw();
		gfxModule->swap();
		
		//check performances
		lastTime = currentTime;
		currentTime = gfxModule->getTime();
		
		float deltaTime = currentTime-lastTime;
		
		//update fps in window title
		timeSinceUpdateFPS += deltaTime;
		if(timeSinceUpdateFPS >= FPS_TRACK_DELAY)
		{
			timeSinceUpdateFPS = 0.0;
			float fps = 1.0f/deltaTime;
			std::stringstream ss;
			ss	<< " FPS: " << fps;
			gfxModule->setWindowTitle(ss.str());
		}
	}
	
	//clean up
	for(std::vector<Entity*>::iterator it = ENTITIES.begin() ; it != ENTITIES.end() ; it++)
	{
		delete *it;
	}
	ENTITIES.clear();
	
	delete gfxModule;
	//delete sndModule;
	
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
			i++;//skip ahead one index to get the argument value
			if(i < argc)
			{
				result[argv[i-1][1]] = argv[i];
			}
		}
	}
	
	return std::map<char,char*>(result);
}

void bindToLua()
{
	
};