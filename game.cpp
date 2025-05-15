#include <iostream>
#include <string>
#include <cmath>
#include "util.h"
#include<random>
#include<ctime>

//CLASS NUMER 1 <.......................................PADDLE CLASS...............................................>

class Paddle 
{
    int x, y;       // x and y coordinates of paddle
    int w, h;      //width and height of the paddle
    int colorNo;  // for changing the color of paddle upon collision with ball 

public:
    Paddle() : x(0), y(0), w(0), h(0) {}//DEFAULT CONSTRUCTOR

    Paddle(int Xcor, int Ycor, int wid, int hei) : x(Xcor), y(Ycor), w(wid), h(hei) {}//PARAMETEROZED CONSTRUCTOR


// GETTER AND SETTERS 
    void setX(int a) 
    {
        x = a;
    }

    void setY(int b) 
    {
        y = b;
    }

    int getX() const 
    {
        return x;
    }

    int getY() const 
    {
        return y;
    }

    int getWid() const 
    {
        return w;
    }

    int getHei() const 
    {
        return h;
    }
    void setColor(int col)//for changing color on ball touch
    {
    	colorNo=col;
    }
    int getColor()
    {
    	return colorNo;
    }
    
//MEMBER FUNCTIONS

    void draw() const // FUNCTION TO DRAW AND CHANGE THE PADDLE COLOR UPON COLLISION
    {
        switch (colorNo) 
        {
            case 0:
                DrawRoundRect(x, y, w, h, colors[DARK_GREEN], 10);
                break;
            case 1:
                DrawRoundRect(x, y, w, h, colors[RED], 10);
                break;
            case 2:
                DrawRoundRect(x, y, w, h, colors[BLUE], 10);
                break;
            case 3:
                DrawRoundRect(x, y, w, h, colors[YELLOW], 10);
                break;
            case 4:
                DrawRoundRect(x, y, w, h, colors[HOT_PINK], 10);
                break;
            default:
                // Default color if colorNo is out of range
                DrawRoundRect(x, y, w, h, colors[GRAY], 10);
                break;
        }
    }

    void setSize(int a) // Setting the size of paddle for the power ups and downs
    {
    if(a>40 && a<400)
    {
        w = a;
    }
        
    }

    void updatePosition(int xx, int screenSize) // for movement of paddle in frame of 1000x1000
    {
        x = xx - w / 2;
        if (x < 0) 
        {
            x = 0;
        }
        if (x + w > screenSize) 
        {
            x = screenSize - w;
        }
    }
    void setVal(int a,int b,int c,int d)
    {
	    x=a;
	    y=b;
	    w=c;
	    h=d;
    }
    
};
//........................................................................................................................//
//Paddle class holds the functionality of the paddle such as movements, color change and drawing the paddle. The functionality of power up and down for paddle is also controlled by its member function.



//CLASS NO 2 <..................................................CLASS BRICK................................................>

class Brick 
{
    int x, y;
    int colorNo;
    bool finish;  //for checking if brick is present or not

public:
    int touch = 0;//for counting the bounces with bricks
    static const int MAX_BRICKS = 48;//MAX NO OF BRICKS FOR LEV 1
   
    
    
    Brick() : x(0), y(0), finish(false), colorNo((rand() % 5)), touch(0) {}//default const

    Brick(int xp, int yp, int col) : x(xp), y(yp), finish(false), colorNo(col), touch(0) {}//parameterized const

    void addTouch() 
    {
        touch++;
    }

    int getTouches() const 
    {
        return touch;
    }
    int getColor()
    {
    	return colorNo;
    }
    bool canBeDestroyed() const //Bool to check if the brick is ready to break based upon collisions 
    {
        switch (colorNo) {
        case 0:
            return touch >= 0;
        case 1:
            return touch >= 2;
        case 2:
            return touch >= 2;
        case 3:
            return touch >= 1;
        case 4:
            return touch >= 1;
        default:
            return false;
        }
        return false;
    }

    int getColor() const 
    {
        return colorNo;
    }

    int getX() const 
    {
        return x;
    }

