#pragma once
#define MAX_SERVER_PLAYERS 4
#define MAX_SERVER_VEHICLES 200
#define MAX_SERVER_PEDS 300
#define RENDER_FONT_SIZE 12
#define _DEV
#define PURECALL (0x82263A)
#define STREAM_DISTANCE (100.0f) // todo

// networking ------------------------------------------------------------------------------

#include "enet/enet.h"

// windows ---------------------------------------------------------------------------------

#include <Windows.h>

// plugin-sdk ------------------------------------------------------------------------------

#include "plugin.h"
#include "Patch.h"
#include "CPlayerPed.h"
#include "CStreaming.h"
#include "CWorld.h"
#include "RenderWare.h"
#include "d3dx9.h"
#include "extensions/ScriptCommands.h"
#include "CTaskSimpleDuckToggle.h"
#include "CTaskSimplePlayerOnFoot.h"
#include "CRadar.h"
#include "CText.h"
#include "CCamera.h"
#include "CBulletTraces.h"
#include "CDraw.h"
#include "CMenuManager.h"
#include "CSprite.h"
#include "CFont.h"
#include "CHud.h"
#include "CModelInfo.h"
#include "CTxdStore.h"
#include "CKeyGen.h"
#include "CAnimManager.h"
#include "CMessages.h"
#include "CExplosion.h"
#include "CMonsterTruck.h"
#include "CQuadBike.h"
#include "CHeli.h"
#include "CPlane.h"
#include "CBmx.h"
#include "CTrailer.h"
#include "CTrain.h"
#include "CBoat.h"
#include "CTaskComplexEnterCarAsDriver.h"
#include "CTaskComplexLeaveCar.h"
#include "CCarCtrl.h"
#include "CCheat.h"
#include "CEmergencyPed.h"
#include "CCivilianPed.h"
#include "CTaskComplexWanderStandard.h"
#include "CTheScripts.h"
#include "CTaskSimpleGangDriveBy.h"
#include "CLoadingScreen.h"
#include "CPopulation.h"
#include "CWeather.h"
#include "CClock.h"
// classes ---------------------------------------------------------------------------------

using namespace plugin;

#include "CCore.h"
#include "structs.h"
#include "CPackets.h"
#include "CPacketHandler.h"
#include "CNetwork.h"
#include "CUtil.h"
#include "CPatch.h"
#include "Hooks/CHook.h"
#include "Events.h"
#include "CLocalPlayer.h"
#include "CNetworkPlayerMapPin.h"
#include "CNetworkPlayerWaypoint.h"
#include "CLaunchManager.h"
#include "CNetworkPlayerNameTag.h"
#include "CChat.h"
#include "CDebugVehicleSpawner.h"
#include "CPassengerEnter.h"
#include "CDriveBy.h"
#include "CDebugPedTasks.h"
// -----------------------------------------------------------------------------------------
