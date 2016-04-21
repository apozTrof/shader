//Cross platform file for OpenGL header file inclusion.
//Always include this file instead of directly including glut/glew/gl.

#ifndef GLINCLUDE_H_
#define GLINCLUDE_H_

#if __APPLE__

#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>

#else 

#include "../Resources/Win32/Glew/include/GL/glew.h"
#include "../Resources/Win32//GLUT/glut.h"

#endif

#endif //GLINCLUDE_H_