    int getY() const 
    {
        return y;
    }

    int getWidth() const 
    {
        return 100;
    }

    int getHeight() const 
    {
        return 25;
    }

    bool destroyed() const 
    {
        return finish;
    }

    void destroy() 
    {
        finish = true;
    }
   
    void draw() const //draw random bricks on basis of colors
    {
        if (!finish) 
        {
            if (colorNo == 0)
                DrawRectangle(x, y, 100, 25, colors[DARK_GREEN]);
            else if (colorNo == 1)
                DrawRectangle(x, y, 100, 25, colors[RED]);
            else if (colorNo == 2)
                DrawRectangle(x, y, 100, 25, colors[BLUE]);
            else if (colorNo == 3)
                DrawRectangle(x, y, 100, 25, colors[YELLOW]);
            else if (colorNo == 4)
                DrawRectangle(x, y, 100, 25, colors[HOT_PINK]);
        }
    }


    bool isGreenBrick() const 
    {
        return colorNo == 0;
    }

    bool isRedBrick() const 
    {
        return colorNo == 1;
    }

    bool isBlueBrick() const 
    {
        return colorNo == 2;
    }

    bool isYellowBrick() const 
    {
        return colorNo == 3;
    }
    bool isPinkBrick() const 
    {
        return colorNo == 4;
    }
};
//....................................................................................................................//
// In this class, all the properties of a brick are handled from drawing to changing the color of bricks upon collision and a boolean for checking if the brick is in the state of being destroyed based upon the number of collisions wrt each color of brick


//CLASS NO 3<...............................................BALL CLASS.................................................>

class Ball 
{
    int x, y, rad;//x and y coordinates of ball
    float x1, y1; // for keeping the speed of ball 
    int colorNo; // fpr changing the clor of ball wrt the bricks

public:
    bool ballPassed;// For checking if bal has passed the paddle to decrement the lives count

    Ball() : x(0), y(0), rad(0), x1(0), y1(0), ballPassed(false) {}//DEFAULT CONSTRUCTOR

    Ball(int xp, int yp, int r, float dx, float dy) : x(xp), y(yp), rad(r), x1(dx), y1(dy), ballPassed(false) {}//PARAMETERIZED CONSTRUCTOR

    void moveBall() //for continuous movement in the screen boundry
    {
        x += x1;
        y += y1;
        if (x - rad < 0 || x + rad > 1000) 
        
        {
            x1 = -x1;
        }
        if (y - rad < 0 || y + rad > 1000) {
            y1 = -y1;
        }
    }

    void drawBall() const // Drawing and changing the color of ball wrt the brick color upon collision
    {
    switch (colorNo) 
    {
        case 0:
            DrawCircle(x, y, rad, colors[DARK_GREEN]);
            break;
        case 1:
            DrawCircle(x, y, rad, colors[RED]);
            break;
        case 2:
            DrawCircle(x, y, rad, colors[BLUE]);
            break;
        case 3:
            DrawCircle(x, y, rad, colors[YELLOW]);
            break;
        case 4:
            DrawCircle(x, y, rad, colors[PINK]);
            break;
        default:
            DrawCircle(x, y, rad, colors[WHITE]);//STARTING COLOR
            break;
    }
}

//MEMBER FUNCTION TO CHECK THE COLLISION OF THE BALL WITH THE BRICK AND IF COLLIDES THEN BREAK THE BRICK IF THE NO OF BOUNCES ARE COMPLETE
// IT IS  SET TO BOOL SO THAT WHEN IT BREAKS THE BRICK IT ACTIVATES THE POWER FOOD SO IT RETURN BOOLEAN VALUE '1' OR '0'
    bool brickCollision(Brick& currentBrick)          //check if brick 
    {
        if (! currentBrick.destroyed())                //if the current brick is not destroyed yet
        {
            if (x + rad >= currentBrick.getX() &&     // and if the ball collides with the brick
                x - rad <= currentBrick.getX() + currentBrick.getWidth() &&
                y + rad >= currentBrick.getY() &&
                y - rad <= currentBrick.getY() + currentBrick.getHeight()) 
                {
                y1 = -y1;
                setColor(currentBrick.getColor());
                if (currentBrick.canBeDestroyed())     // check whether the brick is in breaking state wrt the no of collisions or not , if yes than
                {
                    currentBrick.destroy();	       // destroy the brick
                    return true;
                    
                } else {
                    currentBrick.touch++;	      //other-wise increase the touch count 
                    return false;
                }
            }
        }

    }


