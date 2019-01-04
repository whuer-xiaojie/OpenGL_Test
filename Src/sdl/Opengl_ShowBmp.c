#include <GL/glut.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static GLuint program;
static GLint positionLoc;
static GLint texCoordLoc;
static GLint samplerLoc;

GLint imageWidth;
GLint imageHeight;
unsigned char *buf = NULL;
/************************************************************************/
/*
*vertex Shader源码
*attribute变量用于获取定点属性信息(顶点坐标，纹理坐标，颜色等)
*a_position存放顶点位置坐标信息（x,y）
*a_texCoord存放纹理坐标信息(u,v)
* varying变量用于和flagment Shader进行数据传递
*v_texCoord 传递纹理坐标信息给片元着色器  (经过GPU计算转化过的)
*/
/************************************************************************/
/*
const char* vertex_shader_src = "#version 330 core\n"
"in vec4 a_position;                        \n"
"in vec2 a_texCoord;                        \n"
"out vec2 v_texCoord;                       \n"
"void mian()                                \n"
"{                                          \n"
"gl_Position=a_position;                    \n"
"v_texCoord = a_texCoord;                   \n"
"}                                          \n";
*/

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
/*
const char *fragment_shader_src ="#version 330 core   \n"
"precision mediump float;                             \n"
"in vec2 v_texCoord;                                  \n"
"uniform sampler2D s_texture;                         \n"
"out vec4 fragColor                                   \n"
"void main() {                                        \n"
"    fragColor = texture2D(s_texture, v_texCoord);    \n"
"}                                                    \n";
*/


const char *fragment_shader_src =
"/*precision mediump float;*/                             \n"
"varying vec2 v_texCoord;                             \n"
"uniform sampler2D s_texture;                         \n"
"void main() {                                        \n"
"    gl_FragColor = texture2D(s_texture, v_texCoord); \n"
"}                                                    \n";


