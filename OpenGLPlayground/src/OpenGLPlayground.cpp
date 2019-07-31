/* OpenGLPlayground.cpp
*
* Author: Lonnie Souder II
* Date:   07/25/2019
*/
#include "pch.h"

#include <iostream>
#include <string>
#include <random>

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

  window = glfwCreateWindow(1024, 512, "OpenGL Playground", NULL, NULL);
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Failed to initialize OpenGL" << std::endl;
    kill();
    return -1;
  }

  glClearColor(0.15f, 0.15f, 0.2f, 1.0f);

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

  const std::string ShaderFolder = "./shaders/";
  GLuint VertexShaderID = LSShaderUtilities::LoadShader(ShaderFolder + "solid.vs");

  std::string FragmentShaderText = LSShaderUtilities::LoadFile(ShaderFolder + "solid.fs");
  const char* FragmentShaderTextC = FragmentShaderText.c_str();
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(
    FragmentShaderID,
    1,
    &FragmentShaderTextC,
    NULL);
  glCompileShader(FragmentShaderID);

  GLint FragmentShaderCompileStatus;
  glGetObjectParameterivARB(FragmentShaderID, GL_COMPILE_STATUS, &FragmentShaderCompileStatus);
  if (!FragmentShaderCompileStatus)
  {
    GLint LogLength;
    GLint temp;
    glGetProgramiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &LogLength);
    if (LogLength > 1)
    {
      GLchar* FragmentShaderCompilerLog = new GLchar[LogLength];
      glGetInfoLogARB(FragmentShaderID, LogLength, &temp, FragmentShaderCompilerLog);
      std::cerr << FragmentShaderCompilerLog << std::endl;
      delete FragmentShaderCompilerLog;
    }
  }

  GLuint ShaderProgramID = glCreateProgram();
  glAttachObjectARB(ShaderProgramID, VertexShaderID);
  glAttachShader(ShaderProgramID, FragmentShaderID);
  glLinkProgram(ShaderProgramID);

  GLint LinkerStatus;
  glGetObjectParameterivARB(ShaderProgramID, GL_LINK_STATUS, &LinkerStatus);
  if (!LinkerStatus)
  {
    GLint LogLength;
    GLint temp;
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &LogLength);
    if (LogLength > 1)
    {
      GLchar* LinkerLog = new GLchar[LogLength];
      glGetInfoLogARB(FragmentShaderID, LogLength, &temp, LinkerLog);
      std::cerr << LinkerLog << std::endl;
      delete LinkerLog;
    }
  }

  glUseProgram(ShaderProgramID);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  const int NUM_PARTICLES = 1024*1024;

  // Compute Shader setup
  GLint BufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

  GLuint computePosBufID;
  glGenBuffers(1, &computePosBufID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, computePosBufID);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * 3 * sizeof(float), NULL, GL_STATIC_DRAW);
  float* ComputePoints = (float*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * 3 * sizeof(float), BufMask);
  for (unsigned int i = 0; i < NUM_PARTICLES * 3; i+=3)
  {
    ComputePoints[i] = static_cast<float>(rand());
    ComputePoints[i + 1] = static_cast<float>(rand());
    ComputePoints[i + 2] = static_cast<float>(rand());
  }
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);

  GLuint computeVelBufID;
  glGenBuffers(1, &computeVelBufID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, computeVelBufID);
  glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * 3 * sizeof(float), NULL, GL_STATIC_DRAW);
  float* ComputeVelocities = (float*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * 3 * sizeof(float), BufMask);
  for (unsigned int i = 0; i < NUM_PARTICLES * 3; i += 3)
  {
    ComputeVelocities[i] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 10.f);
    ComputeVelocities[i + 1] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 10.f);
    ComputeVelocities[i + 2] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 10.f);
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

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, computePosBufID);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, computeVelBufID);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, computeColorBufID);

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 9);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  cleanup();
  return 0;
}
