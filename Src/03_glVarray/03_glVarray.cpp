#include <GL/glut.h>

static GLint vertices[] = {
	25, 25,
	100, 325,
	175, 25,
	175, 325,
	250, 25,
	325, 325
};
static GLfloat colors[] = {
	1.0, 0.2, 0.2,
	0.2, 0.2, 1.0,
	0.8, 1.0, 0.2,
	0.75, 0.75, 0.75,
	0.35, 0.35, 0.35,
	0.5, 0.5, 0.5
};
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(2, GL_INT, 0, vertices);
}

void Display(void)
{
	

 	glBegin(GL_TRIANGLES);
 	glArrayElement(2);
 	glArrayElement(3);
 	glArrayElement(5);
 	glEnd();

// 	glBegin(GL_TRIANGLES);
// 	
// 	glColor3fv(colors + (2 * 3));
// 	glVertex2iv(vertices + (2 * 2));
// 
// 	glColor3fv(colors + (3 * 3));
// 	glVertex2iv(vertices + (3 * 2));
// 
// 	glColor3fv(colors + (5 * 3));
// 	glVertex2iv(vertices + (5 * 2));
// 	glEnd();

	glFlush();
}

void Reshap(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	init();

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshap);
	glutMainLoop();
	return 0;
}