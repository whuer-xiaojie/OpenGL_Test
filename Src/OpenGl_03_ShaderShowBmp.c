#include <GL/glut.h>
#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>

//static SDL_Window *screen = NULL;
//static SDL_GLContext gl_context;
static GLuint program;
static GLint positionLoc;
static GLint texCoordLoc;
static GLint samplerLoc;
 
GLuint vertex_shader;
GLuint fragment_shader;

unsigned char *buf=NULL;
/************************************************************************/
/*        *vertex Shader源码
*attribute变量用于获取定点属性信息
*a_position存放顶点位置坐标信息
*a_texCoord存放纹理坐标信息
* varying变量用于和flagment Shader进行数据传递
*v_texCoord 传递纹理坐标信息给片元着色器                                                              */
/************************************************************************/


const char *vertex_shader_src =
"attribute vec4 a_position;    \n"
"attribute vec2 a_texCoord;    \n"
"varying vec2 v_texCoord;      \n"
"void main() {                 \n"
"    gl_Position = a_position; \n"
"    v_texCoord = a_texCoord;  \n"
"}                             \n";
/************************************************************************/
/*                                                                      */
/************************************************************************/
const char *fragment_shader_src =
"precision mediump float;                             \n"
"varying vec2 v_texCoord;                             \n"
"uniform sampler2D s_texture;                         \n"
"void main() {                                        \n"
"    gl_FragColor = texture2D(s_texture, v_texCoord); \n"
"}                                                    \n";


/************************************************************************/
/*                                                                      */
/************************************************************************/
static GLuint load_shader(const char *source, GLenum type)
{
	GLuint shader;
	const char *shaders[1] = { NULL };
	GLint status;

	if ((shader = glCreateShader(type)) == 0)
	{
		fprintf(stderr, "Create Shader failed\n");
		return 0;
	 }

	shaders[0] = source;
	glShaderSource(shader, 1, shaders, NULL);
	shaders[0] = NULL;

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		
		//get shader compiled error
		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			fprintf(stderr, "Shaderlog:\n%s", log);
			free(log);
		}
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}
void  read_Bmp()
{
	return 0;
}
void display()
{
	const unsigned char *b;
	int x, y;
	unsigned char red, green, blue;
	GLuint textureId;
	GLfloat vertices[] = { -1.0f, 1.0f, 0.0f,	/* Position 0 */
		0.0f, 0.0f,		/* TexCooed 0 */
		-1.0f, -1.0f, 0.0f,	/* Position 1 */
		0.0f, 1.0f,		/* TexCooed 1 */
		1.0f, -1.0f, 0.0f,	/* Position 2 */
		1.0f, 1.0f,		/* TexCooed 2 */
		1.0f, 1.0f, 0.0f,	/* Position 3 */
		1.0f, 0.0f		/* TexCooed 3 */
	};
	GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
      glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT);
	if (buf == NULL)
		{fprintf(stderr, "777777\n");return;}

	//t1 = __clock();

	//pthread_mutex_lock(&screen_mutex);

	/* Lock the screen */
	/*if (SDL_MUSTLOCK(screen))
	if (SDL_LockSurface(screen) < 0)
	goto out;*/

	//t2 = __clock();

	/*b = buf;
	for (y = 0; y < sign_height; y++)
	for (x = 0; x < sign_width; x++) {
	red   = *b++;
	green = *b++;
	blue  = *b++;
	putpixel(screen, x, y, PC_RGB(red, green, blue));
	}*/

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 500, 500, 0,
		GL_RGB, GL_UNSIGNED_BYTE, buf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//t3 = __clock();

	/* Unlock the screen */
	//if (SDL_MUSTLOCK(screen))
	//	SDL_UnlockSurface(screen);

	/* Update the entire screen */
	//SDL_UpdateRect(screen, 1, 1, sign_width, sign_height);

	//glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);

	glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(GLfloat), vertices);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(GLfloat), &vertices[3]);

	glEnableVertexAttribArray(positionLoc);
	glEnableVertexAttribArray(texCoordLoc);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glUniform1i(samplerLoc, 0);

	//draw the picture
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

	//SDL_GL_SwapWindow(screen);

	glDeleteTextures(1, &textureId);


/*
glClear(GL_COLOR_BUFFER_BIT);

glBegin(GL_POLYGON);
glVertex2f(-0.5,-0.5);
glVertex2f(-0.5,0.5);
glVertex2f(0.5,0.5);
glVertex2f(0.5,-0.5);
glEnd();
*/
}
void gl_Create()
{
      GLint status;
	//create screen
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Show_BMP_Shader");
      
    glEnable(GL_TEXTURE_2D);//启用二维文理
	
	//create vertex shader
	vertex_shader = load_shader(vertex_shader_src, GL_VERTEX_SHADER);
	if (vertex_shader == 0) {
		fprintf(stderr, "Load vertex shader failed\n");
		exit(1);
	}

	//create fragment shader

	fragment_shader = load_shader(fragment_shader_src, GL_FRAGMENT_SHADER);
	if (fragment_shader == 0) {
		fprintf(stderr, "Load fragment shader failed\n");
		exit(1);
	}

	//create program
	if ((program = glCreateProgram()) == 0) {
		fprintf(stderr, "glCreateProgram() failed\n");
		exit(1);
	}

	//attach shader to program
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	//link program
	glLinkProgram(program);

	//get link information
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		GLint infoLen;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1) {
			char *infoLog = malloc(infoLen);

			glGetProgramInfoLog(program, infoLen, NULL, infoLog);
			fprintf(stderr, "Link program: \"%s\"\n", infoLog);
			free(infoLog);
		}

		glDeleteProgram(program);
		exit(1);
	}

	//delete the shader
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	//get shader start point(position,texcoord,texture)
	positionLoc = glGetAttribLocation(program, "a_position");
	texCoordLoc = glGetAttribLocation(program, "a_texCoord");

	samplerLoc = glGetUniformLocation(program, "s_texture");

	//create the view_port start from left_top 
	glViewport(0, 640, 500, 500);

	//init the start color
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc ,char **argv)
{
glutInit(&argc,argv);
/* Initialize SDL */
/*
if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
	exit(1);
}
if ((screen = SDL_CreateWindow("beacon", 0, 0,
	PC_SCREEN_WIDTH, PC_SCREEN_HEIGHT,
	SDL_WINDOW_OPENGL)) == NULL) {
	fprintf(stderr, "Couldn't set %dx%dx24 video mode: %s\n",
		PC_SCREEN_WIDTH, PC_SCREEN_HEIGHT, SDL_GetError());
	exit(1);
}

//创建Opengl的上下文对象
//gl_context = SDL_GL_CreateContext(screen);
*/
gl_Create();
//glutCreateWindow("Hello,world!");
glutDisplayFunc(display);
glutMainLoop();
}
