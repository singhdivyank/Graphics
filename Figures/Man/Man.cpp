#include <GL/glut.h>
#include <math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define DEG2RAD 3.14159/180.0

void DrawEllipse(float radiusX, float radiusY, int x, int y)
{
	int i;

	glBegin(GL_POLYGON);
	for (i = 0; i < 360; i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(x + cos(rad) * radiusX, y + sin(rad) * radiusY);
	}
	glEnd();
}

void humanBody() {
	glColor3f(0, 0.5, 0.5);
	glPushMatrix();
	glRotatef(-10, 0, 0, 1);
	DrawEllipse(10, 50, 0, 0); //left leg
	glPopMatrix();

	glPushMatrix();
	glRotatef(10, 0, 0, 1);
	DrawEllipse(10, 50, 25, -7); //right leg
	glPopMatrix();
	DrawEllipse(20, 50, 12, 70); //center torso

	glPushMatrix();

	glRotatef(60, 0, 0, 1);
	DrawEllipse(40, 10, 60, 55); // left arm
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 0, 0, 1);
	DrawEllipse(40, 10, -50, 75);// right arm
	glPopMatrix();

	DrawEllipse(15, 25, 12, 135); //head

	glPushMatrix();

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);

	glEnd();

}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	humanBody();
	glFlush();
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-300, 500, -300, 500);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Man");

	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

	return 0;
}
