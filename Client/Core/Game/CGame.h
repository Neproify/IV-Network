/*
* Copyright (C) GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CGame_h
#define CGame_h

#include <Common.h>

#include <Network/CLocalPlayer.h>

#include <Game/Entity/CEntityManager.h>
#include <Game/Entity/CNetworkEntity.h>

#include <Game/Entity/CPlayerEntity.h>
#include <Game/Entity/CVehicleEntity.h>
#include <Game/Entity/CObjectEntity.h>
#include <Game/Entity/CPickupEntity.h>
#include <Game/Entity/CBlipEntity.h>
#include <Game/Entity/CCheckpointEntity.h>

#include <Game/EFLC/CModelInfo.h>
#include <Game/EFLC/CPad.h>
#include <Game/EFLC/CPool.h>
#include <Game/EFLC/CCam.h>
#include <Game/EFLC/CWeaponInfo.h>

#include <Game\EFLC\CPool.h>
#include <Game\EFLC\CCam.h>
#include <Game\EFLC\CVehicle.h>
#include <Game\EFLC\CPed.h>
#include <Game\EFLC\CPlayerInfo.h>
#include <Game\EFLC\CPlayerPed.h>

#include "CTaskManager.h"
#include "CPools.h"
#include "CCamera.h"
#include "CGameFuncs.h"
#include "CCharacterManager.h"
#include "CContextSwitch.h"
#include <Game/CTrafficLights.h>
#include <Game/CTrafficHandler.h>

typedef CEntityManager<CPlayerEntity, MAX_PLAYERS> CPlayerManager;
typedef CEntityManager<CVehicleEntity, MAX_VEHICLES> CVehicleManager;
typedef CEntityManager<CObjectEntity, MAX_OBJECTS> CObjectManager;
typedef CEntityManager<CPickupEntity, MAX_PICKUPS> CPickupManager;
typedef CEntityManager<CBlipEntity, MAX_BLIPS> CBlipManager;
typedef CEntityManager<CCheckpointEntity, MAX_CHECKPOINTS> CCheckpointManager;

class CLocalPlayer;
class CPools;
class CGame
{
private:
	CLocalPlayer					* m_pLocalPlayer = nullptr;
	EFLC::CPad							* m_pPad = nullptr;
	CTaskManager					* m_pTaskManager = nullptr;
	CPools							* m_pPool = nullptr;
	CCamera							* m_pCamera = nullptr;
	EFLC::CModelInfo					m_modelInfos[NUM_ModelInfos];
	EFLC::CWeaponInfo					m_weaponInfos[NUM_WeaponInfos];

	CPlayerManager					* m_pPlayerManager = nullptr;
	CVehicleManager					* m_pVehicleManager = nullptr;
	CObjectManager					* m_pObjectManager = nullptr;
	CPickupManager					* m_pPickupManager = nullptr;
	CBlipManager					* m_pBlipManager = nullptr;
	CCheckpointManager				* m_pCheckpointManager = nullptr;
	CTrafficLights					* m_pTrafficLights = nullptr;

	HWND							m_hwndGameWindow;
	bool							m_bFocused;

public:
										CGame();
										~CGame();

	void								Initialize();
	void								Setup();
	void								Process();
	void								UnprotectMemory();
	void								Reset();

	EFLC::CModelInfo						* GetModelInfo(int iModelIndex);
	EFLC::CWeaponInfo						* GetWeaponInfo(EFLC::eWeaponType weaponType);

	const decltype(m_pLocalPlayer)        GetLocalPlayer() { return m_pLocalPlayer; }
	const decltype(m_pPad)                GetPad() { return m_pPad; }
	const decltype(m_pTaskManager)        GetTaskManager() { return m_pTaskManager; }
	const decltype(m_pPool)               GetPools() { return m_pPool; }
	const decltype(m_pCamera)             GetCamera() { return m_pCamera; }
	const decltype(m_pPlayerManager)      GetPlayerManager() { return m_pPlayerManager; }
	const decltype(m_pVehicleManager)     GetVehicleManager() { return m_pVehicleManager; }
	const decltype(m_pObjectManager)      GetObjectManager() { return m_pObjectManager; }
	const decltype(m_pPickupManager)      GetPickupManager() { return m_pPickupManager; }
	const decltype(m_pBlipManager)        GetBlipManager() { return m_pBlipManager; }
	const decltype(m_pCheckpointManager)  GetCheckpointManager() { return m_pCheckpointManager; }
	const decltype(m_pTrafficLights)      GetTrafficLights() { return m_pTrafficLights; }

	inline void						SetFocused(bool bFocus) { m_bFocused = bFocus; }
	bool							IsFocused() { return m_bFocused; }

	HWND								GetGameWindow();
	void								ThrowInternalException(DWORD dwAddress, DWORD dwExcetionType);
};

#endif // CGame_h