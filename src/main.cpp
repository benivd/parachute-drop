/*
 * main.cpp
 *
 * Description:
 * Main program file including GLUT Functions for the OpenGL game
 * 'Ducks in space'.
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

#if defined _WIN32
# include <Windows.h>
#endif

#include <GL/glut.h>

#include "global.h"       // Global variables and constants
#include "Camera.h"       // Camera movement
#include "Player.h"       // Player drawing and x/y movement
#include "ObstacleList.h" // Linked List of obstacles and z movement

#include "imageloader.h"  // BMP loader for textures

bool testMode = false;
bool beginSnd = false;    // used for Start Sound

int width  = WIDTH;       // Current window width
int height = HEIGHT;      // Current window height

// Game info
enum gameState { MENU, LEVEL, GAME_OVER, INSTRUCTIONS, CREDITS };
gameState state = MENU;

int level = 0;
int levelCounter = LEVEL_TIME;
int titleCounter = TITLE_TIME;

// Stars
int starPos[NUM_STARS][2];
int tunnelSize = ( -GAME_DEPTH )*2;

// Fog
float fogStart = 0.0;
float fogEnd   = 0.0;

// Panels
bool mesh = false;
int margin = MARGIN;

// Obstacles
GLfloat position[] = {0,0,0,0};
        
// Game speed (milliseconds)
int speedMove   = 100;
int speedCreate = 1000;

// Rotation
float xRot = 0.0;
float yRot = 0.0;
float xPrev = width/2;
float yPrev = height/2;
float planetAngle = 0;

// Texture
GLuint worldTexId;
GLuint menuTexId;
GLuint gameoverTexId;
GLuint sunTexId;
GLuint playTexId;
GLuint instructionTexId;
GLuint creditsTexId;
GLuint mainMenuTexId;
GLuint instructionsTexId;
GLuint creditsSTexId;

// Keyboard
bool* keyStates = new bool[256];

// Create Class Instances
Camera cam;
Player player;
ObstacleList obstacles;


// Game values for Level 1
void setLevel1()
{
    state = LEVEL;
    level = 1;
    levelCounter = LEVEL_TIME;
    titleCounter = TITLE_TIME;
    
    // Start fog at 1/2 of play field for Level 1
    fogStart = -(GAME_DEPTH) * FOGEND_L1*0.50;
    fogEnd   = -(GAME_DEPTH) * FOGEND_L1;

    speedCreate = SPAWN_L1;

    // Clear level
    obstacles.removeAll();

	// Reset Initial Sound
	beginSnd = true;
}

// Game values for Level 2
void setLevel2()
{
    state = LEVEL;
    level = 2;
    levelCounter = LEVEL_TIME;
    titleCounter = TITLE_TIME;
    
    // Start fog at 1/2 of play field for Level 2
    fogStart = -(GAME_DEPTH) * FOGEND_L2*0.50;
    fogEnd   = -(GAME_DEPTH) * FOGEND_L2;

    speedCreate = SPAWN_L2;
    
    // Clear level
    obstacles.removeAll();

	// Reset Initial Sound
	beginSnd = true;
}

void setLevel3()
{	
    state = LEVEL;
    level = 3;
    levelCounter = LEVEL_TIME;
    titleCounter = TITLE_TIME;

    // Start fog at 1/2 of play field for Level 3
    fogStart = -(GAME_DEPTH) * FOGEND_L3*0.50;
    fogEnd   = -(GAME_DEPTH) * FOGEND_L3;

    speedCreate = SPAWN_L3;
    
    // Clear level
    obstacles.removeAll();

	// Reset Initial Sound
	beginSnd = true;
}

void setLevel3Plus()
{
	state= LEVEL;
	level = level+1;
	levelCounter= LEVEL_TIME;
	titleCounter = TITLE_TIME;

	//fog constant
	fogStart = -(GAME_DEPTH) * FOGEND_L3*0.50;
    fogEnd   = -(GAME_DEPTH) * FOGEND_L3;

	speedCreate = SPAWN_L3/(level);

	// Clear level
    obstacles.removeAll();

	// Reset Initial Sound
	beginSnd = true;
}

void resetLevel3Plus()
{
	state= LEVEL;
	level = level;
	levelCounter= LEVEL_TIME;
	titleCounter = TITLE_TIME;

	//fog constant
	fogStart = -(GAME_DEPTH) * FOGEND_L3*0.50;
    fogEnd   = -(GAME_DEPTH) * FOGEND_L3;

	speedCreate = SPAWN_L3/(level);

	// Reset Initial Sound
	beginSnd = true;
}

// Print a single char array
void printString(char* s)
{
    glPushMatrix();
    char* p;
    for (p = s; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
    glPopMatrix();
}

// Draw text for title screen
void drawMenu()
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);	

    glEnable(GL_TEXTURE_2D);

	glBindTexture( GL_TEXTURE_2D, playTexId );
	glBegin(GL_QUADS);
		glTexCoord2f( 0, 0 ); glVertex2f( width*.1, height*.05);
		glTexCoord2f( 1, 0 ); glVertex2f( width*.35, height*.05);
		glTexCoord2f( 1, 1 ); glVertex2f( width*.35, height*.25);
		glTexCoord2f( 0, 1 ); glVertex2f( width*.1, height*.25);
    glEnd();

	glBindTexture( GL_TEXTURE_2D, instructionTexId );
	glBegin(GL_QUADS);
		glTexCoord2f( 0, 0 ); glVertex2f( width*.375, height*.05);
		glTexCoord2f( 1, 0 ); glVertex2f( width*.625, height*.05);
		glTexCoord2f( 1, 1 ); glVertex2f( width*.625, height*.25);
		glTexCoord2f( 0, 1 ); glVertex2f( width*.375, height*.25);
    glEnd();

	glBindTexture( GL_TEXTURE_2D, creditsTexId );
	glBegin(GL_QUADS);
		glTexCoord2f( 0, 0 ); glVertex2f( width*.65, height*.05);
		glTexCoord2f( 1, 0 ); glVertex2f( width*.9, height*.05);
		glTexCoord2f( 1, 1 ); glVertex2f( width*.9, height*.25);
		glTexCoord2f( 0, 1 ); glVertex2f( width*.65, height*.25);
    glEnd();
	
    glBindTexture( GL_TEXTURE_2D, menuTexId );
    glBegin(GL_QUADS);
		glTexCoord2f( 0, 0 ); glVertex2f( 0, 0);
		glTexCoord2f( 1, 0 ); glVertex2f( width, 0);
		glTexCoord2f( 1, 1 ); glVertex2f( width, height);
		glTexCoord2f( 0, 1 ); glVertex2f( 0, height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Draw text for game over screen
void drawGameOver()
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Points
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(width/2 - 40, height/2 - 18/2);
    char buffer[20];
    sprintf(buffer, "Score: %i", player.getPoints());
    printString(buffer);

    // Game Over Screen
    glEnable(GL_TEXTURE_2D);

	    glBindTexture( GL_TEXTURE_2D, mainMenuTexId );
		glBegin(GL_QUADS);
		glTexCoord3f( 0, 0, -5 ); glVertex2f( width*.375, height*.15);
		glTexCoord3f( 1, 0, -5 ); glVertex2f( width*.625, height*.15);
		glTexCoord3f( 1, 1, -5 ); glVertex2f( width*.625, height*.35);
		glTexCoord3f( 0, 1, -5 ); glVertex2f( width*.375, height*.35);
		glEnd();

		glBindTexture( GL_TEXTURE_2D, gameoverTexId );
		glBegin(GL_QUADS);
		glTexCoord3f( 0, 0, -5 ); glVertex2f( 0, 0);
		glTexCoord3f( 1, 0, -5 ); glVertex2f( width, 0);
		glTexCoord3f( 1, 1, -5 ); glVertex2f( width, height);
		glTexCoord3f( 0, 1, -5 ); glVertex2f( 0, height);
		glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Draw text for instruction screen
void drawInstructions()
{
	glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);	

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, instructionsTexId );
    glBegin(GL_QUADS);
		glTexCoord2f( 0, 0 ); glVertex2f( 0, 0);
		glTexCoord2f( 1, 0 ); glVertex2f( width, 0);
		glTexCoord2f( 1, 1 ); glVertex2f( width, height);
		glTexCoord2f( 0, 1 ); glVertex2f( 0, height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Draw text for credits screen
void drawCredits()
{
	glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);	

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, creditsSTexId );
    glBegin(GL_QUADS);
		glTexCoord2f( 0, 0 ); glVertex2f( 0, 0);
		glTexCoord2f( 1, 0 ); glVertex2f( width, 0);
		glTexCoord2f( 1, 1 ); glVertex2f( width, height);
		glTexCoord2f( 0, 1 ); glVertex2f( 0, height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawStars()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);

    // Stars
    for (int i = 0; i < NUM_STARS; i++)
    {
        glPushMatrix();
        glTranslatef( starPos[i][0], starPos[i][1], GAME_DEPTH );
        glBegin(GL_QUADS);
        glVertex2f( -0.5, -0.5);
        glVertex2f( +0.5, -0.5);
        glVertex2f( +0.5, +0.5);
        glVertex2f( -0.5, +0.5);
        glEnd();
        glPopMatrix();
    }
	    
    // Sun (at GAME_DEPTH, above the glass panels)
    glPushMatrix();
	glTranslatef( -GAME_WIDTH/3, GAME_HEIGHT + margin + SUN_SIZE, GAME_DEPTH);
    GLUquadricObj *sphere=NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,sunTexId);
	glRotatef(planetAngle,0,1,0);
	glRotatef(-90,1,0,0);
	glColor3f(.5,.5,0.5);
	gluSphere(sphere, SUN_SIZE, 100, 100);
	glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
}

// Enable ambient and directed light
void drawLight()
{
    glPushMatrix();
    glEnable(GL_LIGHTING);
    GLfloat ambientLight[] = { 0.1, 0.1, 0.1, 1 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientLight );

    glEnable(GL_LIGHT0);
    GLfloat lightColor0[] = { 0.6, 0.5, 0.1 };
    //GLfloat lightPos0[] = { -((GAME_WIDTH/2) - (-GAME_WIDTH/3)), -((GAME_HEIGHT/2) - (GAME_HEIGHT + PLAYER_SIZE + SUN_SIZE)), GAME_DEPTH/3, 0.0 };
    GLfloat lightPos0[] = { 0,-.25,1, 0.0 };
	glLightfv( GL_LIGHT0, GL_DIFFUSE, lightColor0 );
    glLightfv( GL_LIGHT0, GL_POSITION, lightPos0 );
}

void drawFog()
{
    GLfloat fogColor[3] = { 0.0, 0.0, 0.0 };
    glEnable(GL_FOG);
    glFogfv( GL_FOG_COLOR, fogColor);
    glFogi( GL_FOG_MODE, GL_LINEAR);
    glFogi( GL_FOG_START, fogStart);
    glFogi( GL_FOG_END, fogEnd);
    glPopMatrix();
}

void drawPanels()
{
    /*
    GLfloat ambient[] = {0.22, 0.33, 0.44, 0.5};
    GLfloat diffuse[] = {0.11, 0.55, 0.77, 0.5};
    GLfloat specular[] = {0.90, 0.95, 1.00, 1.0};
    GLfloat shininess = 30;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    */

    if (mesh)
    {
        margin = PLAYER_SIZE + 5;
    }
    else // Resizable glass panels
    {
        // Top Panel:
        glPushMatrix();
        glTranslatef( GAME_WIDTH/2, GAME_HEIGHT + margin, -tunnelSize/2 + 50 );
        glScalef( GAME_WIDTH + margin*2, 1.0, tunnelSize );
        glColor4f( 0.9, 0.95, 1.0, 0.2 );
        glutSolidCube(1);
        glPopMatrix();

        // Bottom Panel:
        glPushMatrix();
        glTranslatef( GAME_WIDTH/2, -margin, -tunnelSize/2 + 50 );
        glScalef( GAME_WIDTH + margin*2, 1.0, tunnelSize );
        glColor4f( 0.9, 0.95, 1.0, 0.2 );
        glutSolidCube(1);
        glPopMatrix();

        // Left Panel:
        glPushMatrix();
        glTranslatef( -margin, GAME_HEIGHT/2, -tunnelSize/2 + 50 );
        glScalef(1.0, GAME_HEIGHT + margin*2, tunnelSize);
        glColor4f(0.9, 0.95, 1.0, 0.2);
        glutSolidCube(1);
        glPopMatrix();

        // Right Panel:
        glPushMatrix();
        glTranslatef(GAME_WIDTH + margin, GAME_HEIGHT/2, -tunnelSize/2 + 50);
        glScalef(1.0, GAME_HEIGHT + margin*2, tunnelSize);
        glColor4f(0.9, 0.95, 1.0, 0.2);
        glutSolidCube(1);
        glPopMatrix();
    }
}

