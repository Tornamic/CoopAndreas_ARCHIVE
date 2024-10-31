#pragma once
#include "stdafx.h"
#include "CControllerState.h"
#include "CNetwork.h"
#include "CNetworkPed.h"
#include "CNetworkPedManager.h"
#include "CNetworkPlayerManager.h"
#include "CNetworkVehicle.h"
#include "CNetworkVehicleManager.h"
#include "eNetworkEntityType.h"

enum ePacketType : unsigned short
{
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
	ENTITY_STREAM
};

class CPackets
{
public:
	struct PlayerConnected
	{
		uint16_t id;
	};

	struct PlayerDisconnected
	{
		uint16_t id;
		unsigned char reason;
	};
	#pragma pack(1)
	struct PlayerOnFoot
	{
		uint16_t id;
		CVector position;
		CVector	velocity;
		float rotation;
		unsigned char health;
		unsigned char armour;
		unsigned char weapon;
		unsigned short ammo;
		bool ducking;
		float aimX;
		float aimY;
		bool hasJetpack = false;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			// create packet
			CPackets::PlayerOnFoot* packet = (CPackets::PlayerOnFoot*)data;

			// set packet`s playerid, cuz incoming packet has id = 0
			packet->id = CNetworkPlayerManager::Instance().Get(peer)->GetId();


