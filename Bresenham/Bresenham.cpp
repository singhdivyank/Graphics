#include<Windows.h>
#include<gl/glut.h>
#include<gl/GL.h>
#include<iostream>
#include<math.h>
using namespace std;

GLdouble x, y, x1, x2, y1, y2, dx, dy, p, m; // m is slope

void myDisplay(void) {
	x = x1, y = y1; // two parameters x and y

	dx = x2 - x1, dy = y2 - y1;
	dx == 0 ? m = dy : m = dy / dx; // initialise m

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	if (m < 1 && m>0) {
		p = 2 * dy - dx;
		for (int k = 0; k < abs(dx - 1); k++) {
			if (p < 0) {
				x += 1;
				glVertex2f(x, y);
				p += 2 * dy;
			}
			else {
				x += 1;
				y += 1;
				glVertex2f(x, y);
				p += 2 * dy - dx;
			}
		}
	}
	else if (m > 1) {
		p = 2 * (dx - dy);
		for (int k = 0; k < abs(dy - 1); k++) {
			if (p < 0) {
				y += 1;
				glVertex2f(x, y);
				p += 2 * dx;
			}
			else {
				x += 1;
				y += 1;
				glVertex2f(x, y);
				p += 2 * (dx - dy);
			}
		}
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

	cout << "Specify the point for drawing line (x1, y1): " << endl;
	cin >> x1 >> y1;
	cout << "Specify the point for drawing the line (x2, y2): " << endl;
	cin >> x2 >> y2;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Bresenham");

	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
