#include "stdafx.h"
#include "LevelLoader.hpp"



////////////////////////////////////////////////////////////
LevelLoader::LevelLoader(std::string const & filename) 
{
	
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());
	}
	loadMenuData();
	loadLevel1Data();
}

////////////////////////////////////////////////////////////
LevelLoader::~LevelLoader() {
	delete m_value;
}

////////////////////////////////////////////////////////////
void LevelLoader::load(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		throw std::exception(s.c_str());		
	}
	loadAIData();
}

////////////////////////////////////////////////////////////
void LevelLoader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	// Loads all the data in the file into a std::string.
	std::ifstream myfile(filename);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			m_JSONData.append(line);
		}
		myfile.close();
	}
	else
	{
		std::string errorMessage = "Could not open " + filename + " exiting!";
		throw std::exception(errorMessage.c_str());
	}
}

////////////////////////////////////////////////////////////
void LevelLoader::loadMenuData() 
{
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject gameData = root[L"general_game_data"]->AsObject();
	// Locate the menu background filename.
	if (gameData.find(L"menu_background_file") != gameData.end() && gameData[L"menu_background_file"]->IsString())
	{			
		m_menuData.m_menuBackgroundFile = wStringToString(gameData[L"menu_background_file"]->AsString());			
	}
	// For brevity, remaining checks on JSON types are skipped.
	// Locate the menu font file.	
	JSONObject globalSettings = gameData[L"global_settings"]->AsObject();
	m_menuData.m_menuFontFile = wStringToString(globalSettings[L"font_file"]->AsString());
	// Drill down into the various menu items.
	JSONObject menuItems = gameData[L"menu_items"]->AsObject();
	JSONObject item = menuItems[L"play"]->AsObject();
	m_menuData.m_menuItemPlay.m_size = item[L"size"]->AsNumber();
	m_menuData.m_menuItemPlay.m_text = wStringToString(item[L"text"]->AsString());
	m_menuData.m_menuItemPlay.m_x = item[L"x"]->AsNumber();
	m_menuData.m_menuItemPlay.m_y = item[L"y"]->AsNumber();		

	item = menuItems[L"exit"]->AsObject();
	m_menuData.m_menuItemExit.m_size = item[L"size"]->AsNumber();
	m_menuData.m_menuItemExit.m_text = wStringToString(item[L"text"]->AsString());
	m_menuData.m_menuItemExit.m_x = item[L"x"]->AsNumber();
	m_menuData.m_menuItemExit.m_y = item[L"y"]->AsNumber();

	item = menuItems[L"continue"]->AsObject();
	m_menuData.m_menuItemContinue.m_size = item[L"size"]->AsNumber();	
	m_menuData.m_menuItemContinue.m_text = wStringToString(item[L"text"]->AsString());
	m_menuData.m_menuItemContinue.m_x = item[L"x"]->AsNumber();
	m_menuData.m_menuItemContinue.m_y = item[L"y"]->AsNumber();	
}

