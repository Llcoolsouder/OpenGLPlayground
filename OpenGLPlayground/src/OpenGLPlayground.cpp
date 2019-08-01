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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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

  const std::string ShaderFolder = "./shaders/";
  GLuint VertexShaderID = LSShaderUtilities::LoadShader(ShaderFolder + "solid.vert");
  GLuint FragmentShaderID = LSShaderUtilities::LoadShader(ShaderFolder + "solid.frag");
  std::vector<GLuint> ShaderIDs = { VertexShaderID, FragmentShaderID };
  GLuint ShaderProgramID = LSShaderUtilities::LinkProgram(ShaderIDs);
  for_each(
    ShaderIDs.begin(),
    ShaderIDs.end(),
    [](GLuint& ShaderID) { glDeleteShader(ShaderID); });
  ShaderIDs.clear();

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  // Compute Shader setup
  const unsigned int NUM_PARTICLES = 256 * 1024;
  GLint BufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

  GLuint computePosBufID;
  glGenBuffers(1, &computePosBufID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, computePosBufID);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
  glm::vec4* ComputePoints = (glm::vec4*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(glm::vec4), BufMask);
  for (unsigned int i = 0; i < NUM_PARTICLES; i++)
  {
    ComputePoints[i].x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputePoints[i].y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputePoints[i].z = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputePoints[i].w = 1.0f;
  }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  GLuint computeVelBufID;
  glGenBuffers(1, &computeVelBufID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, computeVelBufID);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
  glm::vec4* ComputeVelocities = (glm::vec4*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(glm::vec4), BufMask);
  for (unsigned int i = 0; i < NUM_PARTICLES; i ++)
  {
    ComputeVelocities[i].x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputeVelocities[i].y = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputeVelocities[i].z = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f;
    ComputeVelocities[i].w = 0.0f;
  }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  GLuint computeColorBufID;
  glGenBuffers(1, &computeColorBufID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, computeColorBufID);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
  glm::vec4* ComputeColors = (glm::vec4*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(glm::vec4), BufMask);
  for (unsigned int i = 0; i < NUM_PARTICLES; i++)
  {
    ComputeColors[i].x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    ComputeColors[i].y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    ComputeColors[i].z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    ComputeColors[i].w = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  GLuint ComputeShader = LSShaderUtilities::LoadShader(ShaderFolder + "particle.comp");
  std::vector<GLuint> ComputeShaderIDs = { ComputeShader };
  GLuint ComputeProgramID = LSShaderUtilities::LinkProgram(ComputeShaderIDs);
  glDeleteShader(ComputeShader);
  ComputeShaderIDs.clear();

  const unsigned int WORK_GROUP_SIZE = 1024;
  const GLuint NUM_WORK_GROUPS = NUM_PARTICLES / WORK_GROUP_SIZE;

  // Timer
  std::chrono::system_clock::time_point FrameStart;
  float deltaTime = 0.0f;
  float uTime = 0.0f;
  const float zero = 0.0f;

  // Shader Const uniforms
  glm::vec4 particle_uColor = { 0.0f, 0.0f, 0.0f, 0.0f };
  glm::vec4 triangle_uColor = { 1.0f, 1.0f, 1.0f, 1.0f };

  while (!glfwWindowShouldClose(window))
  {
    FrameStart = std::chrono::system_clock::now();

    particle_uColor.r = 0.5f * (std::sin(uTime) + 1);
    particle_uColor.b = 0.5f * (std::cos(uTime) + 1);

    glClear(GL_COLOR_BUFFER_BIT);

    // Compute particles
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, computePosBufID);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, computeVelBufID);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, computeColorBufID);
    glUseProgram(ComputeProgramID);
    glUniform1fv(glGetUniformLocation(ComputeProgramID, "dT"), 1, &deltaTime);
    std::cout << "uniform loc: " << glGetUniformLocation(ComputeProgramID, "dT") << std::endl;
    glDispatchCompute(NUM_WORK_GROUPS, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glUseProgram(ShaderProgramID);

    // Draw particles
    glUniform4fv(glGetUniformLocation(ShaderProgramID, "uColor"), 1, (GLfloat*)&particle_uColor);
    glBindBuffer(GL_ARRAY_BUFFER, computePosBufID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);

    // Draw Triangle
    glUniform4fv(glGetUniformLocation(ShaderProgramID, "uColor"), 1, (GLfloat*)&triangle_uColor);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();

    deltaTime = (float)(std::chrono::duration_cast<std::chrono::milliseconds>
      (std::chrono::system_clock::now() - FrameStart).count()) / 1000.0f;
    std::cout << deltaTime << std::endl;
    uTime += deltaTime;
  }

  cleanup();
  return 0;
}
