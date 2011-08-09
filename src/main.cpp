/*
 * main.cpp
 *
 * Description:
 * Main program file including GLUT Functions for the OpenGL game
 * 'Parachute Drop'.
 *
 * Last Modified:   11/07/19
 * Changelog:       11/07/19 - Basic GLUT functions
 *                  11/08/02 - Tested basic classes
 *                  11/08/05 - Started level design
 *                  11/08/06 - Integrated ObstacleList
 *                           - Timer functions create/delete obstacles
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <GL/glut.h>

#include "global.h"       // Global variables and constants
#include "Camera.h"       // Camera movement
#include "Player.h"       // Player drawing and x/y movement
#include "ObstacleList.h" // Linked List of obstacles and z movement

#include "imageloader.h"  // BMP loader for textures

int width  = WIDTH;       // Current window width
int height = HEIGHT;      // Current window height

enum gameState { MENU, LEVEL, GAME_OVER };
gameState state = MENU;

int level = 0;

float bgSize = 0.0;

GLfloat position[] = {0,0,0,0};

// Fog
GLfloat fogColor[3] = { 0.0, 0.0, 0.0 };
float fogStart = 0.0;
float fogEnd   = 0.0;

// Game speed (milliseconds)
int speedMove   = 100;
int speedCreate = 1000;

// Mouse
int sensitivity = 10;

float xRot = 0.0;
float yRot = 0.0;
float xPrev = width/2;
float yPrev = height/2;

// Texture
GLuint worldTexId;
GLuint menuTexId;
GLuint gameoverTexId;

//keyboard
bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  

Camera cam;
Player player;
ObstacleList obstacles;


// Game values for Level 1
void setLevel1()
{
    state = LEVEL;
    level = 1;
    
    // Start fog at 3/4 of play field for Level 1
    //fogColor[R] = 0.9; fogColor[G] = 0.9; fogColor[B] = 1.0;
    fogStart = -(GAME_DEPTH) * FOGEND_L1*0.50;
    fogEnd   = -(GAME_DEPTH) * FOGEND_L1;

    speedCreate = 3000;
}

// Game values for Level 2
void setLevel2()
{
    state = LEVEL;
    level = 2;
    
    // Start fog at 3/4 of play field for Level 2
    //fogColor[R] = 0.6; fogColor[G] = 0.3; fogColor[B] = 0.2;
    fogStart = -(GAME_DEPTH) * FOGEND_L2*0.50;
    fogEnd   = -(GAME_DEPTH) * FOGEND_L2;

    speedCreate = 2000;
}

void setLevel3()
{
    state = LEVEL;
    level = 3;

    // Start fog at 3/4 of play field for Level 3
    //fogColor[R] = 0.3; fogColor[G] = 0.2; fogColor[B] = 0.3;
    fogStart = -(GAME_DEPTH) * FOGEND_L3*0.50;
    fogEnd   = -(GAME_DEPTH) * FOGEND_L3;

    speedCreate = 1000;
}

// Print a single char array
void printString(char* s)
{
    char* p;
    for (p = s; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
}

// Draw text for menu and game over screen
void drawMenu()
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, menuTexId );
    glBegin(GL_QUADS);
    glTexCoord2f( 0, 0 ); glVertex2f( 0, 0);
    glTexCoord2f( 1, 0 ); glVertex2f( width, 0);
    glTexCoord2f( 1, 1 ); glVertex2f( width, height);
    glTexCoord2f( 0, 1 ); glVertex2f( 0, height);
    /*
    glTexCoord2f( 0, 0 ); glVertex2f( std::max(0, (width - (185/2))), std::max(0, (height - (67/2))) );
    glTexCoord2f( 0, 1 ); glVertex2f( std::max(0, (width - (185/2))), std::min(height, (height+67)/2));
    glTexCoord2f( 1, 1 ); glVertex2f( std::min(width, (width+185)/2), std::min(height, (height+67)/2));
    glTexCoord2f( 1, 0 ); glVertex2f( std::min(width, (width+185)/2), std::max(0, (height - (67/2))) );
    */
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

// Draw text for menu and game over screen
void drawGameOver()
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, menuTexId );
    glBegin(GL_QUADS);
    glTexCoord2f( 0, 0 ); glVertex2f( 0, 0);
    glTexCoord2f( 1, 0 ); glVertex2f( width, 0);
    glTexCoord2f( 1, 1 ); glVertex2f( width, height);
    glTexCoord2f( 0, 1 ); glVertex2f( 0, height);
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
}



