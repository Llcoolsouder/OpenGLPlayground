#include "pch.h"

#include "Camera.h"

Camera::Camera(glm::mat4 viewMat, glm::mat4 projMat)
  : mViewMatrix(viewMat),
    mProjMatrix(projMat)
{}