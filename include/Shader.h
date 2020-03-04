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

#include <map>
#include <string>
#include <vector>

class Shader
{
public:
	Shader() = delete;
	Shader(const Shader &other) = delete;

	/**
   * Loads, compiles, and links a shader program
   * from the files given by Filenames
   *
   * @param Filenames Paths to GLSL shader files
   */
	Shader(const std::vector<std::string> &Filenames);

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
	bool SetUniform(const std::string &name, const void *data);

	/**
   * Sets all vertex attribute pointers to their places
   * in the currently bound vertex buffer. This assumes that
   * the currently bound buffer is an interleaved buffer
   * containing ALL of the attributes specified in this shader.
   * NOTE: This MUST be called after a new buffer is bound.
   */
	void SetAllVertexAttribPointers();

private:
	struct ShaderParameter
	{
		char Name[16]; /// Data name from shader source
		int TYPE; /// Data type
		unsigned int NumItems; /// How many datum make up this object
		GLint Location; /// Location in shader program
		int Offset; /// Offset in interleaved vertex buffer
	};

	void SetVertexAttribPointer(const std::pair<std::string, ShaderParameter> Attrib);

	int GetSizeofGLType(int type);

private:
	GLuint mProgramID;
	std::map<std::string, ShaderParameter> mVertexAttribs;
	std::map<std::string, ShaderParameter> mUniforms;
	int mVertexSize;

	/// Defines supported vertex attribute names
	static constexpr ShaderParameter mSupportedVertexAttribs[];

	/// Defines supported shader uniforms
	static constexpr ShaderParameter mSupportedUniforms[];
};