////////////////////////////////////////////////////////////
void LevelLoader::loadLevel1Data()
{
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject gameData = root[L"general_game_data"]->AsObject();
	// Load the time to place towers field and related text settings.
	JSONObject globalSettings = gameData[L"global_settings"]->AsObject();	
	m_gameData.m_placeTowersText = wStringToString(globalSettings[L"place_towers_text"]->AsString());
	m_gameData.m_placeTowersTextSize = globalSettings[L"place_towers_text_size"]->AsNumber();
	m_gameData.m_fontFile = wStringToString(globalSettings[L"font_file"]->AsString());
	m_gameData.m_placeTowersTextX = globalSettings[L"place_towers_text_x"]->AsNumber();
	m_gameData.m_placeTowersTextY = globalSettings[L"place_towers_text_y"]->AsNumber();

	// Load game lose text.
	m_gameData.m_gameLoseText = wStringToString(globalSettings[L"game_lose_text"]->AsString());
	// Load the particle system texture file.
	m_gameData.m_particlesTextureFile = wStringToString(globalSettings[L"particles_texture_file"]->AsString());
	
	// Load the go button filename.
	m_gameData.m_goButtonFile = wStringToString(globalSettings[L"go_button_file"]->AsString());
	m_gameData.m_goButtonWidth = globalSettings[L"go_button_width"]->AsNumber();
	m_gameData.m_goButtonHeight = globalSettings[L"go_button_height"]->AsNumber();
	// Load the x,y position for the go button.
	JSONObject goButtonPos = globalSettings[L"go_button_position"]->AsObject();
	m_gameData.m_goButtonX = goButtonPos[L"x"]->AsNumber();
	m_gameData.m_goButtonY = goButtonPos[L"y"]->AsNumber();

	// Load the tower points background.
	m_gameData.m_towerPointsFile = wStringToString(globalSettings[L"tower_points_file"]->AsString());

	// Load the tower points.
	m_gameData.m_towerPoints = globalSettings[L"tower_points"]->AsNumber();

	// Load a value giving the honey level for the hive.
	m_gameData.m_honeyLevel = globalSettings[L"honey_level"]->AsNumber();

	// Load the honey hive base.
	m_gameData.m_honeyHiveFile = wStringToString(globalSettings[L"honey_hive_file"]->AsString());
	m_gameData.m_honeyHiveWidth = globalSettings[L"honey_hive_width"]->AsNumber();
	m_gameData.m_honeyHiveRows = globalSettings[L"honey_hive_rows"]->AsNumber();
	m_gameData.m_honeyHiveCols = globalSettings[L"honey_hive_cols"]->AsNumber();
	m_gameData.m_honeyHiveFrames = globalSettings[L"honey_hive_frames"]->AsNumber();

	JSONObject honeyHive = globalSettings[L"honey_hive_position"]->AsObject();
	m_gameData.m_honeyHiveX = honeyHive[L"x"]->AsNumber();
	m_gameData.m_honeyHiveY = honeyHive[L"y"]->AsNumber();

	// Load the tower file
	JSONObject tower = globalSettings[L"tower"]->AsObject();
	// Load the tower base image filename
	m_gameData.m_towerBaseFile = wStringToString(tower[L"tower_base_file"]->AsString());
	// Tower width	
	m_gameData.m_towerWidth = tower[L"tower_width"]->AsNumber();
	// Tower height
	m_gameData.m_towerHeight = tower[L"tower_height"]->AsNumber();
	m_gameData.m_towerFile = wStringToString(tower[L"tower_file"]->AsString());
	m_gameData.m_numberOfTowers = tower[L"max_num_towers"]->AsNumber();
	m_gameData.m_firingDelay = tower[L"firing_delay"]->AsNumber();
	m_gameData.m_towerRotationSpeed = tower[L"tower_rotation_speed"]->AsNumber();
	JSONObject towerRotationOrigin = tower[L"tower_rotation_origin"]->AsObject();
	m_gameData.m_towerRotationOriginX = towerRotationOrigin[L"x"]->AsNumber();
	m_gameData.m_towerRotationOriginY = towerRotationOrigin[L"y"]->AsNumber();

	// Load some sfx files
	JSONObject sfx = globalSettings[L"sfx"]->AsObject();
	m_gameData.m_mouseOverTowerBaseFile = wStringToString(sfx[L"mouse_over_tower_base"]->AsString());
	m_gameData.m_towerPlacedFile = wStringToString(sfx[L"tower_placed"]->AsString());
	m_gameData.m_towerFiringFile = wStringToString(sfx[L"tower_firing"]->AsString());
	m_gameData.m_bumbleBeesFile = wStringToString(sfx[L"bumble_bees"]->AsString());

	// Load the projectile related data	
	JSONObject projectile = globalSettings[L"projectile"]->AsObject();
	m_gameData.m_projectileFile = wStringToString(projectile[L"projectile_file"]->AsString());

	JSONObject projectileCentre = projectile[L"projectile_centre"]->AsObject();
	m_gameData.m_projectileCentreX = projectileCentre[L"x"]->AsNumber();
	m_gameData.m_projectileCentreY = projectileCentre[L"y"]->AsNumber();
	m_gameData.m_maxProjectiles = projectile[L"max_num_projectiles"]->AsNumber();
	m_gameData.m_timeToLive = projectile[L"time_to_live"]->AsNumber();
	m_gameData.m_velocity = projectile[L"velocity"]->AsNumber();

	// Load the background image filename for level 1
	JSONObject level1 = gameData[L"level1"]->AsObject();
	m_gameData.m_level1BackgroundFile = wStringToString(level1[L"level1_background_file"]->AsString());

	// Load the tower base positions from an array.
	JSONArray towerBaseArray = level1[L"tower_bases"]->AsArray();
	m_gameData.m_numberOfTowerBases = towerBaseArray.size();

	for (unsigned int i = 0; i < towerBaseArray.size(); i++)
	{
		// Each tower base position is a JSON Object.
		JSONObject towerBasePos = towerBaseArray[i]->AsObject();
		m_gameData.m_towerBaseX[i] = towerBasePos[L"x"]->AsNumber();
		m_gameData.m_towerBaseY[i] = towerBasePos[L"y"]->AsNumber();
	}		

}

