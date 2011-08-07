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

#ifndef M_PI
#define M_PI            3.14159265f
#endif
#ifndef NULL
#define NULL            0
#endif

// Window
#define WIDTH           800
#define HEIGHT          600

// Game World
#define GAME_WIDTH      200     // X
#define GAME_HEIGHT     200     // Y
#define GAME_DEPTH     -1000     // Z

#define R   0
#define G   1
#define B   2

#endif
