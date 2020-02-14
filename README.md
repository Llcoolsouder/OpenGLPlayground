# OpenGL Playground [![Build Status](https://travis-ci.org/Llcoolsouder/OpenGLPlayground.svg?branch=master)](https://travis-ci.org/Llcoolsouder/OpenGLPlayground) [![codecov](https://codecov.io/gh/Llcoolsouder/OpenGLPlayground/branch/master/graph/badge.svg)](https://codecov.io/gh/Llcoolsouder/OpenGLPlayground)

# Table of Contents
1. [Description](#description)
2. [Dependencies](#dependencies)
3. [Building](#building)
    - [Windows](#windows)
    - [Linux](#linux)
4. [Examples (you should just skip to this)](#examples)


## Description <a name="description"></a>
This is just a mess of code created in my OpenGL studies.  
All of the code is documented at <https://llcoolsouder.github.io/OpenGLPlayground/index.html>;
not because I think anyone will find it particularly useful, but because it's
good practice.

## Dependencies <a name="dependencies"></a>
- OpenGL 4.3 (for computer shaders)
- GLEW
- GLFW3
- GLM
- CMake (This was tested on version 3.15)

## Building <a name="building"></a>

Once all of the dependencies are installed, building should be as easy as
```
mkdir build && cd build
cmake ..
make .
```

### Windows <a name="windows"></a>
For Windows, CMake will expect the dependencies to be installed in `C:/thirdparty/`
At the time of making this, there has been a Windows update that blocks
manual changes to `C:/Program Files (x86)/`, which is where CMake looks for most
of these dependencies by default on Windows. The file structure should look like
this:

<pre>
C:/thirdparty/  
|-- glew  
|   |-- include/  
|   `-- lib/Win32/Release/  
|-- glfw3  
|   |-- include/  
|   `--build/src/Release/  
`-- glm  
</pre>

On Windows I built using the CMake-Gui. If you have this file structure,
CMake should find everything except GLFW3 static libraries. You will have
to give a path to glfw3.lib for GLFW3_LIBRARY.

### Linux <a name="linux"></a>
I built this on Ubuntu 16, and Travis currently tests on Ubuntu 18.
You will need to run the following commands to install the dependencies.
```
sudo apt-get install -y libglew-dev
sudo apt-get install -y libglm-dev
sudo apt-get install -y libglfw3-dev
```
***I needed to install CMake __3.15__ in order to find GLEW properly.***


## Examples <a name="examples"></a>
![alt text](https://github.com/Llcoolsouder/OpenGLPlayground/blob/master/samples/particle_attraction.gif "Particles simulated on compute shaders")