////////////////////////////////////////////////////////////
void LevelLoader::loadAIData()
{
	// Retrieve the main (root) object
	JSONObject root = getTopLevelJSONObject();

	JSONObject aiGameData = root[L"ai_game_data"]->AsObject();
	// Load the ai game data for level 1.
	JSONObject level1 = aiGameData[L"level1"]->AsObject();
	JSONObject ai = level1[L"ai"]->AsObject();

	// Load the number of AI paths.
	m_gameData.m_aiPaths = ai[L"ai_paths"]->AsNumber();

	// Load the number of little bears.
	m_gameData.m_maxNumLittleBears = ai[L"max_num_little_bears"]->AsNumber();

	// Load the number of bears for the different paths.
	m_gameData.m_littleBearsPath1 = ai[L"little_bears_path1"]->AsNumber();
	m_gameData.m_littleBearsPath2 = ai[L"little_bears_path2"]->AsNumber();
	m_gameData.m_littleBearsPath3 = ai[L"little_bears_path3"]->AsNumber();

	// Load the damage capability of the little bear ai.
	m_gameData.m_littleBearDamage = ai[L"little_bear_damage"]->AsNumber();

	// Load the spawn interval.
	m_gameData.m_littleBearSpawnInterval = ai[L"little_bear_spawn_interval"]->AsNumber();
	// Load the scaling factor.
	m_gameData.m_littleBearScale = ai[L"little_bear_scale"]->AsNumber();
	// Load the velocity.
	m_gameData.m_littleBearVelocity = ai[L"little_bear_velocity"]->AsNumber();
	// Load the starting position for path 1.
	JSONObject startPosition = ai[L"little_bear_start_position_path1"]->AsObject();
	m_gameData.m_littleBearStartXPath1 = startPosition[L"x"]->AsNumber();
	m_gameData.m_littleBearStartYPath1 = startPosition[L"y"]->AsNumber();

	// Load the starting position for path 2.
	startPosition = ai[L"little_bear_start_position_path2"]->AsObject();
	m_gameData.m_littleBearStartXPath2 = startPosition[L"x"]->AsNumber();
	m_gameData.m_littleBearStartYPath2 = startPosition[L"y"]->AsNumber();

	// Load the starting position for path 3.
	startPosition = ai[L"little_bear_start_position_path3"]->AsObject();
	m_gameData.m_littleBearStartXPath3 = startPosition[L"x"]->AsNumber();
	m_gameData.m_littleBearStartYPath3 = startPosition[L"y"]->AsNumber();

	// Load the spritesheet (walking) data.
	JSONObject littleBearWalkingSpriteSheet = ai[L"little_bear_walking_spritesheet"]->AsObject();
	m_gameData.m_littleBearWalkingRows = littleBearWalkingSpriteSheet[L"rows"]->AsNumber();
	m_gameData.m_littleBearWalkingCols = littleBearWalkingSpriteSheet[L"columns"]->AsNumber();
	m_gameData.m_littleBearWalkingWidth = littleBearWalkingSpriteSheet[L"width"]->AsNumber();
	m_gameData.m_littleBearWalkingHeight = littleBearWalkingSpriteSheet[L"height"]->AsNumber();

	// Load the spritesheet (waving) data.
	JSONObject littleBearWavingSpriteSheet = ai[L"little_bear_waving_spritesheet"]->AsObject();
	m_gameData.m_littleBearWavingRows = littleBearWavingSpriteSheet[L"rows"]->AsNumber();
	m_gameData.m_littleBearWavingCols = littleBearWavingSpriteSheet[L"columns"]->AsNumber();
	m_gameData.m_littleBearWavingWidth = littleBearWavingSpriteSheet[L"width"]->AsNumber();
	m_gameData.m_littleBearWavingHeight = littleBearWavingSpriteSheet[L"height"]->AsNumber();

	// Load the image for the little bear walking.
	m_gameData.m_littleBearWalkingFile = wStringToString(ai[L"little_bear_walking_file"]->AsString());
	// Load the image for the little bear waving.
	m_gameData.m_littleBearWavingFile = wStringToString(ai[L"little_bear_waving_file"]->AsString());
	
	// Load AI waypoints for each of the three paths.
	int index = 0;
	loadAIWaypoints(ai, L"little_bear_waypoints_1", index, 
		m_gameData.m_littleBearStartXPath1, m_gameData.m_littleBearStartYPath1);
	
	index = m_gameData.m_littleBearsPath1;
	loadAIWaypoints(ai, L"little_bear_waypoints_2", index,
		m_gameData.m_littleBearStartXPath2, m_gameData.m_littleBearStartYPath2);

	index = m_gameData.m_littleBearsPath1 + m_gameData.m_littleBearsPath2;
	loadAIWaypoints(ai, L"little_bear_waypoints_3", index,
		m_gameData.m_littleBearStartXPath3, m_gameData.m_littleBearStartYPath3);

	
	m_gameData.m_beesSwarmingFile = wStringToString(ai[L"bees_swarming_file"]->AsString());
	JSONObject beesSwarmingSpriteSheet = ai[L"bees_swarming_spritesheet"]->AsObject();
	m_gameData.m_beesSwarmingRows = beesSwarmingSpriteSheet[L"rows"]->AsNumber();
	m_gameData.m_beesSwarmingWidth = beesSwarmingSpriteSheet[L"width"]->AsNumber();
	m_gameData.m_beesSwarmingHeight = beesSwarmingSpriteSheet[L"height"]->AsNumber();
	m_gameData.m_beesSwarmingOnScreenTime = beesSwarmingSpriteSheet[L"on_screen_time"]->AsNumber();
}

