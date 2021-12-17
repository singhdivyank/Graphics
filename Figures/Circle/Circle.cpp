#include<windows.h>
#include<GL/glut.h>
#include<iostream>
using namespace std;

int x1, y1, r;

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(4.0);

	circleMidpoint();
	glFlush();
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void circleMidpoint() {
	int x = 0, y = r;
	float decision = 5 / 4 - r;
	setPixel(x, y);

	while (y > x) {
		if (decision < 0.0f) {
			x++;
			decision += 2 * x + 1;
		}
		else {
			y--;
			x++;
			decision += 2 * (x - y) + 1;
		}
		setPixel(x, y);
		setPixel(x, -y);
		setPixel(-x, y);
		setPixel(-x, -y);
		setPixel(y, x);
		setPixel(-y, x);
		setPixel(y, -x);
		setPixel(-y, -x);
	}
}

int main(int argc, char** argv) {
	cout << "Enter coordinates of the center" << endl;
	cin >> x1 >> y1;

	cout << "Specify radius of circle" << endl;
	cin >> r;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("CIRCLE");

	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

	return 0;

}
