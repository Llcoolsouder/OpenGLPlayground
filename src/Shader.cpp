#include "pch.h"

#include "Shader.h"
#include "ShaderUtilities.h"

#include <GL/glew.h>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>

//=============================================================================
//=============================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Shader::Shader(const std::vector<std::string>& Filenames)
{
  // Compile and link shaders
  std::vector<GLuint> ShaderIDs;
  std::for_each(
    Filenames.begin(),
    Filenames.end(),
    [&](const std::string filename)
  { ShaderIDs.push_back(LSShaderUtilities::LoadShader(filename)); });
  mProgramID = LSShaderUtilities::LinkProgram(ShaderIDs);

  // Delete shader stages
  std::for_each(
    ShaderIDs.begin(),
    ShaderIDs.end(),
    [&](GLuint id) { glDeleteShader(id); });
  ShaderIDs.clear();

  // Get all vertex attribute locations
  int NumSupAttribs = sizeof(SupportedVertexAttribs) / sizeof(SupportedVertexAttribs[0]);
  mVertexSize = 0;
  for (int i = 0; i < NumSupAttribs; i++)
  {
    ShaderParameter Attrib(SupportedVertexAttribs[i]);
    Attrib.Location = glGetAttribLocation(mProgramID, Attrib.Name);
    if (Attrib.Location != -1)
    {
      Attrib.Offset = mVertexSize;
      mVertexAttribs.insert(std::pair<std::string, ShaderParameter>(Attrib.Name, Attrib));
      mVertexSize += Attrib.NumItems * GetSizeofGLType(Attrib.TYPE);
    }
  }

  // Set all vertex attribute pointers
  std::for_each(
    mVertexAttribs.begin(),
    mVertexAttribs.end(),
    [this](const std::pair<std::string, ShaderParameter> Attrib) { SetVertexAttrib(Attrib); });

  // Get all uniforms
  int NumSupUniforms = sizeof(SupportedUniforms) / sizeof(SupportedUniforms[0]);
  for (int i = 0; i < NumSupUniforms; i++)
  {
    ShaderParameter uniform(SupportedUniforms[i]);
    uniform.Location = glGetUniformLocation(mProgramID, uniform.Name);
    if (uniform.Location != 1)
    {
      mUniforms.insert(std::pair<std::string, ShaderParameter>(uniform.Name, uniform));
    }
  }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Shader::~Shader()
{
  glDeleteProgram(mProgramID);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Shader::Use()
{
  glUseProgram(mProgramID);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool Shader::SetUniform(const std::string& name, const void* data)
{
  glUseProgram(mProgramID);
  std::map<std::string, ShaderParameter>::iterator iUniform = mUniforms.find(name);
  if (iUniform == mUniforms.end())
  {
    return false;
  }

  if (iUniform->second.TYPE == GL_FLOAT)
  {
    switch (iUniform->second.NumItems)
    {
      case(1): glUniform1f(iUniform->second.Location, *(GLfloat*)data); break;
      case(4): glUniform4fv(iUniform->second.Location, 1, (GLfloat*)data); break;
      case(16): glUniformMatrix4fv(iUniform->second.Location, 1, GL_FALSE, (GLfloat*)data); break;
      default:
      {
        std::cerr << "Shader module does not support " << iUniform->second.NumItems << " floats" << std::endl;
        return false;
      }
      return true;
    }
  }
  else
  {
    std::cerr << "The uniform type specified is not yet supported." << std::endl;
    return false;
  }
}

//=============================================================================
//=============================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Shader::SetVertexAttrib(std::pair<std::string, ShaderParameter> Attrib)
{
  glUseProgram(mProgramID);
  ShaderParameter param = Attrib.second;
  glVertexAttribPointer(
    param.Location,
    param.NumItems,
    param.TYPE,
    GL_FALSE,
    mVertexSize,
    reinterpret_cast<void*>(param.Offset));
  glEnableVertexAttribArray(param.Location);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int Shader::GetSizeofGLType(int type)
{
  static std::map<int, int> DataSizes =
  {
    {GL_FLOAT, sizeof(float)},
  };
  return  DataSizes[type];
}