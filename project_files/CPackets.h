#pragma once

#include "stdafx.h"

enum CPacketsID : unsigned short
{
	CHECK_VERSION = 0, // reserved but not used, see enet_host_connect
	PLAYER_CONNECTED,
	PLAYER_DISCONNECTED,
	PLAYER_ONFOOT,
	PLAYER_BULLET_SHOT,
	PLAYER_HANDSHAKE,
	PLAYER_PLACE_WAYPOINT,
	PLAYER_GET_NAME,
	VEHICLE_SPAWN,
	PLAYER_SET_HOST,
	ADD_EXPLOSION,
	VEHICLE_REMOVE,
	VEHICLE_IDLE_UPDATE,
	VEHICLE_DRIVER_UPDATE,
	VEHICLE_ENTER,
	VEHICLE_EXIT,
	VEHICLE_DAMAGE,
	VEHICLE_COMPONENT_ADD,
	VEHICLE_COMPONENT_REMOVE,
	VEHICLE_PASSENGER_UPDATE,
	PLAYER_CHAT_MESSAGE,
	PED_SPAWN,
	PED_REMOVE,
	PED_ONFOOT,
	GAME_WEATHER_TIME,
	PED_ADD_TASK,
	PED_REMOVE_TASK,
	PLAYER_KEY_SYNC,
	PED_DRIVER_UPDATE,
	PED_SHOT_SYNC,
	PED_PASSENGER_UPDATE,
	PLAYER_AIM_SYNC,
	VEHICLE_CONFIRM,
	PED_CONFIRM,
	PLAYER_STATS,
	REBUILD_PLAYER,
	RESPAWN_PLAYER,
	ASSIGN_VEHICLE,
	MASS_PACKET_SEQUENCE,

	PACKET_ID_MAX
};

class CPackets
{
public:
	static int GetPacketSize(CPacketsID id)
	{
		static std::array<int, PACKET_ID_MAX> m_nPacketSize =
		{
			0, // CHECK_VERSION
			sizeof(PlayerConnected), // PLAYER_CONNECTED
			sizeof(PlayerDisconnected), // PLAYER_DISCONNECTED
			sizeof(PlayerOnFoot), // PLAYER_ONFOOT
			sizeof(PlayerBulletShot), // PLAYER_BULLET_SHOT
			sizeof(PlayerHandshake), // PLAYER_HANDSHAKE
			sizeof(PlayerPlaceWaypoint), // PLAYER_PLACE_WAYPOINT
			sizeof(PlayerGetName), // PLAYER_GET_NAME
			sizeof(VehicleSpawn), // VEHICLE_SPAWN
			sizeof(PlayerSetHost), // PLAYER_SET_HOST
			sizeof(AddExplosion), // ADD_EXPLOSION
			sizeof(VehicleRemove), // VEHICLE_REMOVE
			sizeof(VehicleIdleUpdate), // VEHICLE_IDLE_UPDATE
			sizeof(VehicleDriverUpdate), // VEHICLE_DRIVER_UPDATE
			sizeof(VehicleEnter), // VEHICLE_ENTER
			sizeof(VehicleExit), // VEHICLE_EXIT
			sizeof(VehicleDamage), // VEHICLE_DAMAGE
			sizeof(VehicleComponentAdd), // VEHICLE_COMPONENT_ADD
			sizeof(VehicleComponentRemove), // VEHICLE_COMPONENT_REMOVE
			sizeof(VehiclePassengerUpdate), // VEHICLE_PASSENGER_UPDATE
			sizeof(PlayerChatMessage), // PLAYER_CHAT_MESSAGE
			sizeof(PedSpawn), // PED_SPAWN
			sizeof(PedRemove), // PED_REMOVE
			sizeof(PedOnFoot), // PED_ONFOOT
			sizeof(GameWeatherTime), // GAME_WEATHER_TIME
			0, // PED_ADD_TASK
			sizeof(PedRemoveTask), // PED_REMOVE_TASK
			sizeof(PlayerKeySync), // PLAYER_KEY_SYNC
			sizeof(PedDriverUpdate), // PED_DRIVER_UPDATE
			sizeof(PedShotSync), // PED_SHOT_SYNC
			sizeof(PedPassengerSync), // PED_PASSENGER_UPDATE
			sizeof(PlayerAimSync), // PLAYER_AIM_SYNC
			sizeof(VehicleConfirm), // VEHICLE_CONFIRM
			sizeof(PedConfirm), // PED_CONFIRM
			sizeof(PlayerStats), // PLAYER_STATS
			sizeof(RebuildPlayer), // REBUILD_PLAYER
			sizeof(RespawnPlayer), // RESPAWN_PLAYER
			sizeof(AssignVehicleSyncer), // ASSIGN_VEHICLE
			0 // MASS_PACKET_SEQUENCE
		};

		return m_nPacketSize[id];
	}

	


	struct PlayerConnected
	{
		int id;
		bool isAlreadyConnected; // prevents spam in the chat when connecting by distinguishing already connected players from newly joined ones
	};

	struct PlayerDisconnected
	{
		int id;
		unsigned char reason;
	};

	struct PlayerOnFoot
	{
		int id = 0;
		CVector position = CVector();
		CVector velocity = CVector();
		float rotation = 0.0f;
		unsigned char health = 100;
		unsigned char armour = 0;
		unsigned char weapon = 0;
		unsigned short ammo = 0;
		bool ducking = false;
		bool hasJetpack = false;
		char fightingStyle = 4;
	};

