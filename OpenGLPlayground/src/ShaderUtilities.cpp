#include "pch.h"

#include "ShaderUtilities.h"

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>


std::string LSShaderUtilities::LoadFile(const std::string& FilePath)
{
  std::ifstream File(FilePath);
  std::string FileContents;

  if (File.is_open())
  {
    std::stringstream Buffer;
    Buffer << File.rdbuf();
    FileContents = Buffer.str();
  }

  return FileContents;
}

GLuint LSShaderUtilities::LoadShader(const std::string& FilePath)
{
  std::size_t extensionPos = FilePath.rfind('.');
  std::string extension;

  if (extensionPos != std::string::npos)
  {
     extension =
      FilePath.substr(extensionPos, FilePath.length() - extensionPos);
  }
  else
  {
    std::cerr << "ERROR: Unable to get file extension. " << std::endl;
    exit(1);
  }
  
  GLenum ShaderType;
  if (extension == ".vs")
  {
    ShaderType = GL_VERTEX_SHADER;
  }
  else if (extension == ".gs")
  {
    ShaderType = GL_GEOMETRY_SHADER;
  }
  else if (extension == ".fs")
  {
    ShaderType = GL_FRAGMENT_SHADER;
  }
  else if (extension == ".cs")
  {
    ShaderType = GL_COMPUTE_SHADER;
  }
  else
  {
    std::cerr << "ERROR: Unrecognized shader extension." << std::endl;
    exit(1);
  }

  std::string ShaderSource = LSShaderUtilities::LoadFile(FilePath);
  GLint SourceLength = ShaderSource.length();
  GLchar* CShaderSource = (GLchar*)ShaderSource.c_str();
  GLuint ShaderID = glCreateShader(ShaderType);
  glShaderSource(ShaderID, 1, &CShaderSource, &SourceLength);
  glCompileShader(ShaderID);

  GLint SuccessfulCompilation;
  glGetObjectParameterivARB(ShaderID, GL_COMPILE_STATUS, &SuccessfulCompilation);
  if (!SuccessfulCompilation)
  {
    GLint LogLength,
      dummy;
    glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &LogLength);
    if (LogLength > 1)
    {
      GLchar* InfoLog = new GLchar[LogLength];
      glGetShaderInfoLog(ShaderID, LogLength, &dummy, InfoLog);
      std::cerr << InfoLog << std::endl;
      delete InfoLog;
    }
  }
  return ShaderID;  
}