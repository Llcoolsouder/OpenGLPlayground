#include "Window.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Window::Window(
	const int& AspectRatioWidth,
	const int& AspectRationHeight,
	const int &Scale,
	const std::string& Title) :
		mpGLManager(OpenGLManager::Instance()),
		mpWindow(nullptr),
		mAspectRatio(std::make_tuple(AspectRatioWidth, AspectRationHeight)),
		mScale(Scale)
{
	mpWindow = glfwCreateWindow(
		mScale * std::get<0>(mAspectRatio),
		mScale * std::get<1>(mAspectRatio),
		Title.c_str(), NULL, NULL);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Window::~Window()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Window::Use()
{
	glfwMakeContextCurrent(mpWindow);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool Window::WindowShouldClose() const
{
	return glfwWindowShouldClose(mpWindow);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Window::SwapBuffers() const
{
	glfwSwapBuffers(mpWindow);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
float Window::GetAspectRatio() const
{
	return std::get<0>(mAspectRatio) / std::get<1>(mAspectRatio);
}