void drawStats()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);

    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);

    // Level
    char buffer[20];
    glRasterPos2i( 1, height - 18);
    sprintf(buffer, "Level %i", level);
    printString(buffer);

    if (titleCounter != 0)
    {
        glColor3f(1,1,1);
        glRasterPos2i(width/2 - 40, height/2 - 18);
        printString(buffer);
        titleCounter -= 1;
    }
	if(titleCounter == 1)
	{
		#if defined _WIN32
		PlaySound(L"snd/bgm.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		#endif
	}
    
    // Lives, Health & Score
    glRasterPos2i( 1, 1);
    sprintf(buffer, "Lives: %i", player.getLives());
    printString(buffer);
    sprintf(buffer, "    Health: %i", player.getHealth());
    printString(buffer);
    sprintf(buffer, "    Score: %i", player.getPoints());
    printString(buffer);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( cam.fov, width/height, cam.zNear, cam.zFar );
    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();

    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
}
    
void keyOperations (void) 
{  
    // s: move down
    if (keyStates['s']) 
	{
        if (player.getYPos() > -margin + PLAYER_SIZE)
        {
            player.Move(0,-PLAYER_STEP);   
            cam.translate(0,-PLAYER_STEP,0);
            if(player.getXLean()>=35)
                player.setXLean(35);
            else
                player.setXLean(player.getXLean()+3);
        }

    } 
    // w: move up
  	if (keyStates['w']) 
	{
        if (player.getYPos() < GAME_HEIGHT + margin - PLAYER_SIZE)
        {
            player.Move(0,PLAYER_STEP); 
            cam.translate(0,PLAYER_STEP,0);
            if(player.getXLean()<=-35)
                player.setXLean(-35);
            else
                player.setXLean(player.getXLean()-3);
        }  
    }
    // d: move right
	if (keyStates['d']) 
	{
        if (player.getXPos() < GAME_WIDTH + margin - PLAYER_SIZE)
        {
            player.Move(PLAYER_STEP,0); 
            cam.translate(PLAYER_STEP,0,0);
            if(player.getZLean()>=55)
                player.setZLean(55);
            else
                player.setZLean(player.getZLean()+3);
        }
	}
    // a: move left
	if (keyStates['a']) 
	{ 
        if (player.getXPos() > -margin + PLAYER_SIZE)
        {
            player.Move(-PLAYER_STEP,0); 
            cam.translate(-PLAYER_STEP,0,0);
            if(player.getZLean()<=-55)
                player.setZLean(-55);
            else
                player.setZLean(player.getZLean()-3);
        }
	}  
    player.Lean();

    // r: Rotate duck  
    if (keyStates['r']) 
	{
	   player.setYspin(player.getYSpin()+5);
	}

    // Enable 'bounding' spheres used for collision
	if (keyStates['1']) 
	{
        testMode = true;
	}

    // Enable 'bounding' spheres used for collision
	if (keyStates['2']) 
	{
        testMode = false;
	} 

    // Extend the play area
	if (keyStates['3']) 
	{
        static bool increasing = true;
        if (increasing && margin < 100)                     // max size
            margin += 5;
        else if (!increasing && margin > (PLAYER_SIZE + 5)) // min size
            margin -= 5;
        else if (increasing)
            increasing = false;
        else
            increasing = true;
	}

    // Select glass or mesh panel
    if (keyStates['4'])
    {
        mesh = !mesh;
    }

    if (keyStates['+'])
    {
        if (cam.cz > -6) cam.translate(0.0, 0.0,-1.0);
    }

    if (keyStates['-'])
    {
        if (cam.cz < 20) cam.translate(0.0, 0.0, 1.0);
    }

	if(keyStates[27])
	{
	    exit(0);
	}

} 
 
