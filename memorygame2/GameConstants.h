#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

// Windows & SDL 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>

using namespace std::chrono;

#include <SDL.h>
// Image Texture loading library
#include <SDL_image.h>
// Font loading library
#include <SDL_ttf.h>
// Sound loading library
#include <SDL_mixer.h>

//define board size
#define BOARD_SIZE 3

// Maths functions
#include <math.h>
constexpr auto PI = 3.14159265;

// STL Container & Algorithms
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//Define the string to appear in the top left corner of the window
#define WINDOW_TITLE "Using Arrays to map tiles and Mouse Input to plant new Trees!"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

// This header file contains all the constants & enumarated types for the game
typedef struct fpoint
{
	float  X;
	float  Y;
}FPoint;

inline SDL_Point operator+(SDL_Point const &a, SDL_Point const &b)
{
	return SDL_Point{ a.x + b.x , a.y + b.y };
}


enum class textType { solid, blended, shaded };
enum class soundType { sfx, music };
enum class gameState { menu, memorise, play, score, quit };
enum class btnTypes { exit, instruct, load, play, save, settings };
#endif