			CNetwork::SendPacketToAll(ePacketType::PLAYER_ONFOOT, packet, sizeof *packet, ENET_PACKET_FLAG_UNSEQUENCED, peer);
		}
	};

	#pragma pack(1)
	struct PlayerBulletShot
	{
		uint16_t playerid;
		uint16_t targetid;
		CVector startPos;
		CVector endPos;
		unsigned char colPoint[44]; // padding
		int incrementalHit;
		unsigned char entityType;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			// create packet
			CPackets::PlayerBulletShot* packet = (CPackets::PlayerBulletShot*)data;
			
			// set packet`s playerid, cuz incoming packet has id = 0
			packet->playerid = CNetworkPlayerManager::Instance().Get(peer)->GetId();

			CNetwork::SendPacketToAll(ePacketType::PLAYER_BULLET_SHOT, packet, sizeof * packet, ENET_PACKET_FLAG_UNSEQUENCED, peer);
		}
	};

	struct PlayerHandshake
	{
		uint16_t yourid;
	};

	struct PlayerPlaceWaypoint
	{
		uint16_t playerid;
		bool place;
		CVector position;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::PlayerPlaceWaypoint* packet = (CPackets::PlayerPlaceWaypoint*)data;
			packet->playerid = CNetworkPlayerManager::Instance().Get(peer)->GetId();
			CNetwork::SendPacketToAll(ePacketType::PLAYER_PLACE_WAYPOINT, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);
		}
	};

	struct PlayerGetName
	{
		uint16_t playerid;
		char name[32 + 1];

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::PlayerGetName* packet = (CPackets::PlayerGetName*)data;
			CNetworkPlayer* player = CNetworkPlayerManager::Instance().Get(peer);
			packet->playerid = player->GetId();
			player->SetName(packet->name);
			printf("player %d now also know as %s\n", packet->playerid, packet->name);
			CNetwork::SendPacketToAll(ePacketType::PLAYER_GET_NAME, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);
		}
	};

	struct PlayerSetHost
	{
		uint16_t playerid;
	};

	struct AddExplosion
	{
		unsigned char type;
		CVector pos;
		int time;
		char usesSound;
		float cameraShake;
		char isVisible;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::AddExplosion* packet = (CPackets::AddExplosion*)data;
			CNetwork::SendPacketToAll(ePacketType::ADD_EXPLOSION, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);
		}
	};

	struct VehicleSpawn
	{
		uint16_t vehicleid;
		int16_t modelid;
		CVector pos;
		float rot;
		unsigned char color1;
		unsigned char color2;
		
		static void Handle(ENetPeer* peer, void* data, int size)
		{
			if (!CNetworkPlayerManager::Instance().Get(peer)->IsHost())
				return;

			CPackets::VehicleSpawn* packet = (CPackets::VehicleSpawn*)data;
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_SPAWN, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);
			
			CNetworkVehicle* vehicle = new CNetworkVehicle(packet->vehicleid, packet->modelid);

			auto& syncData = vehicle->GetSyncData();

			syncData.m_vecPosition = packet->pos;
			syncData.m_vecRotation.z = packet->rot;
			syncData.m_nPrimaryColor = packet->color1;
			syncData.m_nSecondaryColor = packet->color2;

			CNetworkVehicleManager::Instance().Add(vehicle);
		}
	};

	struct VehicleRemove
	{
		uint16_t vehicleid;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			if (!CNetworkPlayerManager::Instance().Get(peer)->IsHost())
				return;

			CPackets::VehicleRemove* packet = (CPackets::VehicleRemove*)data;
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_REMOVE, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);

			CNetworkVehicle* vehicle = CNetworkVehicleManager::Instance().Get(packet->vehicleid);
			CNetworkVehicleManager::Instance().Remove(vehicle);
		}
	};

	struct VehicleIdleUpdate
	{
		uint16_t vehicleid;
		CVector pos;
		CVector rot;
		CVector roll;
		CVector velocity;
		unsigned char color1;
		unsigned char color2;
		float health;
		char paintjob;
		float planeGearState;
		unsigned char locked;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			if (!CNetworkPlayerManager::Instance().Get(peer)->IsHost())
				return;

			CPackets::VehicleIdleUpdate* packet = (CPackets::VehicleIdleUpdate*)data;
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_IDLE_UPDATE, packet, sizeof * packet, ENET_PACKET_FLAG_UNSEQUENCED, peer);

			CNetworkVehicle* vehicle = CNetworkVehicleManager::Instance().Get(packet->vehicleid);
			
			if (!vehicle)
				return;

			auto& syncData = vehicle->GetSyncData();

			syncData.m_vecPosition = packet->pos;
			syncData.m_vecRotation = packet->rot;
		}
	};

	struct VehicleDriverUpdate
	{
		uint16_t playerid;
		uint16_t vehicleid;
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
		float turretAimHorizontal;
		float turretAimVertical;
		unsigned short miscComponentAngle; // hydra thrusters
		float planeGearState;
		unsigned char locked;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::VehicleDriverUpdate* packet = (CPackets::VehicleDriverUpdate*)data;
			packet->playerid = CNetworkPlayerManager::Instance().Get(peer)->GetId();
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_DRIVER_UPDATE, packet, sizeof * packet, ENET_PACKET_FLAG_UNSEQUENCED, peer);

			CNetworkVehicle* vehicle = CNetworkVehicleManager::Instance().Get(packet->vehicleid);

			auto& syncData = vehicle->GetSyncData();

			syncData.m_vecPosition = packet->pos;
			syncData.m_vecRotation = packet->rot;
		}
	};

	struct VehicleEnter
	{
		uint16_t playerid;
		uint16_t vehicleid;
		unsigned char seatid;
		bool force; // if true - put directly in vehicle (without any anim)

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::VehicleEnter* packet = (CPackets::VehicleEnter*)data;
			CNetworkPlayer* player = CNetworkPlayerManager::Instance().Get(peer);

			CNetworkVehicle* vehicle = CNetworkVehicleManager::Instance().Get(packet->vehicleid);
			player->SetSeatId(packet->seatid);
			player->SetVehicle(vehicle);

			packet->playerid = player->GetId();

			CNetwork::SendPacketToAll(ePacketType::VEHICLE_ENTER, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);

			vehicle->m_aOccupants[packet->seatid] = player;
		}
	};

	struct VehicleExit
	{
		uint16_t playerid;
		bool force;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::VehicleExit* packet = (CPackets::VehicleExit*)data;
			CNetworkPlayer* player = CNetworkPlayerManager::Instance().Get(peer);
			packet->playerid = player->GetId();
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_EXIT, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);

			CNetworkVehicle* vehicle = player->GetVehicle();

			vehicle->m_aOccupants[player->GetSeatId()] = nullptr;
			player->SetSeatId(-1);
			player->SetVehicle(nullptr);
		}
	};

	struct VehicleDamage
	{
		uint16_t vehicleid;
		unsigned char damageManager_padding[23];

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::VehicleDamage* packet = (CPackets::VehicleDamage*)data;
			memcpy(CNetworkVehicleManager::Instance().Get(packet->vehicleid)->m_damageManager_padding, packet->damageManager_padding, 23);
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_DAMAGE, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);
		}
	};

	struct VehicleComponentAdd
	{
		uint16_t vehicleid;
		int componentid;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::VehicleComponentAdd* packet = (CPackets::VehicleComponentAdd*)data;
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_COMPONENT_ADD, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);

			CNetworkVehicle* vehicle = CNetworkVehicleManager::Instance().Get(packet->vehicleid);
			vehicle->m_aComponents.push_back(packet->componentid);
		}
	};

	struct VehicleComponentRemove
	{
		uint16_t vehicleid;
		int componentid;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::VehicleComponentAdd* packet = (CPackets::VehicleComponentAdd*)data;
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_COMPONENT_REMOVE, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);

			CNetworkVehicle* vehicle = CNetworkVehicleManager::Instance().Get(packet->vehicleid);

			auto it = std::find(vehicle->m_aComponents.begin(), vehicle->m_aComponents.end(), packet->componentid);
			if (it != vehicle->m_aComponents.end())
				vehicle->m_aComponents.erase(it);
		}
	};

	struct VehiclePassengerUpdate
	{
		uint16_t playerid;
		uint16_t vehicleid;
		unsigned char playerHealth;
		unsigned char playerArmour;
		unsigned char weapon;
		unsigned short ammo;
		unsigned char driveby;
		CVector aim;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::VehiclePassengerUpdate* packet = (CPackets::VehiclePassengerUpdate*)data;
			packet->playerid = CNetworkPlayerManager::Instance().Get(peer)->GetId();
			CNetwork::SendPacketToAll(ePacketType::VEHICLE_PASSENGER_UPDATE, packet, sizeof * packet, ENET_PACKET_FLAG_UNSEQUENCED, peer);
		}
	};

	struct PlayerChatMessage
	{
		uint16_t playerid;
		char message[128 + 1];

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::PlayerChatMessage* packet = (CPackets::PlayerChatMessage*)data;
			packet->playerid = CNetworkPlayerManager::Instance().Get(peer)->GetId();
			CNetwork::SendPacketToAll(ePacketType::PLAYER_CHAT_MESSAGE, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);
		}
	};

	struct PedSpawn
	{
		uint16_t pedid;
		short modelId;
		unsigned char pedType;
		CVector pos;
		unsigned char createdBy;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			if (!CNetworkPlayerManager::Instance().Get(peer)->m_bIsHost)
				return;

			CPackets::PedSpawn* packet = (CPackets::PedSpawn*)data;
			CNetwork::SendPacketToAll(ePacketType::PED_SPAWN, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);

			CNetworkPed* ped = new CNetworkPed(packet->pedid, packet->modelId, packet->pedType, packet->createdBy);

			CNetworkPedManager::Instance().Add(ped);
		}
	};

	struct PedRemove
	{
		uint16_t pedid;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			if (!CNetworkPlayerManager::Instance().Get(peer)->m_bIsHost)
				return;

			CPackets::PedRemove* packet = (CPackets::PedRemove*)data;

			CNetworkPed* ped = CNetworkPedManager::Instance().Get(packet->pedid);

			if (!ped)
				return;

			CNetwork::SendPacketToAll(ePacketType::PED_REMOVE, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);

			CNetworkPedManager::Instance().Remove(ped);
		}
	};

	struct PedOnFoot
	{
		uint16_t pedid = 0;
		CVector pos = CVector();
		CVector velocity = CVector();
		unsigned char health = 100;
		unsigned char armour = 0;
		unsigned char weapon = 0;
		unsigned short ammo = 0;
		float aimingRotation = 0.0f;
		float currentRotation = 0.0f;
		float lookDirection = 0.0f;
		unsigned char moveState = 0;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			if (!CNetworkPlayerManager::Instance().Get(peer)->m_bIsHost)
				return;

			CPackets::PedOnFoot* packet = (CPackets::PedOnFoot*)data;

			CNetworkPed* ped = CNetworkPedManager::Instance().Get(packet->pedid);

			if (ped)
			{
				ped->GetSyncData().m_vecPosition = packet->pos;
				CNetwork::SendPacketToAll(ePacketType::PED_ONFOOT, packet, sizeof * packet, ENET_PACKET_FLAG_UNSEQUENCED, peer);
			}
		}
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

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			if (!CNetworkPlayerManager::Instance().Get(peer)->m_bIsHost)
				return;

			CPackets::GameWeatherTime* packet = (CPackets::GameWeatherTime*)data;
			CNetwork::SendPacketToAll(ePacketType::GAME_WEATHER_TIME, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);
		}
	};

	struct PedRemoveTask
	{
		uint16_t pedid;
		int taskid; // eTaskType
	};

	struct PlayerKeySync
	{
		uint16_t playerid;
		—CompressedControllerState newState;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::PlayerKeySync* packet = (CPackets::PlayerKeySync*)data;
			packet->playerid = CNetworkPlayerManager::Instance().Get(peer)->GetId();
			CNetwork::SendPacketToAll(ePacketType::PLAYER_KEY_SYNC, packet, sizeof * packet, ENET_PACKET_FLAG_RELIABLE, peer);
		}
	};

	struct PedAddTask
	{
		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CNetwork::SendPacketToAll(ePacketType::PED_ADD_TASK, data, size, ENET_PACKET_FLAG_RELIABLE, peer);
		}
	};

	struct PedDriverUpdate
	{
		uint16_t pedid;
		uint16_t vehicleid;
		CVector pos;
		CVector rot;
		CVector roll;
		CVector velocity;
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
		unsigned char autoPilot[92];
		float gasPedal;
		float breakPedal;
		float steerAngle;

		static void Handle(ENetPeer* peer, void* data, int size)
		{
			CPackets::PedDriverUpdate* packet = (CPackets::PedDriverUpdate*)data;
			CNetwork::SendPacketToAll(ePacketType::PED_DRIVER_UPDATE, packet, sizeof * packet, ENET_PACKET_FLAG_UNSEQUENCED, peer);

			CNetworkVehicle* vehicle = CNetworkVehicleManager::Instance().Get(packet->vehicleid);

			if (vehicle == nullptr) // TODO: create vehicle
				return;

			auto& syncData = vehicle->GetSyncData();

			syncData.m_vecPosition = packet->pos;
			syncData.m_vecRotation = packet->rot;
		}
	};

	struct EntityStream
	{
		uint16_t m_nNetworkId;
		union
		{
			struct
			{
				eNetworkEntityType m_nEntityType : 3;
				unsigned char m_bIn : 1; // in == true, out == false
			};
		};
	};
};