// Draw Background to cover field of view at GAME_DEPTH Print Statistics in Orthogonal view
void drawWorld()
{
    glPushMatrix();
    // Statistics
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(0,0);
    
    char buffer[20];
    sprintf(buffer, "Level: %i", player.getLives());
    printString(buffer);

    printString(buffer);
    sprintf(buffer, "    Score: %i", player.getPoints());
    glPopMatrix();

    // Background    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( cam.fov, width/height, cam.zNear, cam.zFar );

    glMatrixMode(GL_MODELVIEW);
    bgSize = ( GAME_DEPTH / cos(cam.fov/2) )*2;
    glColor3f(fogColor[R], fogColor[G], fogColor[B]);

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, worldTexId );
    glBegin(GL_QUADS);
    glTexCoord2f( 0, 0 ); glVertex3f( (GAME_WIDTH/2)-bgSize, (GAME_HEIGHT/2)-bgSize, GAME_DEPTH );
    glTexCoord2f( 0, 1 ); glVertex3f( (GAME_WIDTH/2)-bgSize, (GAME_HEIGHT/2)+bgSize, GAME_DEPTH );
    glTexCoord2f( 1, 1 ); glVertex3f( (GAME_WIDTH/2)+bgSize, (GAME_HEIGHT/2)+bgSize, GAME_DEPTH );
    glTexCoord2f( 1, 0 ); glVertex3f( (GAME_WIDTH/2)+bgSize, (GAME_HEIGHT/2)-bgSize, GAME_DEPTH );
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    // Light
    glEnable(GL_LIGHTING);
    GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientLight );

    glEnable(GL_LIGHT0);
    GLfloat lightColor0[] = { .5, 0.2, 0.2 };
    GLfloat lightPos0[] = { -0.5, 1, 0.25, 0.0 };
    glLightfv( GL_LIGHT0, GL_DIFFUSE, lightColor0 );
    glLightfv( GL_LIGHT0, GL_POSITION, lightPos0 );
    
    // Set Fog
    glEnable(GL_FOG);
    glFogfv( GL_FOG_COLOR, fogColor);
    glFogi( GL_FOG_MODE, GL_LINEAR);
    glFogi( GL_FOG_START, fogStart);
    glFogi( GL_FOG_END, fogEnd);

}

void keyOperations (void) 
	{  
	   if (keyStates['s']) 
	   { // If the 's' key has been pressed  
		   player.Move(0,-PLAYER_STEP); 
           cam.translate(0,-PLAYER_STEP,0);
		   if(player.getXLean()>=35)
			   player.setXLean(35);
		   else
			   player.setXLean(player.getXLean()+3);

	   }  
  	   if (keyStates['w']) 
	   { // If the 'w' key has been pressed  
		   player.Move(0,PLAYER_STEP); 
           cam.translate(0,PLAYER_STEP,0);
		   if(player.getXLean()<=-35)
			   player.setXLean(-35);
		   else
			   player.setXLean(player.getXLean()-3);
	   }  
	   if (keyStates['d']) 
	   { // If the 'd' key has been pressed  
		   player.Move(PLAYER_STEP,0); 
           cam.translate(PLAYER_STEP,0,0);
		    if(player.getZLean()>=55)
			   player.setZLean(55);
		   else
			   player.setZLean(player.getZLean()+3);
	   }  
	   if (keyStates['a']) 
	   { // If the 'a' key has been pressed  
		   player.Move(-PLAYER_STEP,0); 
           cam.translate(-PLAYER_STEP,0,0);
		   if(player.getZLean()<=-55)
			   player.setZLean(-55);
		   else
			   player.setZLean(player.getZLean()-3);
	   }  
	   if(keyStates[27])
	   {
		    exit(0);
	   }
	player.Lean();
   } 
 
// GLUT Display Function
void display(void)
{
	keyOperations(); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    switch (state)
    {
        case MENU:
            drawMenu();            

        break;
        case LEVEL:
            // Set camera view
			cam.view();
            
            // Rotate view based on mouse input
            glTranslatef(player.getXPos(), player.getYPos(), 5.0);
            glRotatef(xRot*sensitivity, 1.0, 0.0, 0.0);
            glRotatef(yRot*sensitivity, 0.0, 1.0, 0.0);
            glTranslatef(-player.getXPos(), -player.getYPos(), -5.0);

            // Draw background and effects
            drawWorld();

            // Draw player
			player.draw();
            
            // Draw obstacles
            obstacles.drawAll(level);
            
        break;
        case GAME_OVER:
            drawGameOver();

        break;
    }
    
    glPopMatrix();
    glutSwapBuffers();
}

