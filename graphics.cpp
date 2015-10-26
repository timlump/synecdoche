#include "graphics.h"


Gfx::Graphics::Graphics(std::map<char,char*> args)
{
	std::map<char,char*>::iterator it;
	
	
	//get screen size from argss
	if((it = args.find('x'))!=args.end())
	{
		mScreenWidth = atoi(it->second);
	}
	else
	{
		mScreenWidth = DEFAULT_SCREEN_WIDTH;
	}
	if((it = args.find('y'))!=args.end())
	{
		mScreenHeight = atoi(it->second);
	}
	else{
		mScreenHeight = DEFAULT_SCREEN_HEIGHT;
	}
	
	if((it = args.find('n'))!=args.end())
	{
		mWindowName = std::string(it->second);
	}
	else
	{
		mWindowName = "Synecdoche";
	}
}

bool Gfx::Graphics::init()
{
	if(!glfwInit())
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		return false;
	}
	
	glewExperimental = GL_TRUE;
	if(!glewInit())
	{
		std::cout << "GLEW failed to initialize" << std::endl;
		return false;
	}
	
	mWindow = glfwCreateWindow(mScreenWidth,mScreenHeight,mWindowName.c_str(),NULL,NULL);
	
	
	return true;
}

Gfx::Graphics::~Graphics()
{
	glfwTerminate();
}

void Gfx::Graphics::clear()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Gfx::Graphics::draw()
{
	glfwSwapBuffers(mWindow);
}

bool Gfx::Graphics::update()
{
	glfwPollEvents();
	if(glfwWindowShouldClose(mWindow))
	{
		std::cout << "GLFW window closed, shutting down" << std::endl;
		return false;
	}
	
	return true;
}