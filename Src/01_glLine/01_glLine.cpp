
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#define DrawOneLine(x1,y1,x2,y2) glBegin(GL_LINES);\
	glVertex2f((x1),(y1));glVertex2f((x2),(y2));glEnd();

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void Display(void)
{
	int i;
	GLfloat pFarray[5] = { 0 };
	glClear(GL_COLOR_BUFFER_BIT);
	/*select white for all lines */
	glColor3f(1.0, 0.0, 1.0);

	//glGetFloatv(0x846e, pFarray);
	//glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE,pFarray)
	//glGetFloatv(0x846d, pFarray);
	//glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, pFarray);


	/* in 1st row,3 lines,each with a different stipple */
	glEnable(GL_LINE_STIPPLE);

	glLineStipple(1, 0x0101);/* dotted */
	DrawOneLine(50.0, 50.0, 150.0, 150.0);

	glLineStipple(1, 0x00FF);/* dashed */
	DrawOneLine(150.0, 50.0, 250.0, 150.0);

	glLineStipple(1, 0x1C47);/* dash/dot/dash */
	DrawOneLine(250.0, 50.0, 350.0, 150.0);

	/* in 2nd row,2 wide lines,each with different stipple */
	glLineWidth(10.0);
	glLineStipple(1, 0x0101);/* dotted */
	DrawOneLine(50.0, 200.0, 150.0, 350.0);

	glLineStipple(1, 0xFFFF);/* dashed */
	DrawOneLine(150.0, 200.0, 250.0, 350.0);

	glLineStipple(1, 0x1C47);/* dash/dot/dash */
	DrawOneLine(250.0, 200.0, 350.0, 350.0);

	/* in 3rd row ,6lines,with dash/dot/dash stipple */
	/* as part of a single connected line strip */
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 100; i++)
		glVertex2f(50.0, 75.0 + ((GLfloat)i*50.0));
	glEnd();

	/*in 4th row,6 independent lines with same stipple*/
 	for (i = 0; i < 6; i++){
 		DrawOneLine(50.0 + ((GLfloat)i*50.0), 50.0,
 			50.0 + ((GLfloat)(i + 1)*50.0), 50.0);
 	}

	glDisable(GL_LINE_STIPPLE);
	glFlush();
}

void Reshap(int w,int h)
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