// GLUT Reshape Function
void reshape(int w, int h)
{
    // Set global variables & adjust view
    xPrev = xPrev / width  * w;
    yPrev = yPrev / height * h;
    width = w;
    height = h;
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( cam.fov, w/h, cam.zNear, cam.zFar );
    glMatrixMode(GL_MODELVIEW);
    cam.view();
}

// GLUT Special Keyboard Function
void specialKey(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_F1:
            setLevel1();
        break;
        case GLUT_KEY_F2:
            setLevel2();
        break;
        case GLUT_KEY_F3:
            setLevel3();
        break;
    }	

    glutPostRedisplay();
}

void keyPressed (unsigned char key, int x, int y) 
	{  
		 keyStates[key] = true; // Set the state of the current key to pressed  
	}  

void keyUp (unsigned char key, int x, int y) 
	{
		keyStates[key] = false; // Set the state of the current key to not pressed  
	}  


// GLUT mouse Function
void mouse(int x, int y)
{
    float xDiff = (x - xPrev)/height;
    float yDiff = (y - yPrev)/width;
    xPrev = x;
    yPrev = y;
    xRot += (float) yDiff;
    yRot += (float) xDiff;
}

// GLUT mouse click Function
void click(int button, int stat, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_UP)
    {
        if (state == MENU) setLevel1();
        else if (state == GAME_OVER) state = MENU;
    }
    glutPostRedisplay();
}

// GLUT Timer Function for obstacles
void moveTimer(int value)
{
    if (state == LEVEL)
    {
        // Move Obstacles
        obstacles.moveAll(level);
        
        // Remove Obstacles that exit world
        if ( !obstacles.isEmpty() && (obstacles.getFirst())->getZPos() >= 25 )
        {
            obstacles.remove();
            // Detect collisions
            float xDiff = player.getXPos() - (obstacles.getFirst())->getXPos();
            float yDiff = player.getYPos() - (obstacles.getFirst())->getYPos();
            
            
            // TODO: COLLISION DETECTION - IMPLEMENT PLAYER/OBS SIZE
            if (xDiff < 5 && yDiff < 5) {
                //if (player.getHealth() > 1)
                
                player.addPoints(P_HIT);
            } else {
                // Avoid 
                player.addPoints(P_AVOID);
            }
        }

        glutPostRedisplay();
    }
    glutTimerFunc(speedMove, moveTimer, 0);
}

void createTimer(int value)
{
    if (state == LEVEL)
    {
        // Create an obstacle at a random location
        obstacles.insert( rand() % GAME_WIDTH, rand() % GAME_HEIGHT, GAME_DEPTH );
    }
    glutTimerFunc(speedCreate, createTimer, 0);
}

// OpenGL Initialisation
void init(void)
{
	for(int key =0; key!=256; key++){
		keyStates[key] = false; // Set the state of the current key to not pressed  
	}

    srand( time(NULL) );
    glClearColor(fogColor[R], fogColor[G], fogColor[B], 0.0);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_BLEND);
    glBlendFunc(  GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // Load world texture
    Image* image = loadBMP("tex/star.bmp");
    glGenTextures( 1, &worldTexId );
    glBindTexture( GL_TEXTURE_2D, worldTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );

    // Load menu texture
    image = loadBMP("tex/ducksinspace.bmp");
    glGenTextures( 1, &menuTexId );
    glBindTexture( GL_TEXTURE_2D, menuTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
    
    // Load game over texture
    image = loadBMP("tex/gameover.bmp");
    glGenTextures( 1, &gameoverTexId );
    glBindTexture( GL_TEXTURE_2D, gameoverTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );

    delete image;
}

int main(int argc, char** argv)
{
    // GLUT initialisation and callbacks
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Helicopter");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

	glutKeyboardUpFunc(keyUp);
	glutKeyboardFunc(keyPressed);

    glutSpecialFunc(specialKey);
    glutPassiveMotionFunc(mouse);
    glutMouseFunc(click);

    glutTimerFunc(speedMove, moveTimer, 0);
    glutTimerFunc(speedCreate, createTimer, 0);

    glutMainLoop();

    exit(0);
}
