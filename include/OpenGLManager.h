/**
 * @file OpenGLManager.h
 *
 * Singleton object for managing initializatin of OpenGL
 *
 * @author Lonnie L. Souder II
 * @date 03/22/20
 */

#pragma once

#include <memory>

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