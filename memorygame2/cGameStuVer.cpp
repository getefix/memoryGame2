/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cButtonMgr* theButtonMgr = cButtonMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	this->m_lastTime = high_resolution_clock::now();
	
	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);
	
	theTextureMgr->setRenderer(theRenderer);
	// Store the textures
	textureName = { "grass", "grassstone", "grassbare", "grassdark", "treedark", "treelight", "treescary", "treeautumn", "theBackground", "transparent", "theBackground", "OpeningScreen", "ClosingScreen" };
	texturesToUse = { "Images\\tile1.png", "Images\\tile2.png", "Images\\tile3.png", "Images\\tile4.png", "Images\\tree1.png", "Images\\tree2.png", "Images\\tree3.png", "Images\\tree4.png", "Images\\theBackground.png", "Images\\transparent.png", "Images/Bkg/Bkgnd.png", "Images/Bkg/OpeningScreenF.png", "Images/Bkg/ClosingScreenF.png" };
	for (unsigned int tCount = 0; tCount < textureName.size(); tCount++)
	{	
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}
	theTileMap.setMapStartXY({ 100, 100 });

	// Save randomly created map in variable variable.
	for (int column = 0; column < BOARD_SIZE; column++)
	{
		for (int row = 0; row < BOARD_SIZE; row++)
		{
			memorisedMap[column][row] = theTileMap.getMapValue(column,row);
		}
	}

	// Load game sounds
	soundList = { "theme", "click" };
	soundTypes = { soundType::music, soundType::sfx };
	soundsToUse = { "Audio/Theme/Kevin_MacLeod_-_Winter_Reflections.wav", "Audio/SFX/ClickOn.wav" };
	for (unsigned int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundMgr->getSnd("theme")->play(-1);

	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("OpeningScreen"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("OpeningScreen")->getTWidth(), theTextureMgr->getTexture("OpeningScreen")->getTHeight());


	theTreePicker.setTreeListStartXY({ 740, 100 });

	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	dragTile.setSpritePos({ 0, 0 });
	dragTile.setTexture(theTextureMgr->getTexture("transparent"));
	dragTile.setSpriteDimensions(theTextureMgr->getTexture("transparent")->getTWidth(), theTextureMgr->getTexture("transparent")->getTHeight());


	// Creating buttons
	// exit, play, clear, submit, menu
	btnNameList = { "exit_btn", "play_btn", "clear_btn", "submit_btn", "menu_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_play.png", "Images/Buttons/button_load.png", "Images/Buttons/button_settings.png", "Images/Buttons/button_menu.png" };
	btnPos = { { 400, 375 },{ 400, 300 },{ 400, 300 },{ 500, 500 },{ 400, 300 },{ 740, 500 },{ 400, 300 } };
	for (unsigned int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureMgr->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (unsigned int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureMgr->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureMgr->getTexture(btnNameList[bCount])->getTWidth(), theTextureMgr->getTexture(btnNameList[bCount])->getTHeight());
		theButtonMgr->add(btnNameList[bCount], newBtn);
	}
	theGameState = gameState::menu;
	//theBtnType = btnTypes::exit;


	// Create textures for Game Dialogue (text)
	fontList = { "pirate", "skeleton" };
	fontsToUse = { "Fonts/BlackPearl.ttf", "Fonts/SkeletonCloset.ttf" };
	for (unsigned int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 48);
	}
	// Create text Textures
	gameTextNames = { "TitleTxt", "CollectTxt", "InstructTxt", "ThanksTxt", "SeeYouTxt","BottleCount" };
	gameTextList = { "Pirate  Treasure", "Collect the bottles of Rum!", "Use the arrow keys to navigate the map.", "Thanks for playing!", "See you again soon!", "Collected: " };
	for (unsigned int text = 0; text < gameTextNames.size(); text++)
	{
		if (text == 0)
		{
			theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("pirate")->createTextTexture(theRenderer, gameTextList[text], textType::solid, { 44, 203, 112, 255 }, { 0, 0, 0, 0 }));
		}
		else
		{
			theTextureMgr->addTexture(gameTextNames[text], theFontMgr->getFont("skeleton")->createTextTexture(theRenderer, gameTextList[text], textType::solid, { 44, 203, 112, 255 }, { 0, 0, 0, 0 }));
		}
	}

}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);


	switch (theGameState)
	{
	case gameState::menu:
	
		spriteBkgd.setTexture(theTextureMgr->getTexture("OpeningScreen"));
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// Render the Title
		tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("CollectTxt");
		pos = { 50, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("InstructTxt");
		pos = { 50, 175, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		// Render Button
		theButtonMgr->getBtn("play_btn")->render(theRenderer, &theButtonMgr->getBtn("play_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("play_btn")->getSpritePos(), theButtonMgr->getBtn("play_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 400, 375 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
	
	
	break;
	case gameState::memorise:
	
		spriteBkgd.setTexture(theTextureMgr->getTexture("OpeningScreen"));
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		theTileMap.render(theSDLWND, theRenderer, theTextureMgr, textureName);

		theButtonMgr->getBtn("clear_btn")->setSpritePos({ WINDOW_WIDTH-100, 600 });
		theButtonMgr->getBtn("clear_btn")->render(theRenderer, &theButtonMgr->getBtn("clear_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("clear_btn")->getSpritePos(), theButtonMgr->getBtn("clear_btn")->getSpriteScale());
		
	
	break;
	case gameState::hide:
	
		// Clearing the tiles
		theTileMap.clear();
		theGameState = gameState::play;
	
	break;
	case gameState::play:	

		spriteBkgd.setTexture(theTextureMgr->getTexture("OpeningScreen"));
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		theTileMap.render(theSDLWND, theRenderer, theTextureMgr, textureName);
		theTreePicker.render(theSDLWND, theRenderer, theTextureMgr, textureName);
		if (theTreePicker.getTreeToPlant() > -1)
		{
			dragTile.render(theRenderer, &dragTile.getSpriteDimensions(), &dragTile.getSpritePos(), spriteBkgd.getSpriteScale());
		}

		theButtonMgr->getBtn("submit_btn")->setSpritePos({ 850, 600 });
		theButtonMgr->getBtn("submit_btn")->render(theRenderer, &theButtonMgr->getBtn("submit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("submit_btn")->getSpritePos(), theButtonMgr->getBtn("submit_btn")->getSpriteScale());

	
	break;
	case gameState::score:
	
		cout << "score";
		/*
		spriteBkgd.setTexture(theTextureMgr->getTexture("ClosingScreen"));
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		tempTextTexture = theTextureMgr->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("ThanksTxt");
		pos = { 50, 100, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureMgr->getTexture("SeeYouTxt");
		pos = { 50, 175, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 500, 500 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());
		theButtonMgr->getBtn("exit_btn")->setSpritePos({ 500, 575 });
		theButtonMgr->getBtn("exit_btn")->render(theRenderer, &theButtonMgr->getBtn("exit_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("exit_btn")->getSpritePos(), theButtonMgr->getBtn("exit_btn")->getSpriteScale());
		*/

		theButtonMgr->getBtn("menu_btn")->setSpritePos({ 350, 600 });
		theButtonMgr->getBtn("menu_btn")->render(theRenderer, &theButtonMgr->getBtn("menu_btn")->getSpriteDimensions(), &theButtonMgr->getBtn("menu_btn")->getSpritePos(), theButtonMgr->getBtn("menu_btn")->getSpriteScale());

	break;
	case gameState::quit:
	
		loop = false;
		
	
	break;
	default:
		break;
	}


	










	
	SDL_RenderPresent(theRenderer);
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	
	switch (theGameState)
	{
	case gameState::menu:
	
		theGameState = theButtonMgr->getBtn("play_btn")->update(theGameState, gameState::memorise, theAreaClicked);
		theGameState = theButtonMgr->getBtn("exit_btn")->update(theGameState, gameState::quit, theAreaClicked);
	
	break;
	case gameState::memorise:
	
		theGameState = theButtonMgr->getBtn("clear_btn")->update(theGameState, gameState::hide, theAreaClicked);
	
	break;
	case gameState::hide:
	
		
	
	break;
	case gameState::play: 
		theGameState = theButtonMgr->getBtn("submit_btn")->update(theGameState, gameState::score, theAreaClicked);
	
	break;
	case gameState::score:
	
		theGameState = theButtonMgr->getBtn("menu_btn")->update(theGameState, gameState::menu, theAreaClicked);
	
	break;
	default:
		break;
	}




}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					theAreaClicked = { event.motion.x, event.motion.y };

					// Lab code goes here
					//get mouse point
					SDL_Point mousePos;
					SDL_GetMouseState(&mousePos.x, &mousePos.y);
					//call update on tree picker to set the tree to plant
					theTreePicker.update(mousePos);

					//show the drag tile
					int textureIndex = theTreePicker.getTreeToPlant();
					if (textureIndex >= 0)
					{
						textureIndex = 4 + (textureIndex % 5);
						dragTile.setTexture(theTextureMgr->getTexture(textureName[textureIndex]));
					}
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					
					// get mouse point
						SDL_Point mousePos;
					SDL_GetMouseState(&mousePos.x, &mousePos.y);
					//call update on tile map passing in the tree to plant
					theTileMap.update(mousePos, theTreePicker.getTreeToPlant());

					//reset the tree to plant
					theTreePicker.setTreeToPlant(-1);

					//hide the drag tile
					dragTile.setTexture(theTextureMgr->getTexture("transparent"));
					
				}
				break;
				case SDL_BUTTON_RIGHT:
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEMOTION:
			{
				
				// Lab Code goes here
				//get mouse point
				SDL_Point mousePos;
				SDL_GetMouseState(&mousePos.x, &mousePos.y);

				//set drag tile position
				dragTile.setSpritePos(mousePos);
			}
			break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					theLoop = false;
					break;
				default:
					break;
				}

			default:
				break;
		}

	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}

