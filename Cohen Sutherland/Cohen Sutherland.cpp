/*
#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<iostream>
using namespace std;

void display();

float xmin = -100, ymin = -100, xmax = 100, ymax = 100, xd1, yd1, xd2, yd2;

void init() {
    glClearColor(0.0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300, 300, -300, 300);

}

int code(float x, float y) {
    int c = 0;

    if (y > ymax) c = 8;
    if (y < ymin) c = 4;
    if (x > xmax) c = c | 2;
    if (x < xmin) c = c | 1;
    
    return c;
}

void cohen_Line(float x1, float y1, float x2, float y2) {
    int c1 = code(x1, y1), c2 = code(x2, y2);
    float m = (y2 - y1) / (x2 - x1);

    while ((c1 | c2) > 0) {
        if ((c1 & c2) > 0) exit(0);

        float xi = x1, yi = y1;
        int c = c1;

        if (c == 0) {
            c = c2;
            xi = x2;
            yi = y2;
        }

        float x, y;
        
        if ((c & 8) > 0) {
            y = ymax;
            x = xi + 1.0 / m * (ymax - yi);
        }
        else {
            if ((c & 4) > 0) {
                y = ymin;
                x = xi + 1.0 / m * (ymin - yi);
            }
            else {
                if ((c & 2) > 0) {
                    x = xmax;
                    y = yi + m * (xmax - xi);
                }
                else {
                    if ((c & 1) > 0) {
                        x = xmin;
                        y = yi + m * (xmin - xi);
                    }
                }
            }
        }

        if (c == c1) {
            xd1 = x;
            yd1 = y;
            c1 = code(xd1, yd1);
        }

        if (c == c2) {
            xd2 = x;
            yd2 = y;
            c2 = code(xd2, yd2);
        }
    }

    display();
}

void mykey(unsigned char key, int x, int y) {
    if (key == 'c') {
        cout << "Hello";
        cohen_Line(xd1, yd1, xd2, yd2);
        glFlush();
    }
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_LINE_LOOP);
        glVertex2i(xmin, ymin);
        glVertex2i(xmin, ymax);
        glVertex2i(xmax, ymax);
        glVertex2i(xmax, ymin);
    glEnd();
    
    glColor3f(1.0, 0.0, 0.0);
    
    glBegin(GL_LINES);
        glVertex2i(xd1, yd1);
        glVertex2i(xd2, yd2);
    glEnd();
    
    glFlush();
}

int main(int argc, char** argv) {
    cout<<"Enter line co-ordinates:"<<endl;
    cin >> xd1 >> yd1 >> xd2 >> yd2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
    
    init();
    glutMainLoop();
    
    return 0;
}*/

#include<windows.h>
#include<GL/glut.h>

int x1 = -80, x2 = 0, y3 = -80, y2 = 0, xmin = -50, ymin = -50, xmax = 50, ymax = 50;
float u1 = 0, u2 = 1;
double p[4], q[4];  // changed from int to double thats it

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-320, 320, -240, 240);
}

void clip(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1, dy = y2 - y1, i;
    double t;

    p[0] = -dx; q[0] = x1 - xmin;
    p[1] = dx; q[1] = xmax - x1;
    p[2] = -dy; q[2] = y1 - ymin;
    p[3] = dy; q[3] = ymax - y1;

    for (i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) return;

        if (p[i] < 0) {
            t = (q[i]) / (p[i]);  // This calculation was returning a zero because both q and p were int
            if (t > u1 && t < u2) u1 = t;
        }

        else if (p[i] > 0) {
            t = (q[i]) / (p[i]);  // This calculation was returning a zero because both q and p were int
            if (t > u1 && t < u2) u2 = t;
        }
    }

    if (u1 < u2) {
        x1 = x1 + u1 * (x2 - x1);
        y1 = y1 + u1 * (y2 - y1);
        x2 = x1 + u2 * (x2 - x1);
        y2 = y1 + u2 * (y2 - y1);
        
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
        glEnd();
        
        glFlush();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    
    glBegin(GL_LINES);
        glVertex2i(x1, y3);
        glVertex2i(x2, y2);
    glEnd();
    
    glFlush();
}

void myKey(unsigned char key, int x, int y) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (key == 'c') {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        glColor3f(0.0, 0.0, 0.0);
        
        glBegin(GL_LINES);
            glVertex2i(-50, -50);
            glVertex2i(-50, 50);
            glVertex2i(-50, 50);
            glVertex2i(50, 50);
            glVertex2i(50, 50);
            glVertex2i(50, -50);
            glVertex2i(50, -50);
            glVertex2i(-50, -50);
        glEnd();
        
        glFlush();
        clip(::x1, y3, x2, y2);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Liang-Barskey algorithm");
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);

    init();
    glutMainLoop();
    
    return 0;
}