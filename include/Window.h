/**
 * @file Window.h
 *
 * Defines a window to use as a rendering context
 *
 * @author Lonnie L. Souder II
 * @date 03/22/20
 */

#pragma once

#include "OpenGLManager.h"
#include <GLFW/glfw3.h>
#include <tuple>
#include <memory>
#include <string>

class Window
{
public:

    Window(
        const int& AspectRatioWidth,
        const int& AspectRationHeight,
        const int& Scale,
		const std::string &Title = "Playground Engine");

    ~Window();
    
    // TODO: Copy constructor?

    /**
     * Sets this window as the current context for OpenGL
     */
    void Use();

    /**
     * Determines whether or not the window should remain open
     * @return true if window should close else false
     */
    bool WindowShouldClose() const;

    /**
     * Swaps the frame buffers for this window
     */
    void SwapBuffers() const;

    /**
     * Returns the aspect ratio
     * @returns Window width / Window height
     */
    float GetAspectRatio() const;

private:
	OpenGLManager* mpGLManager;
	GLFWwindow* mpWindow;
	std::tuple<float, float> mAspectRatio;
	int mScale;
};