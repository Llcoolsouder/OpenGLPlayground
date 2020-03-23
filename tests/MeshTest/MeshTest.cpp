#include <OpenGLManager.h>
#include <Window.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <../include/Mesh.h>

int main()
{
	// TODO: This is NOT a good test. It's only here to see how CodeCov reacts for now
	try
	{
		OpenGLManager *GLManager = OpenGLManager::Instance();

		Window MainWindow(16, 9, 100);
		MainWindow.Use();

		GLManager->InitGLEW();

		std::vector<glm::vec3> aPositions =
		{
			{0.0f, 0.5f, 0.0f},
			{-0.5f, -0.5f, 0.0f},
			{0.5f, -0.5f, 0.0f}
		};
		std::vector<unsigned int> Indices = {0, 1, 2};
		std::vector<glm::vec4> aColors =
		{
			{1.0f, 0.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f, 1.0f}
		};
		Mesh mesh(aPositions, Indices, aColors);
		mesh.Bind();
	}
	catch(std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
