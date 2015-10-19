//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"thor-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "Screen.hpp"
#include "MainMenuScreen.hpp"
#include "GameScreen.hpp"
#include "LevelLoader.hpp"
////////////////////////////////////////////////////////////
/// Entrypoint of application 
//////////////////////////////////////////////////////////// 


int main(int argc, char** argv)
{
	// Applications variables
	std::vector<Screen*> screensList;
	Screen::Screens screenType = Screen::Screens::MainMenu;

	// Window creation
	sf::RenderWindow app(sf::VideoMode(1440, 900, 32), "BearDefense");
	
	// Create the level loader object to load general game data.
	LevelLoader loader(".\\data\\GeneralGameData.json");

	// Load the AI data.
	loader.load(".\\data\\AIGameData.json");

	// Prepare menu and game screens
	MainMenuScreen mainMenu(loader.getMenuData());
	screensList.push_back(&mainMenu);
	GameScreen gameScreen(loader.getGameData());
	screensList.push_back(&gameScreen);

	// Main loop - invokes the run method on the currently 
	//  selected screen type (i.e. main menu or game screen).
	while (screenType != Screen::Screens::Quit)
	{
		if (screenType == Screen::Screens::Game)
		{
			// Show the mouse cursor
			app.setMouseCursorVisible(true);
		}
		else
		{
			// Hide the mouse cursor
			app.setMouseCursorVisible(false);
		}
		screenType = screensList.at(static_cast<int>(screenType))->run(app);
	}

	return EXIT_SUCCESS;
}