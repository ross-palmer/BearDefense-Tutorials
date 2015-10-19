#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include <string>


////////////////////////////////////////////////////////////
/// \brief A simple class that represents configuration
///   data relating to each menu item.
////////////////////////////////////////////////////////////

class MenuItem {
public:
	short m_size;			// The font size.
	std::string m_text;		// The text for this menu item.
	float m_x;				// The x,y position of this menu item.
	float m_y;
};

#endif