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
	
	mWindow = glfwCreateWindow(mScreenWidth,mScreenHeight,mWindowName.c_str(),NULL,NULL);
	glfwMakeContextCurrent(mWindow);
	
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize" << std::endl;
		std::cout << glewGetErrorString(err) << std::endl;
		return false;
	}
	
	glClearColor(CLEAR_COLOR);
	
	std::cout << "*Openg GL Version: " << glGetString(GL_VERSION) << std::endl;
	
	//create fullscreen quad - this contains verts and uvs
	float quadVerts[] = {1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
						 -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
						 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
						 -1.0f, -1.0f, 0.0f, 0.0f, 0.0f};
					   
	glGenVertexArrays(1,&mVAO);
	glBindVertexArray(mVAO);
	
	glGenBuffers(1,&mVBO);
	glBindBuffer(GL_ARRAY_BUFFER,mVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(quadVerts),quadVerts,GL_STATIC_DRAW);
	
	//pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,GL_FLOAT*5,(GLvoid*)0);
	
	//uv
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,GL_FLOAT*5,(GLvoid*)3);
	
	glBindVertexArray(0);
	
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
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES,0,3);
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