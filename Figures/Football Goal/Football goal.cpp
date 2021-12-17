#include "Camera.h" 
#include "Ball.h" 
#include "Board.h"
#include<windows.h> 
#include<GL/glut.h> 
#include<GL/gl.h> 
#include<GL/glu.h> 
#include<cmath> 
#include <iostream> 
#include<stdlib.h>
using namespace std;

int W = 10, D = 8; // for board's width and depth Board board(W,D)
int H = 2; // Height of the goal post

//Just initializes the ball position
double rad = 0.3, Ynew, Znew; // Gives the final position values for y and z coordinates
Ball football = Ball(rad); //radius and coordinates of center of ball
int x = width - 2;

void init() {
	glEnable(GL_DEPTH_TEST); //calculate depth value
	glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE); //sets light properties i.e. light no, parameter(here diffuse light), and color glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
	glMaterialfv(GL_FRONT, GL_SHININESS, RED); //sets material properties i.e. face being lit, parameter, color
	glMaterialf(GL_FRONT, GL_SHININESS, 50); //50 gives the specular exponent of material 143

	glEnable(GL_LIGHTING); //enables lighting
	glEnable(GL_LIGHT0); //enables particular dynamic light, here 0
	board.create();
}

//Draws one frame, the play field then the ball from the current camera position
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT); // clears buffers 
	glLoadIdentity(); //loads identity matrix
	gluLookAt(camera.getX(), camera.getY(), camera.getZ(), board.centerx(), 0.0, board.centerz(), 0.0, 1.0, 0.0); //creates a viewing matrix
	board.draw();
	if (football.state == 0) football.stop(); // Set ball's position to its initial position
	else if (football.state == 1) {
		football.NewPosSet(Ynew, Znew); // Sets new position (x,y,z) with new values of y and z
		football.motion();//Uses linear equations y on x and z on x to give ball a random motion
	}
	else if (football.state == 2) football.jerkback();//Used to jerk back the ball when it touches the net
	else football.gravity(); //bring the ball to the ground
	football.make();//Creates the ball whose center is at a position (x,y,z) initially
	glFlush(); //empties all buffers;forces execution of GL commands in finite time
	glutSwapBuffers(); //flips back buffer with front buffer
}

//On reshape, constructs a camera that perfectly fits the window
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h); //set the viewport rectangle for the current OpenGLcontext 
	glMatrixMode(GL_PROJECTION); //set matrix mode to projection
	glLoadIdentity();
	gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 200.0); //initialize the projection matrix to a perspective projection matrix.
	glMatrixMode(GL_MODELVIEW); //st matrix to model view which is a combination of viewand model(or world) matrix transformation
}

//Requests to draw the next frame
void timer(int v) {
	glutPostRedisplay(); //to tell GLUT that we are ready to render another frame
	glutTimerFunc(1000 / 60, timer, v); //registers a timer callback to be triggered in 1000 / 60 milliseconds.
}

double getRand(double M, double N){ return M + (rand() / (RAND_MAX / (N - M))); } //Gives random number between two double variables M and N 

//Moves the camera according to the key pressed, then ask to refresh the display.
void special(int key, int, int) {
	switch (key) {
		case GLUT_KEY_LEFT: 
			camera.moveLeft();
			break;
		case GLUT_KEY_RIGHT: 
			camera.moveRight(); 
			break;
		case GLUT_KEY_UP: 
			camera.moveUp();
			break;
		case GLUT_KEY_DOWN:
			camera.moveDown(); 
			break;
		case GLUT_KEY_HOME: //Used to give motion to the ball
			football.stop();
			football.state = 1;
			Ynew = getRand(rad + 0.5, H - rad); // get random value between radius of the ball and height of pole - radius(in y axis)
			Znew = getRand(rad + 1, D + rad - 3); // get random value between radius of ball + 1 and sum of total length of base and radius(in z axis)
			break;
		case GLUT_KEY_END: //Used to bring ball to initial position 
			football.stop();
			break;
		}
		glutPostRedisplay();
}

int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //initialize the display mode 
	glutInitWindowPosition(100, 100); //initialize the position of the newly created window
	glutInitWindowSize(1000, 800); //initialize the size of the newly created window 147

	glutCreateWindow("Penalty Kick"); //create the render window using the parameters we have specified before
	glutDisplayFunc(display); //register the callbacks for the GULT event system
	glutReshapeFunc(reshape);
	glutSpecialFunc(special); //Here the glutSpecial refers to keyboard function of Opengl.
	glutTimerFunc(100, timer, 0);
	init();
	glutMainLoop(); //starts the GLUT event processing loop
	
	return 0;
}