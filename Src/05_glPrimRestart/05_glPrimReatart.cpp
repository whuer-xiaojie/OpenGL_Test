#include <GL/glut.h>
#include <EGL/GLES2/gl2.h>
#include <stdio.h>

#define BUFFER_OFFSET(offset) ((GLvoid *)NULL+offset)

#define XStart            -0.8
#define XEnd              0.8
#define YStart            -0.8
#define YEnd              0.8

#define NumXPoints        11
#define NumYPoints        11

#define NumPoints         (NumXPoints * NumYPoints)
#define NumPointPreStrip  (2*NumXPoints)
#define NumStrips         (NumYPoints-1)

#define RestartIndex      0xFFFF

void Init(void)
{
	GLuint vbo, ebo;
	GLfloat *vertices;
	GLushort *indices;

	/* set up vertex data */
	glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void GetOpenglVersion(void)
{
	const GLubyte* name = glGetString(GL_VENDOR); //返回负责当前OpenGL实现厂商的名字
	const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本号
	const GLubyte* gluVersion = gluGetString(GLU_VERSION); //返回当前GLU工具库版本
	printf("OpenGL实现厂商的名字：%s\n", name);
	printf("渲染器标识符：%s\n", biaoshifu);
	printf("OpenGL实现的版本号：%s\n", OpenGLVersion);
	printf("OGLU工具库版本：%s\n", gluVersion);
}
void DisplayCallBack(void)
{

}

void ReshapeCallBack(int w, int h)
{

}

void MouseEventCallBack(int button, int state, int x, int y)
{

}

void KeyBoardCallBack(GLubyte key, int x, int y)
{

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);

	Init();
	GetOpenglVersion();
	glutDisplayFunc(DisplayCallBack);
	glutReshapeFunc(ReshapeCallBack);
	glutMouseFunc(MouseEventCallBack);
	glutKeyboardFunc(KeyBoardCallBack);

	glutMainLoop();
	return 0;
}
