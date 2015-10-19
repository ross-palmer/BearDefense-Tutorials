#include "stdafx.h"
#include "MainMenuScreen.hpp"

////////////////////////////////////////////////////////////
MainMenuScreen::MainMenuScreen(MenuData const & menuData) :
	m_menuData(menuData),
	m_alphaMax(3 * 255),
	m_alphaDiv(3),
	m_playing(false)
{
}

////////////////////////////////////////////////////////////
Screen::Screens MainMenuScreen::run(sf::RenderWindow &app)
{
	sf::Event event;
	bool running = true;
	sf::Texture texture;
	sf::Sprite menuBackground;
	int alpha = 0;
	sf::Font font;
	sf::Text menuItem1;
	sf::Text menuItem2;
	sf::Text menuItem3;
	MainMenuOptions menuOption = MainMenuOptions::Play;

	// Load the menu background.
	if (!texture.loadFromFile(m_menuData.m_menuBackgroundFile))
	{
		std::cerr << "Error loading " << m_menuData.m_menuBackgroundFile << std::endl;
		return Screen::Screens::Quit;
	}
	menuBackground.setTexture(texture);
	
	// Load the menu font.
	if (!font.loadFromFile(m_menuData.m_menuFontFile))
	{
		std::cerr << "Error loading " << m_menuData.m_menuFontFile << std::endl;
		return Screen::Screens::Quit;
	}

	// Prepare the menu items.
	menuItem1.setFont(font);
	menuItem1.setCharacterSize(m_menuData.m_menuItemPlay.m_size);
	menuItem1.setString(m_menuData.m_menuItemPlay.m_text);
	menuItem1.setPosition({ m_menuData.m_menuItemPlay.m_x, m_menuData.m_menuItemPlay.m_y });

	menuItem2.setFont(font);
	menuItem2.setCharacterSize(m_menuData.m_menuItemExit.m_size);
	menuItem2.setString(m_menuData.m_menuItemExit.m_text);
	menuItem2.setPosition({ m_menuData.m_menuItemExit.m_x, m_menuData.m_menuItemExit.m_y });

	menuItem3.setFont(font);
	menuItem3.setCharacterSize(m_menuData.m_menuItemContinue.m_size);
	menuItem3.setString(m_menuData.m_menuItemContinue.m_text);
	menuItem3.setPosition({ m_menuData.m_menuItemContinue.m_x, m_menuData.m_menuItemContinue.m_y });

	// To ensure menu will only fade in on initial startup.
	if (m_playing)
	{
		alpha = m_alphaMax;
	}

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
				case sf::Keyboard::Up:
					menuOption = MainMenuOptions::Play;
					break;
				case sf::Keyboard::Down:
					menuOption = MainMenuOptions::Exit;
					break;
				case sf::Keyboard::Return:
					if (menuOption == MainMenuOptions::Play)
					{
						// Start game...
						m_playing = true;
						return Screen::Screens::Game;
					}
					else
					{
						// Quit...
						return Screen::Screens::Quit;
					}
					break;
				default:
					break;
				}
			}
		}
		// Slowly increase alpha to give the menu background a fade-in effect.
		if (alpha < m_alphaMax)
		{
			alpha++;
		}
		menuBackground.setColor(sf::Color(255, 255, 255, alpha / m_alphaDiv));
		// Highlight the selected menu item in red, other option is white.
		if (menuOption == MainMenuOptions::Play)
		{
			menuItem1.setColor(sf::Color(255, 0, 0, 255));
			menuItem2.setColor(sf::Color(255, 255, 255, 255));
			menuItem3.setColor(sf::Color(255, 0, 0, 255));
		}
		else
		{
			menuItem1.setColor(sf::Color(255, 255, 255, 255));
			menuItem2.setColor(sf::Color(255, 0, 0, 255));
			menuItem3.setColor(sf::Color(255, 255, 255, 255));
		}

		// Clear screen
		app.clear();
		// Draw menu background
		app.draw(menuBackground);
		// If menu fade-in is complete
		if (alpha == m_alphaMax)
		{
			// Only want to show two menu items (Play/Exit) or (Continue/Exit) at any one time.
			if (m_playing)
			{
				app.draw(menuItem3);
			}
			else
			{
				app.draw(menuItem1);
			}
			app.draw(menuItem2);
		}
		app.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return Screen::Screens::Quit;
}