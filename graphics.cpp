#include "graphics.h"


Gfx::Graphics::Graphics(std::map<char,char*> args)
{
	
}

bool Gfx::Graphics::init()
{
	if(!glfwInit())
	{
		return false;
	}
	
	mWindow = glfwCreateWindow(800,600,"Test",NULL,NULL);
	
	
	return true;
}

Gfx::Graphics::~Graphics()
{
	glfwTerminate();
}