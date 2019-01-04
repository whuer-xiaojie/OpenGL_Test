//#include <GL/glut.h>
//
//static const GLfloat vertex_list[][3] = {
//// 	-0.5f, -0.5f, -0.5f,
//// 	0.5f, -0.5f, -0.5f,
//// 	-0.5f, 0.5f, -0.5f,
//// 	0.5f, 0.5f, -0.5f,
//// 	-0.5f, -0.5f, 0.5f,
//// 	0.5f, -0.5f, 0.5f,
//// 	-0.5f, 0.5f, 0.5f,
//// 	0.5f, 0.5f, 0.5f,
//
//	0.2f, 0.2f, 0.2f,
//	0.5f, 0.2f, 0.2f,
//	0.2f, 0.5f, 0.2f,
//	0.5f, 0.5f, 0.2f,
//	0.2f, 0.2f, 0.5f,
//	0.5f, 0.2f, 0.5f,
//	0.2f, 0.5f, 0.5f,
//	0.5f, 0.5f, 0.5f,
//};
//
//static const GLint index_list[][4] = {
//	0, 2, 3, 1,
//	0, 4, 6, 2,
//	0, 1, 5, 4,
//	4, 5, 7, 6,
//	1, 3, 7, 5,
//	2, 6, 7, 3,
//};
//
//void init(void)
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	//glShadeModel(GL_FLAT);
//}
//
//void Display(void)
//{
//// 	static GLubyte frontIndices[] = { 4, 5, 6, 7 };
//// 	static GLubyte rightIndices[] = { 1, 2, 6, 5 };
//// 	static GLubyte bottomIndices[] = { 0, 1, 5, 4 };
//// 	static GLubyte backIndices[] = { 0, 3, 2, 1 };
//// 	static GLubyte leftIndices[] = { 0, 4, 7, 3 };
//// 	static GLubyte topIndices[] = { 2, 3, 7, 6 };
//
//	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontIndices);
//	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightIndices);
//	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomIndices);
//	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backIndices);
//	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftIndices);
//	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topIndices);
//
//	glFrontFace(GL_CCW);
//	glCullFace(GL_BACK);
//	glEnable(GL_CULL_FACE);
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glColor3f(1.0, 1.0, 0.0);
//	glBegin(GL_QUADS);
//	for (int i = 0; i < 6; i++)
//		for (int j = 0; j < 4; j++)
//			glVertex3fv(vertex_list[index_list[i][j]]);
//	glEnd();
//
//	glDisable(GL_CULL_FACE);
//	glFlush();
//}
//
//void Reshap(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
//}
//
//int main(int argc, char **argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	//glutInitWindowPosition(100, 100);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow(argv[0]);
//	init();
//
//	glutDisplayFunc(Display);
//	glutReshapeFunc(Reshap);
//	glutMainLoop();
//	return 0;
//}


#include <GL/glut.h>
#include <math.h>
#define GL_PI 3.1415f
 
 GLfloat xRot = -35.0f;
 GLfloat yRot = 15.0f;
 GLfloat xMov = 0.0f;
 GLfloat winW = 0.0f;
 GLfloat winH = 0.0f;
 GLfloat zoom = 1.0f;
 
 void RenderScene(void)
 {
     glClear(GL_COLOR_BUFFER_BIT);
 
     glPushMatrix();
     glLoadIdentity();
     glRotatef(xRot, 1.0f, 0.0f, 0.0f);
     glRotatef(yRot, 0.0f, 1.0f, 0.0f);
 
     // 底面
     glBegin(GL_LINE_LOOP);
     glVertex3f(0.0f+xMov, 0.0f, 0.0f);
     glVertex3f(1.0f+xMov, 0.0f, 0.0f);
     glVertex3f(1.0f+xMov, 0.0f, 1.0f);
     glVertex3f(0.0f+xMov, 0.0f, 1.0f);
     glEnd();
 
     // 顶面
     glBegin(GL_LINE_LOOP);
     glVertex3f(0.0f+xMov, 1.0f, 1.0f);
     glVertex3f(0.0f+xMov, 1.0f, 0.0f);
     glVertex3f(1.0f+xMov, 1.0f, 0.0f);
     glVertex3f(1.0f+xMov, 1.0f, 1.0f);
     glEnd();
 
     // 背面
     glBegin(GL_LINE_LOOP);
     glVertex3f(0.0f+xMov, 0.0f, 0.0f);
     glVertex3f(1.0f+xMov, 0.0f, 0.0f);
     glVertex3f(1.0f+xMov, 1.0f, 0.0f);
     glVertex3f(0.0f+xMov, 1.0f, 0.0f);
     glEnd();
 
     // 前面
     glBegin(GL_LINE_LOOP);
     glVertex3f(1.0f+xMov, 0.0f, 1.0f);
     glVertex3f(0.0f+xMov, 0.0f, 1.0f);
     glVertex3f(0.0f+xMov, 1.0f, 1.0f);
     glVertex3f(1.0f+xMov, 1.0f, 1.0f);
     glEnd();
 
     // 右面
     glBegin(GL_LINE_LOOP);
     glVertex3f(1.0f+xMov, 0.0f, 0.0f);
     glVertex3f(1.0f+xMov, 0.0f, 1.0f);
     glVertex3f(1.0f+xMov, 1.0f, 1.0f);
     glVertex3f(1.0f+xMov, 1.0f, 0.0f);
     glEnd();
 
     // 左面
     glBegin(GL_LINE_LOOP);
     glVertex3f(0.0f+xMov, 0.0f, 0.0f);
     glVertex3f(0.0f+xMov, 0.0f, 1.0f);
     glVertex3f(0.0f+xMov, 1.0f, 1.0f);
     glVertex3f(0.0f+xMov, 1.0f, 0.0f);
     glEnd();
 
     glPopMatrix();
     glFlush();
 }
 void OnReshape(int w, int h)
 {
     GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;
     winW = w;
     winH = h;
 
     glViewport(0,0,w,h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     if (w <= h)
     {
         glOrtho(-3.0f*zoom, 3.0f*zoom, -3.0f*zoom/aspectRatio, 3.0f*zoom/aspectRatio, -10.0f*zoom, 10.0f*zoom);
     }
     else{
         glOrtho(-3.0f*zoom*aspectRatio, 3.0f*zoom*aspectRatio, -3.0f*zoom, 3.0f*zoom, -10.0f*zoom, 10.0f*zoom);
     }
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
 }
 void OnMouse(int button, int state, int x, int y)
 {
     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
     {
         xRot += 1;
         yRot += 1;
         glutPostRedisplay();
     }
     else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
     {
         xMov -= 0.1;
         glutPostRedisplay();
     }
     else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
     {
         zoom += 0.1;
         OnReshape(winW,winH);
         glutPostRedisplay();
     }
 }
 void OnKeyUpDown(int key, int x, int y)
 {
     if (key == GLUT_KEY_UP){
         zoom -= 0.1;
     }
     else if (key == GLUT_KEY_DOWN){
         zoom += 0.1;
     }
     OnReshape(winW,winH);
     glutPostRedisplay();
 }
 
 void SetupRC()
 {
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
     glColor3f(0.0f, 1.0f, 0.0f);
 }
 
 void main(int argc, char **argv)
 {
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutCreateWindow("Cube");
     glutDisplayFunc(RenderScene);
     glutReshapeFunc(OnReshape);
     glutMouseFunc(OnMouse);
     glutSpecialFunc(OnKeyUpDown);
 
     SetupRC();
 
     glutMainLoop();
 }