/************************************************************************/
/*
*函数名：load_shader(const char *source, GLenum type)
*功能：创建着色器（Shader）并指定着色器的源码并进行编译
*参数：source 存放着色器（Shader）的源码的指针，type 需要创建的Shader的类型
*     （GL_VERTEX_SHADER和GL_FRAGMENT_SHADER）
*返回值：shader创建成功返回shader描述符，创建失败或者源码错误则返回0
*/
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
// 函数power_of_two用于判断一个整数是不是2的整数次幂    
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/************************************************************************/
/*
*/
/************************************************************************/
void  read_Bmp(char *s)
{
	GLint bfsize;
	GLint bfOffBits;
	GLint test;
	GLint bBitCount=0;
	GLint imagePixelSize;
	GLint planes;
	int  read_returnNum;
	FILE *  fd = fopen(s, "rb");
	if (fd == 0)
	{
		fprintf(stderr, "can't open the bmp\n");
		return 0;
	}
	fseek(fd, 2, SEEK_SET);
	if ((read_returnNum = fread(&bfsize, sizeof(bfsize), 1, fd)) != 1)
	{
		fprintf(stderr, "read bfsize error!\n");
		fclose(fd);
		return;
	}
	fseek(fd, 10, SEEK_SET);
	if ((read_returnNum = fread(&bfOffBits, sizeof(bfOffBits), 1, fd))!=1)
	{
		fprintf(stderr, "read bfOffBits error!\n");
		fclose(fd);
		return;
	}
	fseek(fd, 0x0012, SEEK_SET);
	if ((read_returnNum = fread(&imageWidth, sizeof(imageWidth), 1, fd))!=1)
	{
		fprintf(stderr, "read imageWidth error!\n");
		fclose(fd);
		return;
	}
	if ((read_returnNum = fread(&imageHeight, sizeof(imageHeight), 1, fd))!=1)
	{
		fprintf(stderr, "read imageHeight error!\n");
		fclose(fd);
		return;
	}
	if ((read_returnNum=fread(&planes,2,1,fd))!=1)
	{
		fprintf(stderr, "read planes error!\n");
		fclose(fd);
		return;
	}
/*
	if (planes!=1)
	{
		fprintf(stderr, "not BMP file\n");
		fclose(fd);
		return;
	}
*/
	fseek(fd, 0x001c, SEEK_SET);
	if ((read_returnNum = fread(&bBitCount, 2, 1, fd))!=1)
	{
		fprintf(stderr, "read bBitCount error!\n");
		fclose(fd);
		return;
	}
	if (bBitCount != 24)
	{
		fprintf(stderr, "not 24bit Map  BitCount=%d\n", bBitCount);
		fclose(fd);
		return;
	}
	fprintf(stderr, "width=%d   height=%d  bBitCount=%d\n", imageWidth, imageHeight, bBitCount);
	test = imageWidth * 3;
	while (test%4!=0)
	{
		test++;
	}
	test *= imageHeight;
	imagePixelSize=test;
	//fprintf(stderr, "test = %d\n", test );
	//imagePixelSize = bfsize - bfOffBits;
	//fprintf(stderr, "imagePixelSize = %d\n", imagePixelSize);
	//imagePixelSize = imageWidth*imageHeight * 3;
	buf = (unsigned char  *)malloc(imagePixelSize);
	if (buf == 0)
	{
		fprintf(stderr, "buf malloc failed\n");
		fclose(fd);
		return 0;
	}
	fseek(fd, bfOffBits, SEEK_SET);
	if ((fread(buf, imagePixelSize, 1, fd)) <= 0)
	{
		fprintf(stderr, "read pixel data Error\n");
		free(buf);
		buf = NULL;
	}
   {
	 GLint max;
	 glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	 fprintf(stderr, "MaxPixelSize = %d\n", max);
	 if (!power_of_two(imageWidth)
		 || !power_of_two(imageHeight)
		 || imageWidth > max
		 || imageHeight > max)
	 {
		 const GLint new_width = 256;
		 const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形    
		 GLint new_line_bytes, new_total_bytes;
		 GLubyte* new_pixels = 0;

		 // 计算每行需要的字节数和总字节数    
		 new_line_bytes = new_width * 3;
		 while (new_line_bytes % 4 != 0)
			 ++new_line_bytes;
		 new_total_bytes = new_line_bytes * new_height;

		 // 分配内存    
		 new_pixels = (GLubyte*)malloc(new_total_bytes);
		 if (new_pixels == 0)
		 {
			 fprintf(stderr, "malloc new_pixels failed");
			 free(buf);
			 fclose(fd);
			 return 0;
		 }

		 // 进行像素缩放    
		 gluScaleImage(GL_RGB,
			 imageWidth,imageHeight, GL_UNSIGNED_BYTE, buf,
			 new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

		 // 释放原来的像素数据，把buf指向新的像素数据，并重新设置width和height    
		 free(buf);
		 buf = new_pixels;
		 imageWidth = new_width;
		 imageHeight = new_height;
	 }	 
   }
/*
      //change the pixel date BGR to RGB
	int i = 0; char temp;
	while (i < imagePixelSize)
	{
		temp = buf[i];
		buf[i] = buf[i + 2];
		buf[i + 2] = temp;
		i += 3;
	}
*/
	/*
	else
	{
		unsigned char s1;
		int i = 0; int j = 0;
		while (i < imageWidth)
		{
			i++;
			while (j<imageHeight)
			{
				switch (bBitCount)
				{
				case 24:
				{
					j++;
					s1 = buf[j];
					buf[j] = buf [j+ 2];
					buf[j + 2] = s1;
					break;
				}
				case 32:
				{
					j++;
					s1 = buf[j];
					buf[j] = buf [j+ 2];
					buf[j + 2] = s1;
					break;

				}
				default:
					break;
				}
			}
		}
	}
*/

	fclose(fd);
	//return 0;
}

/************************************************************************/
/*
*函数名：display_Bmp()
*参数：  无
*功能：  根据全局变量buf的内容调用GPU可执行程序program进行GPU显示buf内容
*返回值：无
*/
/************************************************************************/
void display_Bmp()
{
	const unsigned char *b;
	int x, y;
	unsigned char red, green, blue;
	GLuint textureId;

	//init the vertex shader info

	//first 
	//GLfloat vertices[] = { 
	//	-1.0f,  1.0f,  0.0f,	/* Position 0 */ 0.0f, 0.0f,		/* TexCooed 0 */
	//	-1.0f, -1.0f,  0.0f,	/* Position 1 */ 0.0f, 1.0f,		/* TexCooed 1 */
	//	 1.0f,  -1.0f,  0.0f,	/* Position 2 */ 1.0f, 1.0f,		/* TexCooed 2 */
	//	 1.0f,   1.0f,  0.0f,	/* Position 3 */ 1.0f, 0.0f		   /* TexCooed 3 */};

	//second
	//GLfloat vertices[] = {
	//   -1.0f, 1.0f,0.0f, 1.0f,0.0f,0.0f, 0.0f,0.0f,
	//    0.0f,-1.0f,0.0f, 0.0f,1.0f,0.0f, 1.0f,0.0f,
	//    0.0f, 1.0f,0.0f, 0.0f,0.0f,1.0f, 1.0f,1.0f,
	//   -1.0f,-1.0f,0.0f, 1.0f,1.0f,0.0f, 0.0f,1.0f };

	//改变顶点的顺序解决图像颠倒的问题
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,	/* Bottom Left  */
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,		/* Bottom Right */
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,		/* Top Right */
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f		/* Top Left */
	};

	GLushort indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};


	if (buf == NULL)
	{
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		//SDL_GL_SwapWindow(screen);
		//SDL_ShowCursor(SDL_DISABLE);
		fprintf(stderr, "no show data \n");
		return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0,
	//	GL_RGB, GL_UNSIGNED_BYTE, buf);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imageWidth, imageHeight, 
		GL_BGR_EXT, GL_UNSIGNED_BYTE, buf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glUseProgram(program);

	glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(GLfloat), vertices);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(GLfloat), &vertices[3]);

	glEnableVertexAttribArray(positionLoc);
	glEnableVertexAttribArray(texCoordLoc);

	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textureId);

	//glUniform1i(samplerLoc, 0);

	//draw the picture
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
	
	//glFlush();
	glutSwapBuffers();
	//SDL_GL_SwapWindow(screen);
	//SDL_ShowCursor(SDL_DISABLE);
	glDeleteTextures(1, &textureId);
	free(buf);
	buf = NULL;


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

