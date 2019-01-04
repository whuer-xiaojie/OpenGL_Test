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
	const GLubyte* name = glGetString(GL_VENDOR); //���ظ���ǰOpenGLʵ�ֳ��̵�����
	const GLubyte* biaoshifu = glGetString(GL_RENDERER); //����һ����Ⱦ����ʶ����ͨ���Ǹ�Ӳ��ƽ̨
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //���ص�ǰOpenGLʵ�ֵİ汾��
	const GLubyte* gluVersion = gluGetString(GLU_VERSION); //���ص�ǰGLU���߿�汾
	printf("OpenGLʵ�ֳ��̵����֣�%s\n", name);
	printf("��Ⱦ����ʶ����%s\n", biaoshifu);
	printf("OpenGLʵ�ֵİ汾�ţ�%s\n", OpenGLVersion);
	printf("OGLU���߿�汾��%s\n", gluVersion);
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
