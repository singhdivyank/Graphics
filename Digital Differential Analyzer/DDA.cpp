#include<windows.h>
#include<GL/GL.h>
#include<gl/glut.h>
#include<iostream>
#include<math.h>
using namespace std;

GLdouble x1, y1, x2, y2;

void myDisplay(void) {
	GLdouble dx = x2 - x1, dy = y2 - y1, steps;
	float xinc, yinc, x = x1, y = y1;

	steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
	xinc = dx / (float)steps;
	yinc = dy / (float)steps;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	for (int k = 0; k < steps; k++) {
		x += xinc;
		y += yinc;
		glVertex2d(x, y);
	}
	glEnd();
	glFlush();
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void main(int argc, char** argv) {

	cout << "Specify two points for line drawing (x1, y1):" << endl;
	cin >> x1 >> y1;
	cout << "Now specify (x2, y2)" << endl;
	cin >> x2 >> y2;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("DDA");


	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
