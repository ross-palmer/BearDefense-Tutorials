#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <vector>
#include "GameData.hpp"
#include "GameStates.hpp"

class World
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
	World(GameData const & gameData);

	void update(sf::RenderWindow &app, sf::Mouse::Button &mouseButton);

	void reset();

	void setGameState(GameStates state);

	GameStates getGameState() const;

	GameData const & getGameData();

private:
	GameData const & m_gameData;
	GameStates m_gameState;

};

#endif