    void paddleTouch(Paddle& gamePaddle) // for controlling the ball when it touches the paddle
    {
        int paddleCenterX = gamePaddle.getX() + gamePaddle.getWid() / 2;//center of paddle x cord + width
        int paddleWidthHalf = gamePaddle.getWid() / 2;	//half the width ofpaddle


		//condition if the ball touch paddle
        if (y - rad <= gamePaddle.getY() + gamePaddle.getHei() &&
            x >= gamePaddle.getX() &&
            x <= gamePaddle.getX() + gamePaddle.getWid()) 
            {
        int ballColor = getColor();     // Get the color of the ball

        
        switch (ballColor)              // Update paddle color based on ball color
        {
            case 0:
                gamePaddle.setColor(0); // Update paddle color to DARK_GREEN
                break;
            case 1:
                gamePaddle.setColor(1); // Update paddle color to RED
                break;
            case 2:
                gamePaddle.setColor(2); // Update paddle color to BLUE
                break;
            case 3:
                gamePaddle.setColor(3); // Update paddle color to YELLOW
                break;
            case 4:
                gamePaddle.setColor(4); // Update paddle color to PINK
                break;
            default:
                
                break;
        }
//changing the directions of ball after bouncing from the paddle
            float reflect = x - paddleCenterX;
            y1 = -y1;
		// formula for the ball boncing from paddle
            float angle = 60 * (reflect / paddleWidthHalf);
            float radAngle = angle * M_PI / 180.0;
            float newVelocityX = sin(radAngle) * abs(y1);
            x1 = newVelocityX;
        }
    }

    void setVal(int xp, int yp, int r, int dx, int dy) //resetting the values for ball
    {
        x = xp;
        y = yp;
        rad = r;
        x1 = dx;
        y1 = dy;
    }
    void setColor(int col)
    {
    	colorNo=col;
    }
    int getColor()
    {
    	return colorNo;
    }
    int getY() const 
    {
        return y;
    }

    int getX() const 
    {
        return x;
    }

    int getRad() const 
    {
        return rad;
    }
     void setSpeed(int vx,int vy) //FOR POWER UP AND POWER DOWN FOR CHANGING BALLS SPEED
    {
	    x1=vx;
	    y1=vy;
    }

};
//..................................................................................................................//
// IN this class the properties of a ball is controlled. Drawing the ball, changing its color upon collision with brick and it also pass the color to paddle to change the color. 
//More over it handles the collision and breaking of the bricks. the function brick collision takes the object of brick as parameter and check the conditions for the brick to break and if the conditions meet brick collides or breaks otherwise the colllisions are increased to meet desired condition.
// 1st it check if the brick is already destroed or not
//2nd it check if the ball touches the current brick
//3rd it check whether no of collisions are done or left
// if the touches are equal to condition it destroy the brick else it increase the touches

// This class also manages the ball and paddle collision to move ball in 3 directions left right and stright up based upon paddle collision
//..................................................................................................................//



//4th CLASS...................................//POWERFOOD CLASS (POWE UP AND DOWN)...................................>
class PowerFood {
    int x, y;  		// x and y coordinates of the ball
    int shape; 		// 0: triangle (Green), 1: square (Pink), 2: circle (Blue), 3: rectangle (Red), 4: square (Yellow)
    bool active;	// bool to keep track of the powerup and its time of display.

public:
    PowerFood() : x(0), y(0), shape(0), active(false) {}   //default constructor

    PowerFood(int X, int Y, int Shape) : x(X), y(Y), shape(Shape), active(true) {}  //parameterized constructor

