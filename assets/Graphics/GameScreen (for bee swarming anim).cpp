#include "stdafx.h"
#include "GameScreen.hpp"

////////////////////////////////////////////////////////////
void GameScreen::loadLevel1Assets() {
	
	
	

	// Load sprite texture.
	if (!m_tempTexture.loadFromFile(".\\assets\\graphics\\BeesSwarming.png"))
	{
		std::string s("Error loading " );
		throw std::exception(s.c_str());
	}

	m_anim.setSpriteSheet(m_tempTexture);
	m_anim.addFrame(sf::IntRect(0, 0, 168, 56));
	m_anim.addFrame(sf::IntRect(168, 0, 168, 56));
	m_anim.addFrame(sf::IntRect(336, 0, 168, 56));

	m_animSprite.setPosition(200, 200);
	m_animSprite.play(m_anim);


	// Load the level1 background image.
	if (!m_level1BackgroundTexture.loadFromFile(m_gameData.m_level1BackgroundFile))
	{		
		std::string s("Error loading " + m_gameData.m_level1BackgroundFile);
		throw std::exception(s.c_str());
	}
	m_levelBackground.setTexture(m_level1BackgroundTexture);

	// Load and the tower base
	if (!m_towerBaseTexture.loadFromFile(m_gameData.m_towerBaseFile))
	{
		std::string s("Error loading " + m_gameData.m_towerBaseFile);		
		throw std::exception(s.c_str());
	}

	// Create the animations for the tower bases.	
	m_toggleBaseColour.setSpriteSheet(m_towerBaseTexture);		
	m_toggleBaseColour.addFrame(sf::IntRect(0, 0, 62, 53));
	m_toggleBaseColour.addFrame(sf::IntRect(62, 0, 62, 53));

	// Fill the vector with m_gameData.m_numberOfTowerBases exactly.
	// Each tower base is an AnimatedSprite.
	m_towerBases.resize(m_gameData.m_numberOfTowerBases, AnimatedSprite(sf::seconds(0.2), true, false));	

	// Position each tower.
	for (int i = 0; i < m_towerBases.size(); i++) 
	{
		m_towerBases.at(i).setPosition(m_gameData.m_towerBaseX[i], m_gameData.m_towerBaseY[i]);
		// Set the initial animation state for each tower.
		m_towerBases.at(i).play(m_toggleBaseColour);
	}

}

////////////////////////////////////////////////////////////
GameScreen::GameScreen(GameData const & gameData) :
	m_gameData(gameData)	,
	m_animSprite(sf::seconds(0.2), true, false)
{
	loadLevel1Assets();
	// Create the container of our game components.
	m_container.reset(new ContainerObject(this));
	// Get a reference to the various game entities for later.	
	m_playerEntity.reset(new PlayerEntity(m_container->getPlayerInputComponent()));
	m_soundEntity.reset(new SoundPlayerEntity(m_container->getSoundPlayerComponent()));
}

////////////////////////////////////////////////////////////
Screen::Screens GameScreen::run(sf::RenderWindow &app)
{	
	sf::Event event;
	bool running = true;	
	static int i = 0;
	while (running)
	{
		// Verifying events
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
					m_animSprite.setFrame((i++)%3, true);
					break;
				/*case sf::Keyboard::Down:
					m_posy += m_movementStep;
					break;
				case sf::Keyboard::Left:
					m_posx -= m_movementStep;
					break;
				case sf::Keyboard::Right:
					m_posx += m_movementStep;
					break;
				*/
				default:
					break;
				}
			}
		}		

		switch (m_gameState)
		{
		case GameStates::TowerPlacement:
			m_playerEntity->update(app);
			m_soundEntity->update(app);			
			break;
		case GameStates::GameRunning:
			break;
		default:
			break;
		}
		
		// Clearing screen
		app.clear(sf::Color(0, 0, 0, 0));	
		// Draw menu background
		app.draw(m_levelBackground);
		// Draw each tower base
		for (int i = 0; i < m_towerBases.size(); i++)
		{
			app.draw(m_towerBases.at(i));			
		}		

		app.draw(m_animSprite);
		
		app.display();		
		
	}

	//Never reaching this point normally, but just in case, exit the application
	return Screen::Screens::Quit;
	
}

////////////////////////////////////////////////////////////
std::vector<AnimatedSprite> & GameScreen::getTowerBases()
{
	return m_towerBases;
}

////////////////////////////////////////////////////////////
GameData const & GameScreen::getGameData()
{
	return m_gameData;
}