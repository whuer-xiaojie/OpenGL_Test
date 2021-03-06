#include <GL/glut.h>

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void Display(void)
{
	GLubyte fly[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x03, 0x80, 0x01, 0xc0, 0x06, 0xc0, 0x03, 0x60,
		0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0c, 0x20,
		0x04, 0x18, 0x18, 0x20, 0x04, 0x0c, 0x30, 0x20,
		0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xc0, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
		0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xcc,
		0x19, 0x81, 0x81, 0x98, 0x0c, 0xc1, 0x83, 0x30,
		0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0,
		0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0,
		0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
		0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08,
		0x10, 0x63, 0xc6, 0x08, 0x10, 0x30, 0x0c, 0x08,
		0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08 
	};

	GLubyte halftone[] = {
		0xa0, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa0, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa1, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa1, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa2, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa2, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa3, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa3, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa4, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa4, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa5, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa5, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa6, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa6, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa7, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55,
		0xa7, 0xaa, 0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 
	};

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	/*draw one solid unstippled rectangle */
	/* then two stippled rectangles */
	glRectf(25.0, 25.0, 125.0, 125.0);

	glColor3f(0.0, 1.0, 1.0);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(fly);
	glRectf(125.0, 25.0, 255.0, 125.0);

	glColor3f(1.0, 0.0, 1.0);
	glPolygonStipple(halftone);
	glRectf(255.0, 25.0, 325.0, 125.0);
	glDisable(GL_POLYGON_STIPPLE);
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