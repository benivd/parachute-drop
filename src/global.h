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

// Game World
#define GAME_WIDTH      200     // X
#define GAME_HEIGHT     200     // Y
#define GAME_DEPTH     -1000     // Z

// Obstacles
#define MOVE_BY         10
#define FOGEND_L1       1.0
#define FOGEND_L2       0.85
#define FOGEND_L3       0.70

#define R   0
#define G   1
#define B   2

// Player
#define PLAYER_STEP     0.5

#endif
