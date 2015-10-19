#ifndef MAINMENUSCREEN_HPP
#define MAINMENUSCREEN_HPP

#include "Screen.hpp"
#include "MenuData.hpp"
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
/// \brief A class that represents our main menu
/// 
////////////////////////////////////////////////////////////

class MainMenuScreen : public Screen
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// This constructor stores a reference to main menu
	///   configuration data and sets default values
	///   that govern the appearance of menu items.
	///
	/// \param menuData The main menu configuration data.
	///
	////////////////////////////////////////////////////////////
	MainMenuScreen(MenuData const & menuData);
	
	////////////////////////////////////////////////////////////
	/// \brief run method
	///
	/// \param app The SFML RenderWindow
	///
	////////////////////////////////////////////////////////////
	virtual Screens run(sf::RenderWindow &app) override;

private:
	int m_alphaMax;
	int m_alphaDiv;
	bool m_playing;
	MenuData const & m_menuData;

	enum class MainMenuOptions { Play, Exit };
};

#endif