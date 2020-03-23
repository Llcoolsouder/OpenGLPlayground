/**
 * @file OpenGLManager.h
 *
 * Singleton object for managing initializatin of OpenGL
 * NOTE: This file should be included before any other headers
 * that include OpenGL headers.
 *
 * @author Lonnie L. Souder II
 * @date 03/22/20
 */

#pragma once

// TODO: Make a master header for PlaygroundEngine?
// Makes sure GLEW and GLFW are included in the correct order
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

/**
 * The proper order of operation to initialize OpenGL with a context is
 * 1. Create an instance of this class
 * 2. Create a Window
 * 3. Call Window.Use()
 * 4. Call OpenGLManager::InitGLEW()
 */
class OpenGLManager
{
public:
	~OpenGLManager();

	OpenGLManager(const OpenGLManager &other) = delete;

	/**
     * Accesses the single instance of OpenGLManager
     * @return Shared pointer to instance of OpenGLManager
     */
	static OpenGLManager* Instance();

    /**
     * Initializes GLEW
     * @return true if successful else false
     */
	bool InitGLEW() const;

    void PollEvents();

private:
	OpenGLManager();
	
    /**
     * Initializes OpenGL with GLEW and GLFW3
     * @return true if successful else false
     */
    bool InitializeOpenGL() const;

    /**
     * Initializes GLFW3
     * @return true if successful else false
     */
    bool InitGLFW() const;

    /**
     * Terminates GLFW
     */
    void CleanupGLFW() const;

private:
	static OpenGLManager* mpInstance;
};