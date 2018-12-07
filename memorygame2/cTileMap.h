/*
=================
cTileMap.h
- Header file for class definition - SPECIFICATION
- Header file for the tileMap class which is a child of cSprite class
=================
*/
#ifndef _CTILEMAP_H
#define _CTILEMAP_H
#include "cSprite.h"
#include <random>



class cTileMap: public cSprite
{
protected:
	int tileMap[BOARD_SIZE][BOARD_SIZE];

private:
	SDL_Point mapStartXY;
	SDL_Point tileClickedRC;
	cSprite aTile;
	void initialiseMap();		// Set the initial values for the map

public:
	cTileMap();

	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt);		// Default render function
	void update(SDL_Point theMapAreaClicked, int theTreeToPlant);
	// Sets all tiles to 1
	void clear();
	// Get number in array
	int getMapValue(int column, int row);
	void setMapStartXY(SDL_Point startPosXY);
	SDL_Point getMapStartXY();
};
#endif