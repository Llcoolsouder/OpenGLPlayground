#include "Window.h"
#include "OpenGLManager.h"

#include <iostream>

int main()
{
	OpenGLManager *GLManager = OpenGLManager::Instance();

	Window Window1(16, 9, 10);
	Window Window2(2, 1, 1);
	Window Window3(1, 4, 1);

	constexpr float AspectRatio1 = 16.0 / 9.0;
	constexpr float AspectRatio2 = 2.0;
	constexpr float AspectRatio3 = 0.25;

	if (AspectRatio1 != Window1.GetAspectRatio())
		return 1;
	if (AspectRatio2 != Window2.GetAspectRatio())
		return 1;
	if (AspectRatio3 != Window3.GetAspectRatio())
		return 1;

	try
	{
		Window1.Use();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	GLManager->InitGLEW();

	try
	{
		Window1.SwapBuffers();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}