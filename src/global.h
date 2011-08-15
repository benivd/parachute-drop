/*
 * global.h
 *
 * Description:
 * Global variables and constants for Parachute Drop game
 *
 * Last Modified:   11/07/22
 * Changelog:       11/07/22 - window height & width
 *                  11/08/02 - Game world
 *                  11/08/06 - M_PI/NULL
 */

#ifndef GLOBAL_H
#define GLOBAL_H

/* GLOBAL CONSTANTS */

#ifndef M_PI
#define M_PI            3.14159265f
#endif
#ifndef NULL
#define NULL            0
#endif

// Window
#define WIDTH           800
#define HEIGHT          600

// Window
#define GAME_WIDTH      200     // X
#define GAME_HEIGHT     200     // Y
#define GAME_DEPTH     -1000    // Z

// Camera
#define FOV             25


// Level
#define LEVEL_TIME      60000 // 1 minute/level
#define TITLE_TIME      50

// Panels
#define MARGIN          5
#define MESH_SIZE       40// should be a factor of GAME_WIDTH and GAME_HEIGHT

// Sky
#define SUN_SIZE        100
#define NUM_STARS       200
#define STAR_SPREAD     5

// Obstacles
#define MOVE_BY         5
#define FOGEND_L1       1.0
#define FOGEND_L2       0.85
#define FOGEND_L3       0.70
#define SPAWN_L1        1000
#define SPAWN_L2        500
#define SPAWN_L3        200

enum objType { SUN, TEAPOT, CUBE, VMASK, BUG, CONE, SKULL, GLOVE, SWORD };			// least of possible objects

// Player
#define PLAYER_SIZE     5
#define PLAYER_STEP     2.5
#define LEAN_DECELL		5
#define SENSITIVITY     20
#define PARTICLE_COUNT  50

// Points
#define P_HIT          -100
#define P_AVOID         5

#endif
