#include "OpenGLManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

OpenGLManager* OpenGLManager::mpInstance = nullptr;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
OpenGLManager::OpenGLManager()
{
	InitializeOpenGL();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
OpenGLManager::~OpenGLManager()
{
	CleanupGLFW();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
OpenGLManager* OpenGLManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new OpenGLManager();
	}
	return mpInstance;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OpenGLManager::PollEvents()
{
	glfwPollEvents();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool OpenGLManager::InitializeOpenGL() const
{
	return InitGLFW();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool OpenGLManager::InitGLFW() const
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW library" << std::endl;
		return false;
	}
	return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool OpenGLManager::InitGLEW() const
{
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize OpenGL" << std::endl;
		return false;
	}

	if (glewIsSupported("GL_VERSION_4_3"))
	{
		std::cout << " Version 4.3 supported!" << std::endl;
	}
	else if (glewIsSupported("GL_VERSION_4_1"))
	{
		std::cout << "Version 4.1 supported" << std::endl;
	}
	else
	{
		std::cout << "Maybe we should update the drivers" << std::endl;
	}
	return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void OpenGLManager::CleanupGLFW() const
{
	glfwTerminate();
}