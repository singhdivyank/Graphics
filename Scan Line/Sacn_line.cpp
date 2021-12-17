#include<Windows.h>
#include<gl/glut.h>
#include<iostream>
using namespace std;

GLdouble x1, y1, x2, y2, x3, y3, x4, y4;

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();

	scanfill(x1, y1, x2, y2, x3, y3, x4, y4); // function implementing scan line fill algorithm
	glFlush();
}

void scanfill(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
	int le[500], int re[500], i;

	for (i = 0; i < 500; i++) {
		le[i] = 500;
		re[i] = 0;
	}

	edgedetect(x1, y1, x2, y2, le, re);
	edgedetect(x2, y2, x3, y3, le, re);
	edgedetect(x3, y3, x4, y4, le, re);
	edgedetect(x4, y4, x1, y1, le, re);

	for (int j = 0; j < 500; j++) {
		if (le[j] <= re[j]) {
			for (i = le[j]; i < re[j]; i++) draw_pixel(i, j);
		}
	}
}

void edgedetect(double x1, double y1, double x2, double y2, int* le, int* re) {
	float temp, x, mx;
	int i;

	if (y1 > y2) {
		/* Swap x1 and x2 */
		temp = x1;
		x1 = x2;
		x2 = temp;

		/* Swap y1 and y2 */
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	mx = (y1 == y2) ? x2 - x1 : (x2 - x1) / (y2 - y1);

	x = x1;

	for (i = (int)y1; i <= (int)y2; i++) {
		if (x < (float)le[i]) le[i] = (int)x;
		if (x > (float)re[i]) re[i] = (int)x;

		x += mx;
	}
}

void draw_pixel(int x, int y) {
	glColor3f(0.0, 1.0, 1.0);
	glPointSize(1.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void main(int argc, char** argv) {
	cout << "Enter coordinates: x1, y1, x2, y2, x3, y3,  x4, y4" << endl;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Scan line algo");

	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