	#pragma pack(1)
	struct PlayerBulletShot
	{
		int playerid;
		int targetid;
		CVector startPos;
		CVector endPos;
		CColPoint colPoint;
		int incrementalHit;
		unsigned char entityType;
	};

	struct PlayerHandshake
	{
		int yourid;
	};

	struct PlayerPlaceWaypoint
	{
		int playerid;
		bool place;
		CVector position;
	};

	struct PlayerGetName
	{
		int playerid;
		char name[32 + 1];
	};

	struct PlayerSetHost
	{
		int playerid;
	};

	struct AddExplosion
	{
		unsigned char type;
		CVector pos;
		int time;
		bool usesSound;
		float cameraShake;
		bool isVisible;
	};

	struct VehicleSpawn
	{
		int vehicleid;
		unsigned char tempid;
		unsigned short modelid;
		CVector pos;
		float rot;
		unsigned char color1;
		unsigned char color2;
		unsigned char createdBy;
	};

	struct VehicleRemove
	{
		int vehicleid;
	};

	struct VehicleIdleUpdate
	{
		int vehicleid;
		CVector pos;
		CVector rot;
		CVector roll;
		CVector velocity;
		CVector turnSpeed;
		unsigned char color1;
		unsigned char color2;
		float health;
		char paintjob;
		float planeGearState;
		unsigned char locked;
	};

	struct VehicleDriverUpdate
	{
		int playerid;
		int vehicleid;
		CVector pos;
		CVector rot;
		CVector roll;
		CVector velocity;
		unsigned char playerHealth;
		unsigned char playerArmour;
		unsigned char weapon;
		unsigned short ammo;
		unsigned char color1;
		unsigned char color2;
		float health;
		char paintjob;
		float bikeLean;
		unsigned short miscComponentAngle; // hydra thrusters
		float planeGearState;
		unsigned char locked;
	};

	struct VehicleEnter
	{
		int playerid;
		int vehicleid;
		unsigned char seatid : 3;
		unsigned char force : 1;
		unsigned char passenger : 1;
	};

	struct VehicleExit
	{
		int playerid;
		bool force;
	};

	struct VehicleDamage
	{
		int vehicleid;
		CDamageManager damageManager;
	};

	struct VehicleComponentAdd
	{
		int vehicleid;
		int componentid;
	};

	struct VehicleComponentRemove
	{
		int vehicleid;
		int componentid;
	};

	struct VehiclePassengerUpdate
	{
		int playerid;
		int vehicleid;
		unsigned char playerHealth;
		unsigned char playerArmour;
		unsigned char weapon;
		unsigned short ammo;
		unsigned char driveby;
		unsigned char seatid;
	};

	struct PlayerChatMessage
	{
		int playerid;
		wchar_t message[CChat::MAX_MESSAGE_SIZE+1];
	};

	struct PedSpawn
	{
		int pedid;
		unsigned char tempid;
		short modelId;
		unsigned char pedType;
		CVector pos;
		unsigned char createdBy;
		char specialModelName[8];
	};

	struct PedRemove
	{
		int pedid;
	};

	struct PedOnFoot
	{
		int pedid = 0;
		CVector pos = CVector();
		CVector velocity = CVector();
		unsigned char health = 100;
		unsigned char armour = 0;
		unsigned char weapon = 0;
		unsigned short ammo = 0;
		float aimingRotation = 0.0f;
		float currentRotation = 0.0f;
		int lookDirection = 0;
		struct
		{
			unsigned char moveState : 3;
			unsigned char ducked : 1;
			unsigned char aiming : 1;
		};
		unsigned char fightingStyle = 4;
		CVector weaponAim;
	};
	
	struct GameWeatherTime
	{
		unsigned char newWeather;
		unsigned char oldWeather;
		unsigned char forcedWeather;
		unsigned char currentMonth;
		unsigned char currentDay;
		unsigned char currentHour;
		unsigned char currentMinute;
		unsigned int gameTickCount;
	};

	struct PedRemoveTask
	{
		int pedid;
		eTaskType taskid;
	};

	struct PlayerKeySync
	{
		int playerid;
		CCompressedControllerState newState;
	};

	struct PedDriverUpdate
	{
		int pedid;
		int vehicleid;
		CVector pos;
		CVector rot;
		CVector roll;
		CVector velocity;
		CVector turnSpeed;
		unsigned char pedHealth;
		unsigned char pedArmour;
		unsigned char weapon;
		unsigned short ammo;
		unsigned char color1;
		unsigned char color2;
		float health;
		char paintjob;
		float bikeLean;
		float planeGearState;
		unsigned char locked;
	};

	struct PedShotSync
	{
		int pedid;
		CVector origin;
		CVector effect;
		CVector target;
	};

	struct PedPassengerSync
	{
		int pedid;
		int vehicleid;
		unsigned char health;
		unsigned char armour;
		unsigned char weapon;
		unsigned short ammo;
		unsigned char seatid;
	};

	struct PlayerAimSync
	{
		int playerid;
		unsigned char cameraMode;
		float cameraFov;
		CVector front;
		CVector	source;
		CVector	up;
		float moveHeading;
		float aimY;
		float aimZ;
	};

	struct VehicleConfirm
	{
		unsigned char tempid = 255;
		int vehicleid;
	};

	struct PedConfirm
	{
		unsigned char tempid = 255;
		int pedid;
	};

	struct PlayerStats
	{
		int playerid;
		float stats[14];
	};

	struct RebuildPlayer
	{
		int playerid;
		CPedClothesDesc clothesData;
	};

	struct AssignVehicleSyncer
	{
		int vehicleid;
	};

	struct RespawnPlayer
	{
		int playerid;
	};
};