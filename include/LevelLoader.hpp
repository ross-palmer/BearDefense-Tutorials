#ifndef LEVELOADER_HPP
#define LEVELOADER_HPP

#include "MenuData.hpp"
#include "GameData.hpp"
#include "JSON/JSON.h"

////////////////////////////////////////////////////////////
/// \brief A class to load all the configuration data
///        required by the game. 
///
////////////////////////////////////////////////////////////

class LevelLoader {
public:
	////////////////////////////////////////////////////////////
	/// \brief Constructor
	///
	/// This constructor initialises the JSON parser and loads
	/// the menu and game level data.
	///
	/// \param filename The path and filename of the JSON file.
	///
	////////////////////////////////////////////////////////////
	LevelLoader(std::string const & filename);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// Frees resources acquired by the JSON parser.
	///
	////////////////////////////////////////////////////////////
	~LevelLoader();

	////////////////////////////////////////////////////////////
	/// \brief Loads the JSON data from the specified file.
	///
	/// \param filename The path and filename of the JSON file.
	///
	////////////////////////////////////////////////////////////
	void load(std::string const & filename);

	////////////////////////////////////////////////////////////
	/// \brief Get the menu configuration data
	///
	/// \return A MenuData instance containing config values
	///
	///
	////////////////////////////////////////////////////////////
	MenuData const & getMenuData() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the game configuration data
	///
	/// \return A GameData instance containing config values
	///
	///	
	////////////////////////////////////////////////////////////
	GameData const & getGameData() const;

private:	
	JSONValue *m_value;
	std::string m_JSONData;
	MenuData m_menuData;
	GameData m_gameData;

	void loadJSONData(std::string const & filename);

	void loadMenuData();

	void loadLevel1Data();

	void loadAIData();

	void loadAIWaypoints(JSONObject & ai, std::wstring const & pathName, int index, float startX, float startY);

	// Utility methods.
	JSONObject getTopLevelJSONObject();
	std::string wStringToString(std::wstring const & wstr);

	void calculateDirVec(int index, JSONArray & littleBearArray);
};

#endif