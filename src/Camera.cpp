#include "pch.h"

#include "Camera.h"

Camera::Camera(glm::mat4 viewMat, glm::mat4 projMat)
  : mpViewMatrix(std::make_shared<glm::mat4>(viewMat)),
    mpProjMatrix(std::make_shared<glm::mat4>(projMat))
{}