// GLUT Display Function
void display(void)
{
	keyOperations(); 
	if(player.getYSpin()>325)
	{
		#if defined _WIN32
		PlaySound(L"snd/bgm.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		#endif
	}

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glPushMatrix();

    switch (state)
    {
        case MENU:
            player.setLives(3);
            player.setHealth(3);
            player.setPoints(0);

            drawMenu();            

        break;

		case INSTRUCTIONS:			

			drawInstructions();

		break;

		case CREDITS:

			drawCredits();

		break;

        case LEVEL:
            // Set camera view
			cam.view();
            
            // Rotate view based on mouse input around player
            glTranslatef(player.getXPos(), player.getYPos(), cam.dz+5.0);
            glRotatef(xRot*SENSITIVITY, 1.0, 0.0, 0.0);
            glRotatef(yRot*SENSITIVITY, 0.0, 1.0, 0.0);
            glTranslatef(-player.getXPos(), -player.getYPos(), -(cam.dz+5.0));

            // Enable ambient and directed lights
            drawLight();

            // Enable fog
            drawFog();

            // Draw sun and stars
            drawStars();

/*            // Draw obstacles before panels
            glDisable(GL_DEPTH_TEST);
            obstacles.drawAll(0, testMode);
            glEnable(GL_DEPTH_TEST);
*/
            // Draw glass boundaries
            drawPanels();
            
            // Draw obstacles after panels
            obstacles.drawAll(level, testMode);
            
            // Draw player
            player.draw(testMode);

            // Draw statisitics
            drawStats();

			glEnd();
			
			// Sound to indicate beginning of level
			if (beginSnd) {
			#if defined _WIN32
			PlaySound(L"snd/squeak.wav", NULL, SND_FILENAME | SND_ASYNC);
			#endif
			beginSnd = false;
			}
            
        break;
        case GAME_OVER:
			// Game over sound
			#if defined _WIN32
			PlaySound(L"snd/game_over.wav", NULL, SND_FILENAME | SND_ASYNC);
			#endif
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
        case GLUT_KEY_F4:
            state = GAME_OVER;
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

	if (state == MENU)
	{
		if (x>width*.1&&x<width*.35&&y<height*.95&&y>height*.75&&button == GLUT_LEFT_BUTTON && stat == GLUT_UP)
		{       
			// Menu Click sound
			#if defined _WIN32
			PlaySound(L"snd/blip1.wav", NULL, SND_FILENAME | SND_ASYNC);
			#endif			
			setLevel1();
		}

		if (x>width*.375&&x<width*.625&&y<height*.95&&y>height*.75&&button == GLUT_LEFT_BUTTON && stat == GLUT_UP)
		{   
			// Menu Click sound
			#if defined _WIN32
			PlaySound(L"snd/blip1.wav", NULL, SND_FILENAME | SND_ASYNC);
			#endif			
			state=INSTRUCTIONS;
		}    

		if (x>width*.65&&x<width*.9&&y<height*.95&&y>height*.75&&button == GLUT_LEFT_BUTTON && stat == GLUT_UP)
		{   
			// Menu Click sound
			#if defined _WIN32
			PlaySound(L"snd/blip1.wav", NULL, SND_FILENAME | SND_ASYNC);
			#endif			
			state=CREDITS;
		}
	}
	else if (state == GAME_OVER) 
	{
		if(x>width*.375&&x<width*.625&&y<height*.85&&y>height*.65&&button == GLUT_LEFT_BUTTON && stat == GLUT_UP)
		{   
			// Menu Click sound
			#if defined _WIN32
			PlaySound(L"snd/blip1.wav", NULL, SND_FILENAME | SND_ASYNC);
			#endif			
			state=MENU;
		}
	}

	else if (state == INSTRUCTIONS)
	{
		if(button == GLUT_LEFT_BUTTON && stat == GLUT_UP)
			state=MENU;
	}

	else if (state == CREDITS)
	{
		if(button == GLUT_LEFT_BUTTON && stat == GLUT_UP)
			state=MENU;
	}

    // Wheel down - Zoom in
    if (button == 4)
    {
        if (cam.cz > -6) cam.translate(0.0, 0.0,-1.0);

    } // Wheel up - Zoom out
    else if (button == 3)
    {
        if (cam.cz < 20) cam.translate(0.0, 0.0, 1.0);
    }
    glutPostRedisplay();
}

// GLUT Timer Function for obstacles
void moveTimer(int value)
{
	planetAngle+=.5;
    if (state == LEVEL && !obstacles.isEmpty())
    {
        // Move Obstacles
        obstacles.moveAll(level);

        // Test for collision
		if(obstacles.CollidesAll(&player))
        {
            player.addPoints(P_HIT);

            // Lose health
            if (player.getHealth() > 1)
            {
                // health -1
                player.setHealth(player.getHealth()-1);
            }
            // Lose life
            else
            {
                // reset health
                player.setHealth(3);

                // Lose life
                if (player.getLives() > 0)
                {
                    // Lives -1; reset current level
                    player.setLives(player.getLives()-1);
                    switch (level)
                    {
                        case 1:
                            setLevel1();
                        break;
                        case 2:
                            setLevel2();
                        break;
                        case 3:
                            setLevel3();
						default:
							resetLevel3Plus();
                        break;
                    }
                }
                // Game over
                else 
				{
					state = GAME_OVER;
                }
            }
        }
        player.addPoints(P_AVOID);

		// First obstacle out of sight ?
		if (state == LEVEL && !obstacles.isEmpty() && obstacles.getFirst()->getZPos() > 50)
		{
			obstacles.remove();
		}

        glutPostRedisplay();
    }

    // Update level counter, and change level
    if (state == LEVEL)
    {
        levelCounter -= speedMove;
        if (levelCounter <= 0)
        {
            switch (level)
            {
                case 1:
                    setLevel2();
                break;
                case 2:
                    setLevel3();
                break;
				default:
					setLevel3Plus();
                break;
            }
        }
    }

    glutTimerFunc(speedMove, moveTimer, 0);
}

void createTimer(int value)
{
    if (state == LEVEL)
    {
        // Create an obstacle at a random location
        obstacles.insert( rand() % GAME_WIDTH, rand() % GAME_HEIGHT, GAME_DEPTH, level );
    }
    glutTimerFunc(speedCreate, createTimer, 0);
}

// OpenGL Initialisation
void init(void)
{
	// Initialise global variables
	for(int key =0; key!=256; key++){
		keyStates[key] = false; // Set the state of the current key to not pressed  
	}
    
    Player::createParticles();

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_FOG);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	//Load Mask texture
	Obstacle::LoadVMask();

    // Load menu texture
    // http://www.budproduct.com/collections/80s-pop-culture/ducks-in-space-mini-duck-set-2/ducks-in-space-mini-duck-set/
    Image* image = loadBMP("tex/ducksinspace.bmp");
    glGenTextures( 1, &menuTexId );
    glBindTexture( GL_TEXTURE_2D, menuTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
    
    // Load game over texture
    //
    image = loadBMP("tex/gameover.bmp");
    glGenTextures( 1, &gameoverTexId );
    glBindTexture( GL_TEXTURE_2D, gameoverTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
   
	// Load play game texture
    image = loadBMP("tex/Button1.bmp");
    glGenTextures( 1, &playTexId );
    glBindTexture( GL_TEXTURE_2D, playTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );

	// Load instruction texture
    image = loadBMP("tex/Button2.bmp");
    glGenTextures( 1, &instructionTexId );
    glBindTexture( GL_TEXTURE_2D, instructionTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );

	// Load credits texture
    image = loadBMP("tex/Button3.bmp");
    glGenTextures( 1, &creditsTexId );
    glBindTexture( GL_TEXTURE_2D, creditsTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );

	// Load MainMenu texture
    image = loadBMP("tex/Button4.bmp");
    glGenTextures( 1, &mainMenuTexId );
    glBindTexture( GL_TEXTURE_2D, mainMenuTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );

	// Load instructions page texture
    image = loadBMP("tex/Instructions.bmp");
    glGenTextures( 1, &instructionsTexId );
    glBindTexture( GL_TEXTURE_2D, instructionsTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );

	// Load credits page texture
    image = loadBMP("tex/creditsS.bmp");
    glGenTextures( 1, &creditsSTexId );
    glBindTexture( GL_TEXTURE_2D, creditsSTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );

	
	// Load sun texture
	//http://www.turbosquid.com/FullPreview/Index.cfm/ID/557319
    image = loadBMP("tex/Sun.bmp");
    glGenTextures( 1, &sunTexId );
    glBindTexture( GL_TEXTURE_2D, sunTexId );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, image->width, image->height,
                       GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
    delete image;
}

int main(int argc, char** argv)
{
    srand( time(NULL) );

    for (int i = 0; i < NUM_STARS; i++)
    {
        starPos[i][0] = rand() % (STAR_SPREAD*GAME_WIDTH)  -
                                 (STAR_SPREAD*GAME_WIDTH/2 + GAME_WIDTH/2);
        starPos[i][1] = rand() % (STAR_SPREAD*GAME_HEIGHT) -
                                 (STAR_SPREAD*GAME_HEIGHT/2+ GAME_HEIGHT/2);
    }
    
    // GLUT initialisation and callbacks
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Space Duck!");
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
