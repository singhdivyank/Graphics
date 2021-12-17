#define CONTINUE 1 // to continue playing the game
#define QUIT 0 // exit the game

/* colors */
#define RED 2 
#define GREEN 3
#define BLUE 4
#define BLACK 5
#define C1 8 // color 1
#define C2 9 // color 2
#define C3 10  // color 3
#define GOLD 11
#define ORCHID 12
#define BLACK1 13
#define WHITE 14

/* for spped control */
#define INC 6 // increase the speed
#define DEC 7 // decrease the speed

/* Bricks */
struct bricks {
	float x, y, w, h; // coordinates
	bool alive; // hit or not
}b[45]; //a total of 45 bricks

float red1,red2,green1,green2,blue1,blue2; // alternate rgb sequence for odd and even

/* Ball */
struct ball {
	float ballx, bally, ballwh, velx, vely; // cordinates
	float red, green, blue; // colors
	bool left,right,up,down; // directions
}ball;

/* Block at the bottom to catch the ball */
struct block {
	float myx, myy; // coordinates
	float width, height; // dimensions
	bool lft, rgt; // direction of movement
	float red, green, blue; // colors
}block;

float red=0.0, green=0.0, blue=0.0;

/* all functionalities implemented */

void specialUp(int, int, int); // check for key press
void specialDown(int, int, int);  // check for key release
void reshape(); //modify the co-ordinates of the game objects according to the events
void draw(); // render game objects on the screen
void callMenu(); // create the main pause menu
void processmenu(int); // process the pause menu
void revert(); // for ball movement
void main_menu(int);