    void draw()  // This member function draw different shapes of power ups based upon the brick broaken
    {
       
            switch (shape) 
            {
            case 0: // Green power-up (triangle)
                DrawTriangle(x - 10, y, x + 10, y + 20, x + 20, y, colors[GREEN]);
                break;
            case 1: // Pink power-down (square)
            DrawRectangle(x, y, 40, 12, colors[RED]);
                break;
            case 2: // Blue power-up (circle)
                DrawCircle(x, y, 7, colors[BLUE]);
                break;
            case 3: // Red power-down (rectangle)
                DrawSquare(x, y, 20, colors[YELLOW]);
                break;
            case 4: // Yellow power-up (square)
                DrawSquare(x, y, 20, colors[HOT_PINK]);
                break;
            default:
                break;
            }
        
    }

    void setShape(int c) {
        shape = c;
    }
    void setX(int a) {
        x = a;
    }
    void setY(int b) {
        y = b;
    }

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }

    void remove() {
        active = false;
        x = -5;
        y = -5;
    }

    void move() //move the powerup verticallly downwards
    {
        y -= 3;
    }

    bool belowBoundary() //check if the power up hits the bottom boundry its active status become deactive
    {
    if(y<=0)
	    {
	    active=false;
	    return true;
	    }       
	   return false;
    }

    bool touchingPaddle(Paddle& paddle,Ball & ball) // if the powerfood touches the paddle then perform the functionality as givin in instructions
    {
        int paddleX = paddle.getX();
        int paddleY = paddle.getY();
        int paddleWidth = paddle.getWid();
        int paddleHeight = paddle.getHei();

	if(x >= paddleX && x <= paddleX + paddleWidth && y <= paddleY + paddleHeight)
        {
		active=false; // make it false as the powerup has to finish as it touches the paddle
		
		
	// FUNCTIONALITY OF EACH POWER UP AS IT TOUCH THE PADDLE BASED UPON THE COLOR OF POWERUP
		if(shape==0)
			{
			//DOUBLE PADDLE SIZE
			 paddle.setSize(paddle.getWid() * 2);
			}
		
		else if(shape==1)
			{
			//INCREASE SPEED
			ball.setSpeed(12,12);
		}
		else if(shape==2)
			{
			//DECREASE SPEED
			ball.setSpeed(5,5);
			
		}
		else if(shape==3)
			{
			
			//add balls
			}
		else if(shape==4)
			{
			//DECREASE PADDLE SIZE
			paddle.setSize(paddle.getWid() / 2);
		}
		
		
		
		return true;
        }
        return false;
    }

    int getShape() const  //color nuber getter to draw powerup
    {
        return shape;
        
    }

    bool isActive() const 
    {
        return active;
    }
    bool setActive(int n) // bool to activate the powerup as soon as brick breaks
    {
	    if(n==1)
	    {
	    	active=true;
	    }
	    else
	    {
	   	 active=false;
	    }
    }
};
//...........................................................................................................//
// This class works on power food generation and its application based upon brick collision. it draws moc=ves and impliments the functionality upon power food collision with paddle



// CLASS NO 5 <................GAME CLASS TO MAKE single OBJECT TO CONTROL GAME( Helper Class ).................>
class BrickBreaker
{
public:
    Brick bricks[Brick::MAX_BRICKS];       // Array of bricks from brick class
    Ball gameBall;			   // Object of ball class
    Paddle gamePaddle;		           // object of paddle from paddle class
    PowerFood powerFood[Brick::MAX_BRICKS];// Array of power food equl to size of bricks 
    int lives;
    int score;
    bool gameOver;			   //bool to check game state (lives==0 or not)
    BrickBreaker() : lives(3), score(0) 
    {	
    
	    
	    	//initialize the bricks for starting the game
		const int xBricks = 8;  //no of x bricks(in 1 row)
		const int yBricks = 6;  //no of y bricks(in 1 column)
		int brickWidth = 100;   //width of brick
		int brickHeight = 25;   //height of brick
		int startX = 60;	//starting x position
		int startY = 900;	//starting y position
		int index = 0;

		for (int i = 0; i < xBricks; ++i) {
		    for (int j = 0; j < yBricks; ++j) {
		        int colorNo = (rand() % 5);
		        bricks[index] = Brick(startX + i * (brickWidth + 10), startY - j * (brickHeight + 10), colorNo);
		        powerFood[index].setX(bricks[index].getX()); // initializing the bricks array with x and y positions and random colors
		        powerFood[index].setY(bricks[index].getY()); // initializing the powerup array with same x and y coordinate and colors
		        powerFood[index].setShape(colorNo);
		        index++;
		    }
		}
		gameOver=false;

		gameBall = Ball(475, 200, 10, 0, 8); // initialize the ball object with parameterized constructor
		gamePaddle = Paddle(430, 100, 150, 25);// initializing the paddle with parameterized constructor
    }
};

