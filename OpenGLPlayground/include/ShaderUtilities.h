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
 *                  Vertex Shader = ".vs"
 *                  Geometry Shader = ".gs"
 *                  Fragment Shader = ".fs"
 *                  Compute Shader = ".cs"
 * @return The ID of the compiled shader object
 */
  GLuint LoadShader(const std::string& FilePath);
}

/** @} */