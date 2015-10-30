#include "graphics.h"
#include <oolua.h>

Graphics::Graphics(std::map<char,char*> args)
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
	
	//change window title
	if((it = args.find('n'))!=args.end())
	{
		mWindowName = std::string(it->second);
	}
	else
	{
		mWindowName = "Synecdoche";
	}
}

bool Graphics::init()
{
	if(!glfwInit())
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		return false;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES,16);
	
	glewExperimental = GL_TRUE;
	if(!glewInit())
	{
		std::cout << "GLEW failed to initialize" << std::endl;
		return false;
	}
	
	mWindow = glfwCreateWindow(mScreenWidth,mScreenHeight,mWindowName.c_str(),NULL,NULL);
	glfwMakeContextCurrent(mWindow);
	
	glClearColor(CLEAR_COLOR);
	
	std::cout << "*Openg GL Version: " << glGetString(GL_VERSION) << std::endl;
	
	//create fullscreen quad
	float[] quadVerts = {1.0f, 1.0f, 0.0f,
						 -1.0f, 1.0f, 0.0f,
						 1.0f, -1.0f, 0.0f,
						 -1.0f, -1.0f, 0.0f};
						 
	float[] quadUVs = {1.0f, 1.0f,
					   0.0f, 1.0f,
					   1.0f, 0.0f,
					   0.0f, 0.0f};
					   
	glGenVertexArrays(1,&mVAO);
	glBindVertexArray(mVAO);
	
	glGenBuffers(1,&mVBO);
	//to finish - https://github.com/timlump/SpaceRace/blob/init/SpaceRace/SpaceRace/Mesh.cpp
	
	return true;
}

Graphics::~Graphics()
{
	glfwTerminate();
}

void Graphics::clear()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Graphics::draw()
{
	glfwSwapBuffers(mWindow);
}

bool Graphics::update()
{
	glfwPollEvents();
	if(glfwWindowShouldClose(mWindow))
	{
		std::cout << "GLFW window closed, shutting down" << std::endl;
		return false;
	}
	
	return true;
}

Graphics* Graphics::getInstance()
{
	return mInstance;
}

OOLUA_PROXY(Graphics)
	OOLUA_TAGS(No_default_constructor)
	OOLUA_SFUNC(getInstance)
OOLUA_PROXY_END

OOLUA_EXPORT_NO_FUNCTIONS(Graphics)

Graphics* Graphics::mInstance = NULL;

void Graphics::bindToLua(lua_State *L,Graphics* ptr)
{
	std::cout << "*Binding Graphics module with LUA" << std::endl;
	OOLUA::register_class<Graphics>(L);
	OOLUA::register_class_static<Graphics>(L,"getInstance",&OOLUA::Proxy_class<Graphics>::getInstance);
	
	if(ptr)
	{
		Graphics::mInstance = ptr;
	}
}