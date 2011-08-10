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

#define LEVEL_TIME      60000 // 1 minute/level

// Game World
#define GAME_WIDTH      200     // X
#define GAME_HEIGHT     200     // Y
#define GAME_DEPTH     -1000    // Z

#define FOV             25

// Obstacles
#define MOVE_BY         5
#define FOGEND_L1       1.0
#define FOGEND_L2       0.85
#define FOGEND_L3       0.70

#define R   0
#define G   1
#define B   2

enum objType { SUN, TEAPOT, CUBE, DODEC, ICOSA, CONE, TORUS };			// least of possible objects

// Player
#define PLAYER_STEP     2
#define LEAN_DECELL		2

// Points
#define P_HIT          -100
#define P_AVOID         100

#endif
