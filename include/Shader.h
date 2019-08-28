/**
 * @file Shader.h
 *
 * Describes a class that handles shaders
 *
 * @author Lonnie L. Souder II
 * @date 08/29/19
 */

#pragma once

#include <GL/glew.h>

#include <vector>
#include <string>
#include <map>

class Shader
{
public:

  Shader() = delete;
  Shader(const Shader& rhs) = delete;

  /**
   * Loads, compiles, and links a shader program
   * from the files given by Filenames
   *
   * @param Filenames Paths to GLSL shader files
   */
  Shader(const std::vector<std::string>& Filenames);

  /**
   * Deletes the program
   */
  ~Shader();

  /**
   * Binds shader program to context
   */
  void Use();

  /**
   * Sets a uniform to a given value
   *
   * @param name Name of the uniform from shader source
   * @param data Pointer to data
   *
   * @return true if successful, else false
   */
  bool SetUniform(const std::string& name, const void* data);

private:

  struct ShaderParameter
  {
    char Name[16];  /// Data name from shader source
    int TYPE; /// Data type
    unsigned int NumItems;  /// How many datum make up this object
    GLint Location;  /// Location in shader program
    int Offset; /// Offset in interleaved vertex buffer
  };

  void SetVertexAttrib(const std::pair<std::string, ShaderParameter> Attrib);

  int GetSizeofGLType(int type);

private:
  GLuint mProgramID;
  std::map<std::string, ShaderParameter> mVertexAttribs;
  std::map<std::string, ShaderParameter> mUniforms;
  int mVertexSize;

  /// Defines supported vertex attribute names
  constexpr static ShaderParameter SupportedVertexAttribs[] = 
  {
    {"aPosition", GL_FLOAT, 3, NULL, NULL},
    {"aColor",    GL_FLOAT, 4, NULL, NULL},
  };

  /// Defines supported shader uniforms
  constexpr static ShaderParameter SupportedUniforms[] =
  {
    {"uvModelMatrix", GL_FLOAT, 16, NULL, 0},
    {"uvViewMatrix",  GL_FLOAT, 16, NULL, 0},
    {"uvProjMatrix",  GL_FLOAT, 16, NULL, 0},
    {"uColor",        GL_FLOAT, 4,  NULL, 0},
    {"ugModelMatrix", GL_FLOAT, 16, NULL, 0},
    {"ugViewMatrix",  GL_FLOAT, 16, NULL, 0},
    {"ugProjMatrix",  GL_FLOAT, 16, NULL, 0},
  };
};