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

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderUtilities.h"

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

  window = glfwCreateWindow(1024, 768, "OpenGL Playground", NULL, NULL);
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

  float vertices[] = {
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
  };

  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  const std::string ShaderFolder = "./shaders/";
  GLuint VertexShaderID = LSShaderUtilities::LoadShader(ShaderFolder + "solid.vs");
  GLuint FragmentShaderID = LSShaderUtilities::LoadShader(ShaderFolder + "solid.fs");
  std::vector<GLuint> ShaderIDs = { VertexShaderID, FragmentShaderID };
  GLuint ShaderProgramID = LSShaderUtilities::LinkProgram(ShaderIDs);
  for_each(
    ShaderIDs.begin(),
    ShaderIDs.end(),
    [](GLuint& ShaderID) { glDeleteShader(ShaderID); });
  ShaderIDs.clear();

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Compute Shader setup
  const unsigned int NUM_PARTICLES = 256 * 1024;
  GLint BufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

  GLuint computePosBufID;
  glGenBuffers(1, &computePosBufID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, computePosBufID);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * 3 * sizeof(float), NULL, GL_STATIC_DRAW);
  float* ComputePoints = (float*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * 3 * sizeof(float), BufMask);
  for (unsigned int i = 0; i < NUM_PARTICLES * 3; i+=3)
  {
    ComputePoints[i] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputePoints[i + 1] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputePoints[i + 2] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
  }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  GLuint computeVelBufID;
  glGenBuffers(1, &computeVelBufID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, computeVelBufID);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * 3 * sizeof(float), NULL, GL_STATIC_DRAW);
  float* ComputeVelocities = (float*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * 3 * sizeof(float), BufMask);
  for (unsigned int i = 0; i < NUM_PARTICLES * 3; i += 3)
  {
    ComputeVelocities[i]      = -0.00000000001f;//  static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputeVelocities[i + 1]  = 0.0f;// static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputeVelocities[i + 2]  = 0.0f;// static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
  }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  GLuint computeColorBufID;
  glGenBuffers(1, &computeColorBufID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, computeColorBufID);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * 4 * sizeof(float), NULL, GL_STATIC_DRAW);
  float* ComputeColors = (float*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * 4 * sizeof(float), BufMask);
  for (unsigned int i = 0; i < NUM_PARTICLES * 4; i += 4)
  {
    ComputeColors[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    ComputeColors[i + 1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    ComputeColors[i + 2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    ComputeColors[i + 3] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  GLuint ComputeShader = LSShaderUtilities::LoadShader(ShaderFolder + "particle.cs");
  std::vector<GLuint> ComputeShaderIDs = { ComputeShader };
  GLuint ComputeProgramID = LSShaderUtilities::LinkProgram(ComputeShaderIDs);
  glDeleteShader(ComputeShader);
  ComputeShaderIDs.clear();

  const unsigned int WORK_GROUP_SIZE = 1024;
  const GLuint NUM_WORK_GROUPS = NUM_PARTICLES / WORK_GROUP_SIZE;

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, computePosBufID);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, computeVelBufID);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, computeColorBufID);
    glUseProgram(ComputeProgramID);
    glDispatchCompute(NUM_WORK_GROUPS, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glUseProgram(ShaderProgramID);
    glBindBuffer(GL_ARRAY_BUFFER, computePosBufID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_POINTS, 0, NUM_PARTICLES * 3);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  cleanup();
  return 0;
}
