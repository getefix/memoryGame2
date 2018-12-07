/*
=================
cTreePicker.h
- Header file for class definition - SPECIFICATION
- Header file for the tileMap class which is a child of cSprite class
=================
*/
#ifndef _CTREEPICKER_H
#define _CTREEPICKER_H
#include "GameConstants.h"
#include "cSprite.h"

class cTreePicker : public cSprite
{
protected:
	int treePickingList[4];
	int tileMap[8][8];

private:
	SDL_Point treeListStartXY;
	SDL_Point tileClickedRC;
	cSprite aTile;
	int theTreeToPlant;

	void initialiseTreeList();		// Set the initial values for the map

public:
	cTreePicker();

	void render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt);		// Default render function
	void update(SDL_Point theAreaClicked);
	void setTreeListStartXY(SDL_Point startPosXY);
	SDL_Point getTreeListStartXY();
	void setTreeToPlant(int treeToPlant);
	int getTreeToPlant();
};
#endif