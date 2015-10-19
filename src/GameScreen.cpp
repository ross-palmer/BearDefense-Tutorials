#include "stdafx.h"
#include "GameScreen.hpp"

////////////////////////////////////////////////////////////
void GameScreen::loadLevel1Background() {	
	// Load the level1 background image.
	if (!m_level1BackgroundTexture.loadFromFile(m_gameData.m_level1BackgroundFile))
	{		
		std::string s("Error loading " + m_gameData.m_level1BackgroundFile);
		throw std::exception(s.c_str());
	}
	m_levelBackground.setTexture(m_level1BackgroundTexture);

}



////////////////////////////////////////////////////////////
GameScreen::GameScreen(GameData const & gameData) :
	m_gameData(gameData)	
{
	loadLevel1Background();	
}

////////////////////////////////////////////////////////////
Screen::Screens GameScreen::run(sf::RenderWindow &app)
{	
	sf::Event event;
	
	bool running = true;	
	
	while (running)
	{
		
		// While there are pending events.
		while (app.pollEvent(event))
		{		
			// Window closed
			if (event.type == sf::Event::Closed)
			{
				return Screen::Screens::Quit;
			}
			// Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					return Screen::Screens::MainMenu;
					break;
				case sf::Keyboard::Up:
					break;
				
				default:
					break;
				}
			}
		
		}		
		
		// Clearing screen
		app.clear(sf::Color(0, 0, 0, 0));
		// Draw level background
		app.draw(m_levelBackground);
						
		app.display();		
		
	}

	//Never reaching this point normally, but just in case, exit the application
	return Screen::Screens::Quit;
	
}