/************************************************************************/
/*
*/
/************************************************************************/
void gl_Init_Viewport()
{
	GLint status;
	GLuint vertex_shader;
	GLuint fragment_shader;
	//create screen
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_BLEND);
	glutCreateWindow("OpenGL_Show_Bmp");
	
	/* Extension wrangler initialising */
	/*
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		exit(1);
	}
	*/
	glEnable(GL_TEXTURE_2D);//启用二维文理
	//create vertex shader
	vertex_shader = load_shader(vertex_shader_src, GL_VERTEX_SHADER);
	if (vertex_shader == 0)
	{
		fprintf(stderr, "Load vertex shader failed\n");
		exit(1);
	}
	//create fragment shader
	fragment_shader = load_shader(fragment_shader_src, GL_FRAGMENT_SHADER);
	if (fragment_shader == 0)
	{
		fprintf(stderr, "Load fragment shader failed\n");
		exit(1);
	}

	//create program
	if ((program = glCreateProgram()) == 0)
	{
		fprintf(stderr, "glCreateProgram() failed\n");
		exit(1);
	}

	//attach shader to program
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	//link program( A GPU executable program)
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
    //glViewport(0, 640, 500, 500);

	//init the start color
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//glFlush();
	glutSwapBuffers();
	fprintf(stderr, "Opengl Window Init Finish\n");
	sleep(2);

}
int close_Viewport(void)
{
	glDeleteProgram(program);
      fprintf(stderr,"close_program");
	//SDL_GL_DeleteContext(gl_context);
	//SDL_DestroyWindow(screen);
	//SDL_Quit();
	return 0;
}
void timeFunc(int value)
{
    
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	gl_Init_Viewport();
      char *s;
      s = "photo.bmp";
      read_Bmp(s);
	glutDisplayFunc(display_Bmp);
      //glutTimerFunc(2000,timeFunc,0);
	glutMainLoop();
      close_Viewport();
      return 0;
/*
	int count = 0;
	while (count < 8)
	{
		char *s;
		switch (count % 4)
		{
		case 0:
		{
			s = "photo.bmp";
			read_Bmp(s);
			glutDisplayFunc(display_Bmp);
			glutMainLoop();
			count++;
			sleep(2);
			break;
		}
		case 1:
		{
			s = "photo1.bmp";
			read_Bmp(s);
			glutDisplayFunc(display_Bmp);
			glutMainLoop();
			count++;
			sleep(2);
			break;
		}
		case 2:
		{
			s = "photo2.bmp";
			read_Bmp(s);
			glutDisplayFunc(display_Bmp);
			glutMainLoop();
			count++;
			sleep(2);
			break;
		}
		case 3:
		{
			s = "photo3.bmp";
			read_Bmp(s);
			glutDisplayFunc(display_Bmp);
			glutMainLoop();
			count++;
			sleep(2);
			break;
		}
		default:
			break;
		}
	}
      glutMainLoop();
	close_Viewport();
	return 0;
*/
}

