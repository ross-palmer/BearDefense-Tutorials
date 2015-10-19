#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP

#include <string>

////////////////////////////////////////////////////////////
/// \brief A class that stores gameplay data
/// 
////////////////////////////////////////////////////////////
class GameData {
public:
	// Global settings.
	std::string m_placeTowersText;
	int m_placeTowersTextSize;
	std::string m_fontFile;
	float m_placeTowersTextX;
	float m_placeTowersTextY;
	std::string m_gameLoseText;
	std::string m_particlesTextureFile;

	std::string m_goButtonFile;
	int m_goButtonWidth;
	int m_goButtonHeight;
	float m_goButtonX;
	float m_goButtonY;

	std::string m_towerPointsFile;
	int m_towerPoints;

	int m_honeyLevel;
	std::string m_honeyHiveFile;	
	int m_honeyHiveWidth;
	int m_honeyHiveRows;
	int m_honeyHiveCols;
	int m_honeyHiveFrames;
	float m_honeyHiveX;
	float m_honeyHiveY;

	std::string m_level1BackgroundFile;
	
	// Tower base and tower related fields.
	std::string m_towerBaseFile;
	int m_towerWidth;
	int m_towerHeight;
	std::string m_towerFile;	
	int m_numberOfTowers;
	int m_firingDelay;
	int m_towerRotationSpeed;
	float m_towerRotationOriginX;
	float m_towerRotationOriginY;

	int m_numberOfTowerBases;
	float m_towerBaseX[9];
	float m_towerBaseY[9];


	// Audio related fields...
	std::string m_mouseOverTowerBaseFile;
	std::string m_towerPlacedFile;
	std::string m_towerFiringFile;
	std::string m_bumbleBeesFile;

	// Projectile fields
	std::string m_projectileFile;
	float m_projectileCentreX;
	float m_projectileCentreY;
	int m_maxProjectiles;
	int m_timeToLive;
	int m_velocity;

	// AI fields
	std::string m_littleBearWalkingFile;	
	std::string m_littleBearWavingFile;
	int m_aiPaths;
	int m_maxNumLittleBears;
	int m_littleBearsPath1;
	int m_littleBearsPath2;
	int m_littleBearsPath3;
	int m_littleBearDamage;
	int m_littleBearSpawnInterval;
	float m_littleBearScale;
	float m_littleBearVelocity;
	float m_littleBearStartXPath1;
	float m_littleBearStartYPath1;

	float m_littleBearStartXPath2;
	float m_littleBearStartYPath2;

	float m_littleBearStartXPath3;
	float m_littleBearStartYPath3;

	int m_littleBearWalkingRows;
	int m_littleBearWalkingCols;
	int m_littleBearWalkingWidth;
	int m_littleBearWalkingHeight;

	int m_littleBearWavingRows;
	int m_littleBearWavingCols;
	int m_littleBearWavingWidth;
	int m_littleBearWavingHeight;

	int m_littleBearWayPoints;	
	float m_littleBearDirVecX[24];	// Dir. vec. to corresponding waypoint.
	float m_littleBearDirVecY[24];
	float m_littleBearWPX[24];	// WP = waypoint
	float m_littleBearWPY[24];

	std::string m_beesSwarmingFile;
	int m_beesSwarmingRows;
	int m_beesSwarmingWidth;
	int m_beesSwarmingHeight;
	int m_beesSwarmingOnScreenTime;
	
};

#endif