#include<Windows.h>
#include<gl/glut.h>
#include<iostream>

using namespace std;

/* 4 connected boundary fill */

void flood_fill(int x, int y, float* fillColor, float* bc) {
	float pixels[3];
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);

	if (pixels[0] == bc[0] && pixels[1] == bc[1] && pixels[2] == bc[2]) {
		glColor3f(fillColor[0], fillColor[1], fillColor[2]);
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();

		glFlush();

		flood_fill(x + 1, y, fillColor, bc);
		flood_fill(x, y + 1, fillColor, bc);
		flood_fill(x - 1, y, fillColor, bc);
		flood_fill(x, y - 1, fillColor, bc);
	}
}

/* 8 connected boundary fill */

void flood_fill(int x, int y, float* fillColor, float* bc) {
	float pixels[3];
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, pixels);

	if (pixels[0] == bc[0] && pixels[1] == bc[1] && pixels[2] == bc[2]) {
		glColor3f(fillColor[0], fillColor[1], fillColor[2]);
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();

		glFlush();

		flood_fill(x + 1, y, fillColor, bc);
		flood_fill(x, y + 1, fillColor, bc);
		flood_fill(x - 1, y, fillColor, bc);
		flood_fill(x, y - 1, fillColor, bc);
		flood_fill(x - 1, y - 1, fillColor, bc);
		flood_fill(x - 1, y + 1, fillColor, bc);
		flood_fill(x + 1, y - 1, fillColor, bc);
		flood_fill(x + 1, y + 1, fillColor, bc);
	}
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 640, 0, 480);

}

void myDisplay() {
	glLineWidth(3);
	glPointSize(2);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(150, 100);
	glVertex2i(300, 300);
	glVertex2i(450, 100);
	glEnd();

	glFlush();
}

void mouse(int btn, int state, int x, int y) {
	y = 480 - y;
	if (btn == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			float bColor[] = { 1, 0, 0 };
			float color[] = { 0, 0, 1 };

			flood_fill(x, y, color, bColor);
		}
	}
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 280);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Flood fill algorithm");

	glutDisplayFunc(myDisplay);
	glutMouseFunc(mouse);
	myInit();
	glutMainLoop();
}
