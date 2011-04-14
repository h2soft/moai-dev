#ifndef USLSEXT_PCH_H
#define	USLSEXT_PCH_H

#include <uslscore/uslscore.h>

#ifndef TIXML_USE_STL
	#define TIXML_USE_STL
#endif

#ifdef MOAI_OS_WINDOWS
	#define GLEW_STATIC
	#include <gl/glew.h>
#endif

#ifdef MOAI_OS_OSX
	//#include <GL/glew.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glext.h>
#endif

#ifdef MOAI_OS_IPHONE
	#include <OpenGLES/ES1/gl.h>
	#include <OpenGLES/ES1/glext.h>
#endif

#ifdef MOAI_OS_ANDROID
	#include <GLES/gl.h>
	#include <GLES/glext.h>
#endif

#ifdef MOAI_OS_LINUX
	#ifndef ANDROID
		#include <GL/glew.h>
	#endif
#endif

#endif
