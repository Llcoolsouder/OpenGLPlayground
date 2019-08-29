#include "Mesh.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

//=============================================================================
//=============================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Mesh::Mesh(std::vector<glm::vec3> aPositions,
  std::vector<unsigned int> Indices,
  std::vector<glm::vec4> aColors,
  GLenum DrawMode)
  : mVAO(0),
  mVertexBufferID(0),
  mElementBufferID(0),
  mDrawMode(DrawMode),
  mNumVertices(0),
  mVertexSize(0)
{
  // TODO: Find a better way to handle data for different shaders/meshs
  // TODO: Write/find better error handling code
  assert(aColors.empty() || (aPositions.size() == aColors.size()));
  assert(!Indices.empty());

  // Determine size of vertex
  if (!aPositions.empty()) mVertexSize += sizeof(aPositions[0]);
  if (!aColors.empty()) mVertexSize += sizeof(aColors[0]);

  // Determine number of vertices
  mNumVertices = aPositions.size();

  // Create interleaved buffer
  std::vector<float> VertexBuffer;
  for (int i = 0; i < mNumVertices; i++)
  {
    PushPosition(VertexBuffer, aPositions[i]);

    if (!aColors.empty())
    {
      PushColor(VertexBuffer, aColors[i]);
    }
  }

  // Generate VertexArray and buffers
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVertexBufferID);
  glGenBuffers(1, &mElementBufferID);

  // Configure buffers
  glBindVertexArray(mVAO);
  glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferID);
  glBufferData(GL_ARRAY_BUFFER,
    VertexBuffer.size() * sizeof(VertexBuffer[0]),
    VertexBuffer.data,
    GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    Indices.size() * sizeof(Indices[0]),
    Indices.data,
    GL_STATIC_DRAW);
  glBindVertexArray(0);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
Mesh::~Mesh()
{
  glDeleteVertexArrays(1, &mVAO);
  glDeleteBuffers(1, &mVertexBufferID);
  glDeleteBuffers(1, &mElementBufferID);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Mesh::Bind() const
{
  glBindVertexArray(mVAO);
}

//=============================================================================
//=============================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Mesh::PushPosition(
  std::vector<float>& VertexBuffer,
  const glm::vec3& pos) const
{
  VertexBuffer.push_back(static_cast<float>(pos.x));
  VertexBuffer.push_back(static_cast<float>(pos.y));
  VertexBuffer.push_back(static_cast<float>(pos.z));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Mesh::PushColor(
  std::vector<float>& VertexBuffer,
  const glm::vec4& color) const
{
  VertexBuffer.push_back(static_cast<float>(color.r));
  VertexBuffer.push_back(static_cast<float>(color.g));
  VertexBuffer.push_back(static_cast<float>(color.b));
  VertexBuffer.push_back(static_cast<float>(color.a));
}