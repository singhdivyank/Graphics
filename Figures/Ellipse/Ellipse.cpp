/* Mid-point ellipse algo */
#include<windows.h>
#include<GL/GLU.h>
#include<gl/glut.h>
#include<math.h>
#include<iostream>
using namespace std;

GLint rx, ry; // semi major and semi minor axis
GLint xCenter, yCenter; // center of ellipse

GLint x, y, dx, dy;
GLdouble p1, p2;

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(4.0);

	ellipseMidpoint();
	glFlush();
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void setPixel(GLint x, GLint y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void ellipseMidpoint() {
	/* Region 1*/

	x = 0, y = ry;
	p1 = pow(ry, 2) - pow(rx, 2) * ry + pow(rx, 2) * 0.25;
	dx = 2 * pow(ry, 2) * x, dy = 2 * pow(rx, 2) * y;

	while (dx < dy) {
		setPixel(xCenter + x, yCenter + y);
		setPixel(xCenter - x, yCenter + y);
		setPixel(xCenter + x, yCenter - y);
		setPixel(xCenter - x, yCenter - y);

		if (p1 < 0) {
			x += 1;
			dx = 2 * pow(ry, 2) * x;
			p1 += dx + pow(ry, 2);
		}
		else {
			x += 1;
			y -= 1;
			dx = 2 * pow(ry, 2) * x;
			dy = 2 * pow(rx, 2) * y;
			p1 += dx - dy + pow(ry, 2);
		}
	}

	/* Region 2 */
	p2 = pow(ry, 2) * pow(x + 0.5, 2) + pow(rx, 2) * pow(y - 1, 2) - pow(rx, 2) * pow(ry, 2);

	while (y > 0) {
		setPixel(xCenter + x, yCenter + y);
		setPixel(xCenter - x, yCenter + y);
		setPixel(xCenter + x, yCenter - y);
		setPixel(xCenter - x, yCenter - y);
		if (p2 > 0) {
			x = x;
			y -= 1;
			dy = 2 * pow(rx, 2) * y;
			p2 -= dy + pow(rx, 2);
		}
		else {
			x += 1;
			y -= 1;
			dy -= 2 * pow(rx, 2);
			dx += 2 * pow(ry, 2);
			p2 += dx - dy + pow(rx, 2);
		}
	}
}

int main(int argc, char** argv) {
	cout << "Enter center of ellipse" << endl;
	cin >> xCenter >> yCenter;

	cout << "Enter semi major axis" << endl;
	cin >> rx;


	cout << "Enter semi minor axis" << endl;
	cin >> ry;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("ELLIPSE");

	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

	return 0;
}
