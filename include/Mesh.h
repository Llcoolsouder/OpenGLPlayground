/**
 * @file Mesh.h
 *
 * Handles all buffers that make up a mesh
 *
 * @author Lonnie L. Souder II
 * @date 08/29/2019
 */

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

/**
 * As of 08/29/19, Mesh ONLY supports interleaved arrays
 * because Shader only supports interleaved arrays
 */
class Mesh
{
public:
  Mesh() = delete;
  Mesh(const Mesh& other) = delete;

  /**
   * Creates a mesh with one interleaved vertex buffer
   */
  Mesh(
    std::vector<glm::vec3> aPositions,
    std::vector<unsigned int> Indices,
    std::vector<glm::vec4> aColors = {},
    GLenum DrawMode = GL_TRIANGLES);

  /**
   * Destroys all buffer objects in this mesh
   */
  ~Mesh();

  /**
   * Binds the mesh buffers to the context
   */
  void Bind() const;

private:

  void PushPosition(std::vector<float>&, const glm::vec3&) const;

  void PushColor(std::vector<float>&, const glm::vec4&) const;

private:
  GLuint mVAO;
  GLuint mVertexBufferID;
  GLuint mElementBufferID;
  GLenum mDrawMode;

  // TODO: These aren't strictly necessary at the moment. Revisit this later on. 08/29/19
  unsigned int mNumVertices;
  unsigned int mVertexSize;
};