#ifndef MENUDATA_HPP
#define MENUDATA_HPP

#include <string>
#include "MenuItem.hpp"

////////////////////////////////////////////////////////////
/// \brief A simple class that stores configuration
///   data relating to the appearance of our main menu.
////////////////////////////////////////////////////////////

class MenuData {
public:
	std::string m_menuBackgroundFile;	// A background image for the main menu.
	std::string m_menuFontFile;			// The font for menu items.
	MenuItem m_menuItemPlay;			// The 'Play' item.
	MenuItem m_menuItemExit;			// The 'Exit' item.
	MenuItem m_menuItemContinue;		// The 'Continue' item.
};

#endif