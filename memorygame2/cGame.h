#ifndef _GAME_H
#define _GAME_H

/*
==================================================================================
cGame.h
==================================================================================
*/

#include <SDL.h>

// Game specific includes
#include "treeplanterGame.h"


using namespace std;

class cGame
{
public:
	cGame();

	void initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void cleanUp(SDL_Window* theSDLWND);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer);
	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre);
	void update();
	void update(double deltaTime);
	bool getInput(bool theLoop);
	double getElapsedSeconds();

	static cGame* getInstance();

private:

	static cGame* pInstance;

	// for framerates
	time_point< high_resolution_clock > m_lastTime;
	time_point< high_resolution_clock > m_CurrentTime;
	duration< double > deltaTime;

	// game related variables
	vector<LPCSTR> textureName;
	vector<LPCSTR> texturesToUse;

	// Game Sounds
	vector<LPCSTR> soundList;
	vector<soundType> soundTypes;
	vector<LPCSTR> soundsToUse;

	// Fonts to use
	vector<LPCSTR> fontList;
	vector<LPCSTR> fontsToUse;
	// Text for Game
	vector<LPCSTR> gameTextNames;
	vector<LPCSTR> gameTextList;

	// Sprites for displaying background and rocket textures
	cSprite spriteBkgd;
	cTileMap theTileMap;
	cTreePicker theTreePicker;
	cSprite dragTile;
	// Game objects
	// Define the elements and there position in/on the array/map
	SDL_Point treeTileClicked;
	SDL_Point mapTileClicked;

	// Randomly assigned map that the player will need to guess.
	int memorisedMap[BOARD_SIZE][BOARD_SIZE];

	gameState theGameState;

	// Create vector array of button textures
	vector<LPCSTR> btnNameList;
	vector<LPCSTR> btnTexturesToUse;
	vector<SDL_Point> btnPos;
	vector <cButton> theButtons;
	//btnTypes theBtnType;
	SDL_Point theAreaClicked;
	

	cTexture* tempTextTexture;

	SDL_Rect pos;
	FPoint scale;

	bool loop;
};

#endif
