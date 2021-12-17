/*
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include <list>

using namespace std;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

int xmin = 0, ymin = 0, xmax = 0, ymax = 0, enter = 1, sz, st_flag = 1;

float** pts;

class points {
    int x, y;

    public:
        points(int x, int y) {
        this->x = x;
        this->y = y;
        }

        int getx() { return x; }
        int gety() { return y; }
};

class tryo {
    int x, y;

    public:
        void setx(int x) { this->x = x; }
        int getx() { return x; }
};

points* s, * p;
list <points*> in, outer;

void delay(float ms) {
    clock_t goal = ms + clock();
    while (goal > clock());
}

//draw polygon and create the points array
void drawPolygon() {
    glBegin(GL_LINE_LOOP);
        pts = new float* [in.size()];
        
        for (int i = 0; i < in.size(); i++) pts[i] = new float[2];
        
        sz = in.size();
        while (in.size() > 0) {
            points* temp = in.front();
            pts[in.size() - 1][0] = temp->getx();
            pts[in.size() - 1][1] = temp->gety();
            glVertex2i(temp->getx(), temp->gety());
            in.pop_front();
        }
    glEnd();

    glFlush();
}

void redraw() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < sz; i++) glVertex2i(pts[i][0], pts[i][1]);
    glEnd();
    
    glFlush();
    glColor3f(0, 0, 0);
    
    glBegin(GL_LINE_LOOP);
        glVertex2i(xmin, ymin);
        glVertex2i(xmin, ymax);
        glVertex2i(xmax, ymax);
        glVertex2i(xmax, ymin);
    glEnd();
    
    glFlush();
    
    glColor3f(1, 0, 0);
    glLineWidth(1.0);
}

// DEFINE
// 1 -> right edge
// 2 -> bottom edge
// 3 -> left edge
// 4 -> top edge
// xmin,ymin = top left
// xmax,ymax = bottom right

int inside(int x, int y, int clip_edge) {
    switch (clip_edge) {
    case 1: 
        return (x < xmax) ? 1 : 0;
        break;
    case 2: 
        return (y > ymax)?1:0; 
        break;
    case 3: 
        return (x > xmin)?1:0; 
        break;
    case 4: 
        return (y < ymin)?1:0;
        break;
    default: 
        return 0; 
        break;
    }
}

points* intersect(points* S, points* P, int clip_edge) {
    float m; //div by zero error earlier
    
    m = ((P->getx() - S->getx()) == 0)?0:(float)(P->gety() - S->gety()) / (P->getx() - S->getx());

    float c = (float)(S->gety()) - (m * S->getx());

    switch (clip_edge) {
    case 1:
        int x = xmax; 
        int y = (m * x) + c; 
        return (new points(x, y));
        break;
    case 2:
        int y = ymax; 
        int x; 
        x = (m == 0)?P->getx():(y - c) / m; 
        return (new points(x, y));
        break;
    case 3:
        int x = xmin; 
        int y = (m * x) + c; 
        return (new points(x, y));
        break;
    case 4:
        int y = ymin; 
        int x; 
        (m == 0)?P->getx():((y - c) / m); 
        return (new points(x, y));
        break;
    default:
        return;
        break;
    }
}

float** out_to_in(float** inner, list<points*> out) {
    inner = new float* [out.size()];

    for (int i = 0; i < out.size(); i++) inner[i] = new float[2];
    
    sz = out.size();
    
    while (out.size() > 0) {
        points* temp = out.front();
        inner[out.size() - 1][0] = temp->getx();
        inner[out.size() - 1][1] = temp->gety();
        out.pop_front();
    }
    out.empty();
    
    return inner;
}
//Contains debugging statements to re-create clipping as needed

float** SHPC(float** inva, list<points*> out, int clip_edge) {
    s = new points(inva[sz - 1][0], inva[sz - 1][1]);

    for (int j = 0; j < sz; j++) {
        p = new points(inva[j][0], inva[j][1]);
        if (inside(p->getx(), p->gety(), clip_edge)) { // case 1 & 4
            if (inside(s->getx(), s->gety(), clip_edge)) out.push_front(new points(p->getx(), p->gety())); // case 1
            else { // case 4
                points* temp = intersect(s, p, clip_edge);
                out.push_front(temp);
                out.push_front(p);
            }
        }
        else if (inside(s->getx(), s->gety(), clip_edge)) { //case 2
            points* temp = intersect(s, p, clip_edge);
            out.push_front(temp);
        }
        else s = p;
    }

    return out_to_in(inva, out);
}

void key(unsigned char key_t, int x, int y) {
    switch (key_t) {
    case 'd':
        enter = -1;
        drawPolygon();
        in.empty();
        break;
    case 'c':
        pts = SHPC(pts, outer, 1);
        pts = SHPC(pts, outer, 2);
        pts = SHPC(pts, outer, 3);
        pts = SHPC(pts, outer, 4);
        redraw();
        break;
    }
}

void mouse(int btn, int state, int x, int y) {
    y = 480 - y;
    
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN && enter) {
        points* temp = new points(x, y);
        in.push_front(temp);
    }
}

void drag_start(GLint x, GLint y) {
    y = 480 - y;

    if (enter == -1 && st_flag) {
        xmin = x;
        ymin = y;
        st_flag = 0;
    }
    else {
        xmax = x;
        ymax = y;
    }
    redraw();
}

void drag_end(GLint x, GLint y) {
    y = 480 - y;

    if (enter == -1 && st_flag == 0) {
        xmax = x;
        ymax = y;
        st_flag = 1;
        redraw();
    }
}

void world() {
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Sutherland-Hodgeman polygon clipping algorithm");
    glutDisplayFunc(world);
    glutMouseFunc(mouse);
    glutMotionFunc(drag_start);
    glutPassiveMotionFunc(drag_end);
    glutKeyboardFunc(key);

    init();
    glutMainLoop();
    return 0;
}*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
using namespace std;

#define Size 600

typedef float Color[3];

struct Point {
	int x, y;
};

typedef struct IntersectionPoint {
	int pointFlag, index0, index1, dis;
	bool inFlag;

	Point p;
}IP;

class Pg {
	public:
		vector<Point> pts;
		Pg(void);
		~Pg(void);
		
		void drawPgLine(Color c);
};

Pg::Pg() {}
Pg::~Pg(){}

void Pg::drawPgLine(Color c) {
	glColor3fv(c);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
		int size = pts.size();
		for (int i = 0; i < size; i++) glVertex2i(pts[i].x, pts[i].y);
	glEnd();
}

bool isPointInsidePg(Point p, Pg& py) {
	int cnt = 0, size = py.pts.size();

	for (int i = 0; i < size; i++) {
		Point p1 = py.pts[i];
		Point p2 = py.pts[(i + 1) % size];
		
		if (p1.y == p2.y) continue;
		if (p.y < min(p1.y, p2.y)) continue;
		if (p.y >= max(p1.y, p2.y)) continue;
		
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
		
		if (x > p.x) cnt++;
	}
	return (cnt % 2 == 1);
}

int cross(Point& p0, Point& p1, Point& p2) { return ((p2.x - p0.x) * (p1.y - p0.y) - (p1.x - p0.x) * (p2.y - p0.y)); }

bool onSegment(Point& p0, Point& p1, Point& p2) {
	bool segment = false;

	int minx = min(p0.x, p1.x), maxx = max(p0.x, p1.x);
	int miny = min(p0.y, p1.y), maxy = max(p0.y, p1.y);
	
	if (p2.x >= minx && p2.x <= maxx && p2.y >= miny && p2.y <= maxy) segment = true;
	
	return segment;
}

bool segmentsIntersect(Point& p1, Point& p2, Point& p3, Point& p4) {
	bool intersection = false;
	
	int d1 = cross(p3, p4, p1), d2 = cross(p3, p4, p2), d3 = cross(p1, p2, p3), d4 = cross(p1, p2, p4);

	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) return true;
	if (d1 == 0 && onSegment(p3, p4, p1)) intersection = true;
	if (d2 == 0 && onSegment(p3, p4, p2)) intersection = true;
	if (d3 == 0 && onSegment(p1, p2, p3)) intersection = true;
	if (d4 == 0 && onSegment(p1, p2, p4)) intersection = true;

	return intersection;
}

Point getintersectPoint(Point p1, Point p2, Point p3, Point p4) {
	Point p;

	int b1 = (p2.y - p1.y) * p1.x + (p1.x - p2.x) * p1.y;
	int b2 = (p4.y - p3.y) * p3.x + (p3.x - p4.x) * p3.y;
	int D = (p2.x - p1.x) * (p4.y - p3.y) - (p4.x - p3.x) * (p2.y - p1.y);
	int D1 = b2 * (p2.x - p1.x) - b1 * (p4.x - p3.x);
	int D2 = b2 * (p2.y - p1.y) - b1 * (p4.y - p3.y);
	
	p.x = D1 / D;
	p.y = D2 / D;
	
	return p;
}

void generateIntersectPoints(Pg& pyclip, Pg& py, list<IP>& iplist) {
	int clipSize = pyclip.pts.size(), pySize = py.pts.size();

	for (int i = 0; i < clipSize; i++) {
		Point p1 = pyclip.pts[i];
		Point p2 = pyclip.pts[(i + 1) % clipSize];

		for (int j = 0; j < pySize; j++) {
			Point p3 = py.pts[j];
			Point p4 = py.pts[(j + 1) % pySize];
			
			if (segmentsIntersect(p1, p2, p3, p4)) {
				IP ip;
				
				ip.index0 = j;
				ip.index1 = i;
				ip.p = getintersectPoint(p1, p2, p3, p4);
				
				iplist.push_back(ip);
			}
		}
	}
}

int getDistance(Point& p1, Point& p2) {	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y); }

bool distanceComparator(IP& ip1, IP& ip2) { return ip1.dis < ip2.dis; }

void generateList(Pg& py, list<IP>& iplist, list<IP>& comlist, int index) {
	int size = py.pts.size();
	list<IP>::iterator it;

	for (int i = 0; i < size; i++) {
		Point p1 = py.pts[i];
		IP ip;
		
		ip.pointFlag = 0;
		ip.p = p1;
		
		comlist.push_back(ip);
		
		list<IP> oneSeg;
		
		for (it = iplist.begin(); it != iplist.end(); it++) {
			if ((index == 0 && i == it->index0) || (index == 1 && i == it->index1)) {
				it->dis = getDistance(it->p, p1);
				it->pointFlag = 1;

				oneSeg.push_back(*it);
			}
		}

		oneSeg.sort(distanceComparator);
		for (it = oneSeg.begin(); it != oneSeg.end(); it++) comlist.push_back(*it);
	}
}

void getPgPointInOut(list<IP>& Pglist, Pg& pyclip) {
	bool inFlag;

	list<IP>::iterator it;
	
	for (it = Pglist.begin(); it != Pglist.end(); it++) {
		if (it->pointFlag == 0) inFlag = (isPointInsidePg(it->p, pyclip))?true:false;
		else {
			inFlag = !inFlag;
			it->inFlag = inFlag;
		}
	}
}

bool operator==(Point& p1, Point& p2) {	return p1.x == p2.x && p1.y == p2.y; }

void getClipPointInOut(list<IP>& cliplist, list<IP>& Pglist) {
	list<IP>::iterator it, it1;
	
	for (it = cliplist.begin(); it != cliplist.end(); it++) {
		if (it->pointFlag == 0) continue;
		
		for (it1 = Pglist.begin(); it1 != Pglist.end(); it1++) {
			if (it1->pointFlag == 0) continue;
			if (it->p == it1->p) it->inFlag = it1->inFlag;
		}
	}
}

void generateClipArea(list<IP>& Pglist, list<IP>& cliplist) {
	list<IP>::iterator it, it1;
	Pg py;
	Color c = { 0.0, 0.0, 1.0 };

	for (it = Pglist.begin(); it != Pglist.end(); it++) {
		if (it->pointFlag == 1 && it->inFlag) break;
	}

	py.pts.clear();

	while (true) {
		if (it == Pglist.end()) break;

		py.pts.push_back(it->p);
		
		for (; it != Pglist.end(); it++) {
			if (it->pointFlag == 1 && !it->inFlag) break;
			py.pts.push_back(it->p);
		}
		
		for (it1 = cliplist.begin(); it1 != cliplist.end(); it1++) {
			if (it1->p == it->p) break;
		}

		for (; it1 != cliplist.end(); it1++) {
			if (it1->pointFlag == 1 && it1->inFlag) break;
			
			py.pts.push_back(it1->p);
		}

		if (py.pts[0] == it1->p) {
			py.drawPgLine(c);
			py.pts.clear();
			
			for (; it != Pglist.end(); it++) {
				if (it->pointFlag == 1 && it->inFlag) break;
			}
			continue;
		}

		for (; it != Pglist.end(); it++) {
			if (it->p == it1->p) break;
		}
	}
}

void weilerAtherton(Pg& pyclip, Pg& py) {
	list<IP> iplist, Pglist, cliplist;
	
	generateIntersectPoints(pyclip, py, iplist);
	generateList(py, iplist, Pglist, 0);
	generateList(pyclip, iplist, cliplist, 1);

	getPgPointInOut(Pglist, pyclip);

	getClipPointInOut(cliplist, Pglist);

	generateClipArea(Pglist, cliplist);
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Size - 1, 0.0, Size - 1);
}

void GenerateRandomSimplePg(Pg& G, int M) {
	Point P;
	G.pts.clear();
	
	for (int i = 0; i < M; ++i) {
		bool flag;
		
		do {
			P.x = rand() % Size;
			P.y = rand() % Size;
			
			flag = true;
			
			for (int j = 1; j < i - 1; ++j) {
				if (segmentsIntersect(G.pts[j - 1], G.pts[j], G.pts[i - 1], P)) {
					flag = false;
					break;
				}
			}
			if (flag && i == M - 1) {
				for (int j = 2; j < i; ++j)
					if (segmentsIntersect(G.pts[j - 1], G.pts[j], P, G.pts[0])) {
						flag = false;
						break;
					}
			}
		} while (!flag);
		G.pts.push_back(P);
	}
}

void KeyboardAction(unsigned char key, int x, int y) { exit(0); }

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_POINT_SMOOTH);

	Pg pyclip, py;

	Point p1, p2, p3, p4;
	p1.x = 553, p1.y = 495;
	p2.x = 351, p2.y = 175;
	p3.x = 486, p3.y = 71;
	p4.x = 61, p4.y = 86;

	pyclip.pts.push_back(p1);
	pyclip.pts.push_back(p2);
	pyclip.pts.push_back(p3);
	pyclip.pts.push_back(p4);

	Point p5, p6, p7, p8;
	p5.x = 390, p5.y = 424;
	p6.x = 579, p6.y = 585;
	p7.x = 257, p7.y = 112;
	p8.x = 68, p8.y = 245;
	py.pts.push_back(p5);
	py.pts.push_back(p6);
	py.pts.push_back(p7);
	py.pts.push_back(p8);

	int size = pyclip.pts.size();
	for (int i = 0; i < size; ++i) cout << pyclip.pts[i].x << " " << pyclip.pts[i].y << endl;
	cout << endl;
	size = py.pts.size();
	for (int i = 0; i < size; ++i) cout << py.pts[i].x << " " << py.pts[i].y << endl;

	Color a = { 1.0, 0.0, 0.0 };
	Color b = { 0.0, 1.0, 0.0 };

	py.drawPgLine(a);
	pyclip.drawPgLine(b);
	weilerAtherton(pyclip, py);

	glFlush();
}

int main(int argc, char** argv) {
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Size, Size);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Weiler-Atherton Clipping Algorithm");
	glutKeyboardFunc(KeyboardAction);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}