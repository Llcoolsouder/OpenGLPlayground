/**
 * @file ShaderUtilities.h
 * 
 * Contains a set of functions helpful for loading, compiling, and linking shaders.
 *
 * @author Lonnie L. Souder II
 * @date 07/31/2019
 */

#pragma once

#include <GL/glew.h>

#include <string>
#include <vector>

/**
 * @defgroup LSShaderUtilities Shader Utilities
 * @{
 */

/**
 * Contains a set of functions that are helpfule for loading compiling and linking shaders.
 */
namespace LSShaderUtilities
{
  /**
   * Loads contents of a file into a string
   *
   * @param FilePath A string containing the path to the file
   * @return A string containing the contents of the entire file
   */
  std::string LoadFile(const std::string& FilePath);

  /**
   * Loads and compiles a GLSL shader
   *
   * @param FilePath  A string containing the path to the file
   *                  This function assumes the following file extensions:
   *                  Vertex Shader = ".vert"
   *                  Geometry Shader = ".geo"
   *                  Fragment Shader = ".frag"
   *                  Compute Shader = ".comp"
   * @return The ID of the compiled shader object
   */
  GLuint LoadShader(const std::string& FilePath);

  /**
   * Links a set of shaders to create a program
   * 
   * @param ShaderIDs A vector containing the IDs of all shaders to be linked to the program
   * @return The ID of the program
   */
  GLuint LinkProgram(std::vector<GLuint> ShaderIDs);
}

/** @} */