void SetCanvasSize(int width, int height) 
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}




// the only global onject for controlling the rest of classes (composition)
	BrickBreaker game;

void GameDisplay() 
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);



// DISPLAYS SCORE AND LIVES COUNT AND NAME + ROLL-NO
    DrawString(30, 30, "SCORE: " + to_string(game.score), colors[MISTY_ROSE]);
    DrawString(30, 60, "LEVEL #1 - Lives: " + to_string(game.lives), colors[RED]);
    DrawString(300,30,"MUHAMMAD WAJDAN 23I-0033 AI-A",colors[RED]);

//DRAW THE BOUNDRY LINES
    DrawLine(0, 0, 0, 1000, 20, colors[GREEN]);
    DrawLine(0, 1000, 1000, 1000, 20, colors[GREEN]);
    DrawLine(1000, 1000, 1000, 0, 20, colors[GREEN]);
    DrawLine(1000, 0, 0, 0, 20, colors[GREEN]);


//DRAW THE BRICKS ONLY IF THEY ARE NOT DESTROYED
    for (int i = 0; i < 48; ++i) {
        if (!game.bricks[i].destroyed()) {
            game.bricks[i].draw();
        }
    }
//DRAW THE POWER-UPS
    for (int i=0;i<48;i++)
    {
	   if( game.powerFood[i].isActive()==1)
	   {
	  	 game.powerFood[i].draw();
	  	 game.powerFood[i].move();
	  	 game.powerFood[i].belowBoundary();
	  	 game.powerFood[i].touchingPaddle(game.gamePaddle,game.gameBall);
	   }
    }
    
//DRAW BALL AND PADDLE
    game.gameBall.drawBall();
    game.gamePaddle.draw();

//CHECK IF THE GAME IS OVER THEN DISPLAY THE MESSAGE
    if (game.gameOver) {
        DrawString(300, 500, "GAME ENDED... PRESS (ESC) TO EXIT", colors[RED]);
        DrawString(300, 400, "Press (A) to start again", colors[RED]);
    }
    //IF LEVEL REACHES MAX SCORE DISPLAY MESSAGE
    if (game.score == 480) {
        DrawString(300, 500, "LEVEL 1 COMPLETED :)", colors[RED]);
    }

    glutSwapBuffers();
}