////////////////////////////////////////////////////////////
void LevelLoader::calculateDirVec(int index, JSONArray & littleBearArray)
{
	sf::Vector2f result;
	for (unsigned int i = 1; i < littleBearArray.size(); i++, index++)
	{
		// Each waypoint is a JSON Object.
		JSONObject waypoint = littleBearArray[i]->AsObject();
		m_gameData.m_littleBearWPX[index] = waypoint[L"x"]->AsNumber();
		m_gameData.m_littleBearWPY[index] = waypoint[L"y"]->AsNumber();

		sf::Vector2<float> vec(m_gameData.m_littleBearWPX[index] - m_gameData.m_littleBearWPX[index - 1], 
			m_gameData.m_littleBearWPY[index] - m_gameData.m_littleBearWPY[index - 1]);	
		
		result = thor::unitVector(vec);

		m_gameData.m_littleBearDirVecX[index] = result.x;
		m_gameData.m_littleBearDirVecY[index] = result.y;
	}
}

void LevelLoader::loadAIWaypoints(JSONObject & ai, std::wstring const & pathName, int index, float startX, float startY)
{
	// Load the AI data as waypoints from an array.
	JSONArray littleBearArray = ai[pathName]->AsArray();
	m_gameData.m_littleBearWayPoints = littleBearArray.size();

	// Calculate normalized vectors between each waypoint for path 1.
	JSONObject waypoint = littleBearArray[0]->AsObject();
	m_gameData.m_littleBearWPX[index] = waypoint[L"x"]->AsNumber();
	m_gameData.m_littleBearWPY[index] = waypoint[L"y"]->AsNumber();
	sf::Vector2<float> vec(m_gameData.m_littleBearWPX[index] - startX,
						   m_gameData.m_littleBearWPY[index] - startY);

	sf::Vector2f result = thor::unitVector(vec);

	m_gameData.m_littleBearDirVecX[index] = result.x;
	m_gameData.m_littleBearDirVecY[index] = result.y;

	index++;
	calculateDirVec(index, littleBearArray);
}

////////////////////////////////////////////////////////////
MenuData const & LevelLoader::getMenuData() const 
{
	return m_menuData;
}

GameData const & LevelLoader::getGameData() const
{
	return m_gameData;
}

////////////////////////////////////////////////////////////
JSONObject LevelLoader::getTopLevelJSONObject() {
	// Retrieve the main (root) object
	JSONObject root;

	if (m_value->IsObject() == false)
	{
		throw std::exception("Problem with root element in json file, exiting");
	}
	root = m_value->AsObject();
	
	return root;
}

////////////////////////////////////////////////////////////
std::string LevelLoader::wStringToString(std::wstring const & wstr)
{
	std::string s(wstr.begin(), wstr.end());
	return s;
}

