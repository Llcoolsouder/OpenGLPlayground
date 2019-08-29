/**
 * @file Camera.h
 *
 * Defines a class to store all data and functionality for a camera
 *
 * @author Lonnie L. Souder II
 * @date 08/01/2019
 */
#pragma once

#include <glm/glm.hpp>

#include <memory>

class Camera
{
public:

  /**
   * Creates a camera with the specified matrices
   * 
   * @param viewMat View Matrix (specifies where the camera is in world space)
   * @param projMat Projection Matrix (specifies how the world is projected onto a 2D viewport)
   */
  Camera(
    glm::mat4 viewMat = glm::mat4(1.0f),
    glm::mat4 projMat = glm::mat4(1.0f));

  /**
   * Gets the view matrix
   * This should be used for setting uniforms in shader programs
   *
   * @return view matrix
   */
  inline std::shared_ptr<const glm::mat4> GetViewMatrix() const { return mpViewMatrix; }

  /**
   * Gets the projection matrix
   * This should be used for setting uniforms in shader programs
   *
   * @return projection matrix
   */
  inline std::shared_ptr<const glm::mat4> GetProjMatrix() const { return mpProjMatrix; }

private:
  std::shared_ptr<glm::mat4> mpViewMatrix;
  std::shared_ptr<glm::mat4> mpProjMatrix;
};
