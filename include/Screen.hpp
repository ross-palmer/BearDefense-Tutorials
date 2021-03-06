#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
/// \brief A simple abstract class to represent each screen
/// 
////////////////////////////////////////////////////////////

class Screen
{
public:

	enum class Screens { Quit = -1, MainMenu, Game };

	////////////////////////////////////////////////////////////
	/// \brief run method
	///
	/// \param app The SFML RenderWindow
	///
	////////////////////////////////////////////////////////////
	virtual Screens run(sf::RenderWindow &app) = 0;

	
};

#endif