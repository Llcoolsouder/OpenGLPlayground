#include "OpenGLManager.h"
#include "Window.h"

int main()
{
	bool Success = true;

	OpenGLManager *GLManager = OpenGLManager::Instance();
	Window MainWindow(16, 9, 100);
	MainWindow.Use();

	Success &= GLManager->InitGLEW();

	return Success ? 0 : 1;
}