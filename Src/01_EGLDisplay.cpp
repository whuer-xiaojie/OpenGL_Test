#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>
#include <stdlib.h>

#include "01_EGLDisplay.h"

const EGLint attribute_list[] = {
	EGL_RED_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_BLUE_SIZE, 8,
	EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
	EGL_WIDTH,512,
	EGL_HEIGHT,512,
	EGL_NONE
};

const EGLint context_attributes[] = {
	EGL_CONTEXT_CLIENT_VERSION, 2,
	EGL_NONE
};


EGLBoolean InitEGLStatus(EGLStatus *pEGLStatus)
{
	if (NULL == pEGLStatus)
		return EGL_FALSE;

	EGLint num_config;

	pEGLStatus->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (pEGLStatus->display == EGL_NO_DISPLAY){
		fprintf(stderr, "%s():Get EGL display failed\n", __FUNCTION__);
		return EGL_FALSE;
	}

	if (eglChooseConfig(pEGLStatus->display, attribute_list, pEGLStatus->config, 1, &num_config) 
		== EGL_FALSE){
		fprintf(stderr, "%s():get configs failed\n", __FUNCTION__);
		return EGL_FALSE;
	}

	pEGLStatus->surface = eglCreatePbufferSurface(pEGLStatus->display, pEGLStatus->config,
		attribute_list);
	if (pEGLStatus->surface == EGL_NO_SURFACE){
		fprintf(stderr, "%s():creat buffer surface failed\n", __FUNCTION__);
		return EGL_FALSE;
	}


	return EGL_TRUE;
}

//
// Create a shader object, load the shader source, and
// compile the shader.
//
GLuint LoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
		return 0;

	// Load the shader source
	glShaderSource(shader, 1, &shaderSrc, NULL);

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = malloc(sizeof(char) * infoLen);

			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			print("Error compiling shader:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;

}
