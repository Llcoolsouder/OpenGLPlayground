/**
 * @file ParticleSystem.h
 *
 * Handles particle system data and drawing using compute shaders
 *
 * @author Lonnie L. Souder II
 * @date 08/27/2019
 */

#pragma once

#include <GL/glew.h>

#include <map>
#include <vector>
#include <string>

class ParticleSystem
{
public:
  ParticleSystem() = delete;

  ParticleSystem(
    GLuint RenderShaderProgramID,
    GLuint ComputeShaderProgramID,
    std::vector<std::string> BufferNames);  // Do I need bufferNames or just ID's???
  
  ~ParticleSystem();

  void Draw();

private:

  void Update();

  void Render();

private:
  unsigned int mNumParticles;

  GLuint mRenderShaderProgramID;
  GLuint mComputeShaderProgramID;

  std::map<std::string, GLuint> mBuffers;
};