void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        int x = game.gamePaddle.getX();
        int wid = game.gamePaddle.getWid();
        int x2 = x + 10;
        if (x2 + wid <= 1000) {
            game.gamePaddle.updatePosition(x2, 1000);
        }
    } else if (key == GLUT_KEY_RIGHT) {
        int x = game.gamePaddle.getX();
        int wid = game.gamePaddle.getWid();
        int x2 = x + 10;
        if (x2 - wid >= 0) {
            game.gamePaddle.updatePosition(x2, 1000);
        }
    }
    glutPostRedisplay();
}
void Timer(int m) 
{

    // MOVE THE BALL 
    game.gameBall.moveBall();


    //CHECK IF THE BRICKS ARE NOT BROKEN THEN CHECK BY CALLING THE brickCollision FUNCTION IF BRICK IS READY TO BREAK, BREAK IT AND PUT POWERUP STATUS ACTIVE
	for (int i=0 ; i < Brick::MAX_BRICKS ; ++i) 
	{
	    if (!game.bricks[i].destroyed()) 
	    {
	       if(game.gameBall.brickCollision(game.bricks[i]) ==1) // if the bricks are ready to break, bool will return true (1) which will active the powerup status
		  {
		 	 game.powerFood[i].setActive(1);
		  }
	     
	    }
	}

        
    game.gameBall.paddleTouch(game.gamePaddle); // paddle collision with ball 

    if (game.gameBall.getY() < game.gamePaddle.getY()) //if game ball y coordinate passes the paddles y coordinate, set the bool true
    {
        game.gameBall.ballPassed = true;
    }

    if (game.gameBall.ballPassed && game.gameBall.getY() < game.gamePaddle.getY()) //if the bool ballPassed is true decreament live by 1
    {
        game.lives--;
        game.gameBall.ballPassed = false; // set bool again to false
        if (game.lives == 0) 		  // if lives become 0 then
        {
            game.gameOver = true;	  // set the gameOver true and it will display game over in displayGame function
            glutSwapBuffers();
            return;
        } 
        else 
        {
            game.gameBall.setVal(475, 200, 10, 0, 8); //if lives are still left initialize the ball again
        }
    }

   
    int destroyedBricks = 0; // count for score 
    for (int i = 0; i < 48; ++i) 
    {
        if (game.bricks[i].destroyed()) 
        {
            destroyedBricks++;
        }
    }
    game.score = destroyedBricks * 10; // no of destroyed bricks * 10 will increament score by 10
    glutPostRedisplay();
    glutTimerFunc(16, Timer, 0); 
}



void PrintableKeys(unsigned char key, int x, int y) 
{
    if (key == 27) {
        exit(1);
    }

//RE-START THE GAME
    if (game.gameOver) 
    {
        if (key == 'a' || key == 'A') {
            game.gameOver = false;
            game.lives = 3;
            game.score = 0;

            const int xBricks = 8;
            const int yBricks = 6;
            int brickWidth = 100;
            int brickHeight = 25;
            int startX = 60;
            int startY = 900;
            int index = 0;

            for (int i = 0; i < xBricks; ++i) {
                for (int j = 0; j < yBricks; ++j) {
                    int colorNo = rand() % 5;
                    game.bricks[index] = Brick(startX + i * (brickWidth + 10), startY - j * (brickHeight + 10), colorNo);
                    game.powerFood[index].setX(game.bricks[index].getX()); // initializing the bricks array with x and y positions and random colors
		    game.powerFood[index].setY(game.bricks[index].getY()); // initializing the powerup array with same x and y coordinate and colors
		    game.powerFood[index].setShape(colorNo);
                    index++;
                }
            }

            game.gameBall.setVal(470, 200, 10, 0, 8);
            game.gamePaddle.setVal(430,100,150,25);
            glutTimerFunc(16, Timer, 0);
        }
    }

    glutPostRedisplay();
}




void MousePressedAndMoved(int x, int y) 
{
    cout << x << " " << y << endl;
    glutPostRedisplay();
}



void MouseMoved(int x, int y) // for moving the paddle with mouse
{
    game.gamePaddle.updatePosition(x, 1000);
    glutPostRedisplay();
}




void MouseClicked(int button, int state, int x, int y)
 {
    if (button == GLUT_LEFT_BUTTON) {
        cout << GLUT_DOWN << " " << GLUT_UP << endl;
    } else if (button == GLUT_RIGHT_BUTTON) {
        cout << "Right Button Pressed" << endl;
    }
    glutPostRedisplay();
}







int main(int argc, char *argv[]) {
    srand(time(NULL));
    int width = 1020, height = 840;
    InitRandomizer();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutCreateWindow("23I-0033 BRICK BREAKER PROJECT");
    SetCanvasSize(1000, 1000);

    glutDisplayFunc(GameDisplay);
    glutSpecialFunc(NonPrintableKeys);
    glutKeyboardFunc(PrintableKeys);
    glutTimerFunc(1000.0, Timer, 0);
    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved);
    glutMotionFunc(MousePressedAndMoved);

    glutMainLoop();
    return 1;
}
