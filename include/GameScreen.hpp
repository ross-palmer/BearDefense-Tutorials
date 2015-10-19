#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "Screen.hpp"
#include "GameData.hpp"

#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
/// \brief A class that represents our game screen
/// 
////////////////////////////////////////////////////////////

class GameScreen : public Screen 
{
public:	

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// This constructor stores a reference to game
	///   configuration data.
	///
	/// \param gameData The game configuration data.
	///
	////////////////////////////////////////////////////////////
	GameScreen(GameData const & gameData);

	////////////////////////////////////////////////////////////
	/// \brief run method
	///
	/// \param app The SFML RenderWindow
	///
	////////////////////////////////////////////////////////////
	virtual Screens run(sf::RenderWindow &app) override;

private:
	GameData const & m_gameData;
	sf::Texture m_level1BackgroundTexture;
	sf::Sprite m_levelBackground;

	void loadLevel1Background();
}; 

#endif