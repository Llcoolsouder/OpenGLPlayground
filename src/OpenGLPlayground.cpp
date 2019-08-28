/**
 * @file OpenGLPlayground.cpp
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
#include "pch.h"

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <math.h>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderUtilities.h"
#include "Shader.h"
#include "Camera.h"

void cleanup()
{
  glfwTerminate();
  getchar();
}

void kill()
{
  cleanup();
  exit(1);
}

int main()
{
  GLFWwindow* window;

  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW library" << std::endl;
    kill();
    return -1;
  }

  //Window creation
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
    kill();
    return -1;
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

  glClearColor(0.05f, 0.05f, 0.1f, 1.0f);

  glm::vec3  vertices[] =
  {{-0.5f, -0.5f, 0.0f},
  {0.5f, -0.5f, 0.0f},
  {0.0f,  0.5f, 0.0f}};

  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  const std::string ShaderFolder = "../shaders/";
  std::vector<std::string> ShaderFiles;
  ShaderFiles.push_back(ShaderFolder + "solid.vert");
  ShaderFiles.push_back(ShaderFolder + "solid.frag");
  Shader TriangleShader(ShaderFiles);

  // Timer
  std::chrono::system_clock::time_point FrameStart;
  float deltaTime = 0.0f;
  float uTime = 0.0f;
  const float zero = 0.0f;

  // Shader Const uniforms
  glm::vec4 triangle_uColor = { 0.6f, 0.0f, 1.0f, 1.0f };

  // Camera Setup
  glm::mat4 viewMat = glm::lookAt(
    glm::vec3(0.0f, 0.0f, -20.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
  );
  glm::mat4 projMat = glm::perspective(
    glm::radians(100.0f),
    std::get<0>(AspectRatio) / std::get<1>(AspectRatio),
    0.01f,
    1000.0f);
  Camera mainCamera(viewMat, projMat);

  TriangleShader.Use();
  TriangleShader.SetUniform("uvProjMatrix", &mainCamera.GetProjMatrix());
  TriangleShader.SetUniform("uvViewMatrix", &mainCamera.GetViewMatrix());


  while (!glfwWindowShouldClose(window))
  {
    FrameStart = std::chrono::system_clock::now();

    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw Triangle
    TriangleShader.Use();
    TriangleShader.SetUniform("uColor", &triangle_uColor);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    TriangleShader.SetAllVertexAttribPointers();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();

    deltaTime = (float)(std::chrono::duration_cast<std::chrono::milliseconds>
      (std::chrono::system_clock::now() - FrameStart).count()) / 1000.0f;
    //std::cout << deltaTime << std::endl;
    uTime += deltaTime;
  }

  cleanup();
  return 0;
}
