#include<Windows.h>
#include<gl/glut.h>

/* Draw shapes */
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f); // set color to black
	glPointSize(5.0f); // adjust point size
	glColor3f(1.0, 0.0, 0.0); // set color to red

	glBegin(GL_LINES);
	glVertex2i(100, 200);
	glVertex2i(100, 0);

	glVertex2i(100, 0);
	glVertex2i(300, 0);

	glVertex2i(300, 0);
	glVertex2i(300, 200);

	glVertex2i(300, 200);
	glVertex2i(100, 200);

	/* Draw outlined triangle */

	glColor3f(0.0, 0.0, 1.0); // set color to blue
	glVertex2i(200, 300);
	glVertex2i(100, 200);
	glVertex2i(300, 200);
	glVertex2i(200, 300);
	glEnd();
	glFlush();
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Hut");

	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
