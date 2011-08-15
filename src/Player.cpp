#include "Player.h"

#include <cstdlib>
#include <iostream>

#if defined _WIN32
# include <Windows.h>
#endif

#include <GL/glut.h>

#include "objLoader/glm.c"
#include "imageloader.h"
#include "global.h"


//model
GLMmodel* pmodel;

// Particles
int count = PARTICLE_COUNT;
float partSize = 0.1;
static GLuint smokeMaskId;
static GLuint smokeTexId;

typedef struct
{
    float xPos;
    float yPos;
    float zPos;
    float xMov;
    float zMov;
    float dir;
    float accel;
    float decel;
} Particles;

Particles particle[PARTICLE_COUNT];


Player::Player()
{
    setLives(3);
    setLives(3);
    setPoints(0);
    setXPos( GAME_WIDTH  /2 );
    setYPos( GAME_HEIGHT /2 );
	setZPos( -5);
	setSpinout(false);
	ySpin=0;
	setRad(.6);
	hittable=true;
}

// Player::~Player(); // Using default

void drawmodel(void)
{
    if (!pmodel) {
		//http://www.oyonale.com/modeles.php?lang=en&page=53 for the .obj, made the .mtl myself
        pmodel = glmReadOBJ("obj/ducky.obj");
        if (!pmodel) exit(0);
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90.0);
	 }
    
    glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

//function to load the RAW file
GLuint LoadTextureRAW( const char * filename, int width, int height)
{
    GLuint texture;
    unsigned char * data;
    FILE * file;
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );
    glGenTextures(1, &texture );
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
    return texture;
}

void Player::createParticles (void)
{
    smokeMaskId = LoadTextureRAW("tex/particle_mask.raw",256,256);
    smokeTexId = LoadTextureRAW("tex/particle.raw",256,256);

    for (int i = 1; i < count; i++)
    {
        particle[i].xPos = 0;
        particle[i].yPos = -5;
        particle[i].zPos = -5;
        particle[i].xMov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) -
                           (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
        particle[i].zMov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005) -
                           (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1) * 0.005);
        particle[i].dir  = rand() % 90;
        particle[i].accel= ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.02;
        particle[i].decel= 0.0025;
    }
}

void updateParticles()
{
    for (int i = 1; i < count; i++)
    {
        glColor3f (1, 1, 1);
        particle[i].yPos = particle[i].yPos + particle[i].accel - particle[i].decel;
        particle[i].decel = particle[i].decel + 0.0025;
        particle[i].xPos = particle[i].xPos + particle[i].xMov;
        particle[i].zPos = particle[i].zPos + particle[i].zMov;
        particle[i].dir = particle[i].dir + ((((((int)(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);
        if (particle[i].yPos < -5)
        {
            particle[i].xPos = 0;
            particle[i].yPos = -5;
            particle[i].zPos = -5;
            particle[i].dir = 0;
            particle[i].accel = ((((((8 - 5 + 2) * rand()%11) + 5) - 1 + 1) * rand()%11) + 1) * 0.02;
            particle[i].decel = 0.0025;
        }
    }
}


void drawParticles()
{
    for (int i = 0; i < count; i++)
    {
        glPushMatrix();
        glColor4f(1,1,1,0.3);
        glTranslatef( particle[i].xPos, particle[i].yPos, particle[i].zPos );
        glRotatef( particle[i].dir - 90, 0, 0, 1 );
        
        glScalef(partSize, partSize, 1);
        
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        // Mask
        glBlendFunc (GL_DST_COLOR, GL_ZERO);
        glBindTexture (GL_TEXTURE_2D, smokeMaskId);
        glBegin (GL_QUADS);
        glTexCoord2d (0, 0);
        glVertex3f (-1, -1, 0);
        glTexCoord2d (1, 0);
        glVertex3f (1, -1, 0);
        glTexCoord2d (1, 1);
        glVertex3f (1, 1, 0);
        glTexCoord2d (0, 1);
        glVertex3f (-1, 1, 0);
        glEnd();
         
        // Texture
        glBlendFunc (GL_ONE, GL_ONE);
        glBindTexture (GL_TEXTURE_2D, smokeTexId);
        glBegin(GL_QUADS);
        glTexCoord2d (0, 0);
        glVertex3f(-1, -1, 0);
        glTexCoord2d(1, 0);
        glVertex3f (1, -1, 0);
        glTexCoord2d (1, 1);
        glVertex3f (1, 1, 0);
        glTexCoord2d (0, 1);
        glVertex3f (-1, 1, 0);
        glEnd();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable (GL_DEPTH_TEST);
        glPopMatrix();
    }
}

void drawFire(int amount)
{
    int r = (int) (10);

    // amount = 3 - health (3 to 0)
    for (int i = 0; i < amount; i++)
    {
        float x = rand() % 5 - r/2.0;
        float y = rand() % 5 - r/2.0;

        glPushMatrix();
        glTranslatef(x, y, 0.0);
        updateParticles();
        drawParticles();
        glPopMatrix();
    }
}

void Player::explode()
{
#if defined _WIN32
	PlaySound(L"snd/cardboard_box_impact_hard1.wav", NULL, SND_FILENAME | SND_ASYNC);
#endif
	if(health!=1) {
		setSpinout(true);
	}
	else
	{
		flash=true;
		flashcount=10;
		hittable=false;
	}
}

void Player::draw(bool testMode)
{
    glPushMatrix();
	glTranslated(xPos, yPos,zPos);

    glPushMatrix();
	glRotatef(180,0,1,0);
	glRotatef(xLean,1,0,0);
	glRotatef(zLean,0,0,1);
	if(spinout)
	{
		setYspin(getYSpin()+25);
		if(getYSpin()>=360)
		{
			ySpin=0;
			spinout=false;
		}
	}
	glRotatef(ySpin,0,1,0);
	if(flash)
	{
		flashcount=flashcount-1;
		if(flashcount==0)
		{
			flash=false;
			hittable=true;
		}
	}
	if(flashcount%2==0)
		drawmodel();
	if(testMode)
		glutWireSphere(.6,10,10);

    glPopMatrix();
    drawFire(3-health);

    glPopMatrix();
}

void Player::Move(float stepX, float stepY) {
	xPos += stepX;
	yPos += stepY;	
}

void Player::Lean() {
	xLean=xLean*.9;
	zLean=zLean*.9;
}

