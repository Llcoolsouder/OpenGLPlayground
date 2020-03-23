/**
 * @file Sandbox.cpp
 * @mainpage OpenGL Playground
 *
 * @section Summary
 * This project serves as a sandbox in which to learn and practice OpenGL
 *
 * @section Main Topics
 * The focus of these exercises will be in understanding high-performance
 * computing and some computer graphics, thus the topics will include:
 * - Compute Shaders
 * - Multi-pass rendering
 * - Fluid simulation on the GPU
 *
 * @section My Method
 * Everything will be done the hard way first (i.e. type out ALLL the code).
 * Functionality will only be abstracted to a class or function when it is
 * fully understood. As a test, when abstracting, I will not be looking at
 * the code that I am *essentially* copying. This should give me one last
 * chance to type out the code while focusing on what it does and how it
 * works--and of course this is also good for memory.
 *
 * @author Lonnie L. Souder II
 * @date 07/31/2019
 */

#include "OpenGLManager.h"
#include "Window.h"
#include "ShaderUtilities.h"
//#include "Shader.h"
//#include "Mesh.h"
#include "Camera.h"
#include "Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <math.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <vector>

int main()
{
	OpenGLManager* GLManager = OpenGLManager::Instance();

	Window MainWindow(16, 9, 100);
	MainWindow.Use();

	GLManager->InitGLEW();

	glClearColor(0.05f, 0.05f, 0.1f, 1.0f);

	// Camera Setup
	glm::mat4 viewMat = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projMat = glm::perspective(
		glm::radians(100.0f),
		MainWindow.GetAspectRatio(),
		0.01f,
		1000.0f);
	Camera mainCamera(viewMat, projMat);

	// Create Mesh
	std::vector<glm::vec3> vertices = { { -0.5f, -0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ 0.0f, 0.5f, 0.0f } };

	std::vector<unsigned int> indices = {
		0, 1, 2
	};

	std::shared_ptr<Mesh> pTriangleMesh = std::make_shared<Mesh>(vertices, indices);

	// Create shader program
	const std::string ShaderFolder = "../../../shaders/";
	std::vector<std::string> ShaderFiles;
	ShaderFiles.push_back(ShaderFolder + "solid.vert");
	ShaderFiles.push_back(ShaderFolder + "solid.frag");
	std::shared_ptr<Shader> pTriangleShader = std::make_shared<Shader>(ShaderFiles);

	// Shader uniforms (Note mutability)
	std::shared_ptr<glm::vec4> puColor =
		std::make_shared<glm::vec4>(0.6f, 0.0f, 1.0f, 1.0f);

	std::shared_ptr<glm::mat4> puvModelMatrix =
		std::make_shared<glm::mat4>(1.0f);

	std::shared_ptr<const glm::mat4> puvViewMatrix = mainCamera.GetViewMatrix();
	std::shared_ptr<const glm::mat4> puvProjMatrix = mainCamera.GetProjMatrix();
	std::vector<Model::UniformData> TriangleUniforms = {
		Model::UniformData("uColor", puColor),
		Model::UniformData("uvModelMatrix", puvModelMatrix),
		Model::UniformData("uvViewMatrix", puvViewMatrix),
		Model::UniformData("uvProjMatrix", puvProjMatrix)
	};

	// Model setup
	Model Triangle(pTriangleMesh, pTriangleShader, TriangleUniforms);

	// Timer
	std::chrono::system_clock::time_point FrameStart;
	float deltaTime = 0.0f;
	float uTime = 0.0f;

	//*****************************************************************************
	// Main Loop
	//*****************************************************************************
	while (!MainWindow.WindowShouldClose())
	{
		FrameStart = std::chrono::system_clock::now();

		glClear(GL_COLOR_BUFFER_BIT);

		*puvModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(std::sin(uTime), 0.0, 0.0));
		*puvModelMatrix = glm::rotate(*puvModelMatrix, glm::radians(45.0f) * uTime, glm::vec3(0, 1, 0));

		// Draw Triangle
		Triangle.Update();
		Triangle.Draw();

		glUseProgram(0);
		glBindVertexArray(0);

		MainWindow.SwapBuffers();
		GLManager->PollEvents();

		deltaTime = (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - FrameStart).count()) / 1000000000.0f;
		//std::cout << deltaTime << std::endl;
		uTime += deltaTime;
	}

	return 0;
}
