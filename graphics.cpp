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
	//glfwWindowHint(GLFW_SAMPLES,16);
	
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
	glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE,&mMaxTBOSize);
	std::cout << "*Max Texture Buffer Size: " << mMaxTBOSize << std::endl;
	
	float vertices[] = {
		 -1.0f,  1.0f, // Top-left
		 1.0f,  1.0f,  // Top-right
		 1.0f, -1.0f,  // Bottom-right
		 -1.0f, -1.0f  // Bottom-left
	};
	
	GLuint elements[] = {0,1,2,
						 2,3,0};
					   
	glGenVertexArrays(1,&mVAO);
	glBindVertexArray(mVAO);
	
	glGenBuffers(1,&mVBO);
	glBindBuffer(GL_ARRAY_BUFFER,mVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	
	glGenBuffers(1,&mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(elements),elements,GL_STATIC_DRAW);
	
	float tboData[] = {1.0f, 0.0f, 0.0f,
					   0.0f, 1.0f, 0.0f, 
					   1.0f, 0.0f, 1.0f};
	
	glGenBuffers(1,&mTBO);
	glBindBuffer(GL_TEXTURE_BUFFER,mTBO);
	glBufferData(GL_TEXTURE_BUFFER,sizeof(tboData),tboData,GL_DYNAMIC_DRAW);
	glGenTextures(1,&mTBTEX);
	glBindBuffer(GL_TEXTURE_BUFFER,0);
	
	//pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(GLvoid*)0);
	
	glBindVertexArray(0);
	
	//setup shader
	mShader = new Shader("shaders/basic.vert","shaders/raytrace.frag");
	mShader->bind();
	
	//send resolution
	int width,height;
	glfwGetFramebufferSize(mWindow,&width,&height);
	std::cout << "X: " << width << " Y: " << height << std::endl;
	GLint screenResUni = glGetUniformLocation(mShader->mProgram,"screenRes");
	glUniform3f(screenResUni,800.0f,600.0f,0.0f);
	
	return true;
}

Graphics::~Graphics()
{
	delete mShader;
	glfwTerminate();
}

void Graphics::clear()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Graphics::draw()
{
	glBindVertexArray(mVAO);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_BUFFER,mTBTEX);
	glTexBuffer(GL_TEXTURE_BUFFER,GL_R32F,mTBO);
	GLint tboUni = glGetUniformLocation(mShader->mProgram,"tboTex");
	glUniform1i(tboUni,0);
	
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
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

void Graphics::setWindowTitle(std::string title)
{
	glfwSetWindowTitle(mWindow,(mWindowName+title).c_str());
}

double Graphics::getTime()
{
	return glfwGetTime();
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