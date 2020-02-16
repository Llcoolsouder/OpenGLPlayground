#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW library" << std::endl;
			return 1;
		}

		//Window creation
		GLFWwindow *window;
		const std::tuple<float, float> AspectRatio = std::tuple<float, float>(16.0f, 9.0f);
		const int WindowSize = 100;
		window = glfwCreateWindow(
			WindowSize * std::get<0>(AspectRatio),
			WindowSize * std::get<1>(AspectRatio),
			"OpenGL Playground", NULL, NULL);
		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "Failed to initialize OpenGL" << std::endl;
			glfwTerminate();
			return 1;
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
