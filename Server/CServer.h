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

#ifndef CServer_h
#define CServer_h

#include <limits.h>
#ifndef UINT_MAX
#define UINT_MAX 4294967295
#endif
#include "Common.h"

#include <Scripting/ResourceSystem/CResourceManager.h>

#include <Entity/CEntityManager.h>
#include <Entity/Entities.h>
#include "Network/CNetworkModule.h"
#include "CTimerManager.h"

typedef CEntityManager<CPlayerEntity, MAX_PLAYERS> CPlayerManager;
typedef CEntityManager<CVehicleEntity, MAX_VEHICLES> CVehicleManager;
typedef CEntityManager<CObjectEntity, MAX_OBJECTS> CObjectManager;
typedef CEntityManager<CPickupEntity, MAX_PICKUPS> CPickupManager;
typedef CEntityManager<CBlipEntity, MAX_BLIPS> CBlipManager;
typedef CEntityManager<CCheckpointEntity, MAX_CHECKPOINTS> CCheckpointManager;

class CServer {

private:
	static CServer				* s_pInstance;

	CResourceManager			* m_pResourceManager;

	CPlayerManager				* m_pPlayerManager;
	CVehicleManager				* m_pVehicleManager;
	CObjectManager				* m_pObjectManager;
	CPickupManager				* m_pPickupManager;
	CBlipManager				* m_pBlipManager;
	CCheckpointManager			* m_pCheckpointManager;

	CTimerManager				* m_pTimerManager;

	CNetworkModule				* m_pNetworkModule;


	unsigned int                m_uiSyncRate = 10; /** Describes the maximum number of sync packages sent per second per entity */
    unsigned int                m_uiMaximumFPS = 100;

	bool                        m_bShowFPS = true;
	unsigned long				m_ulLastFPSUpdateTime;
	unsigned long				m_ulFrameCount;
	unsigned long				m_ulFramesPerSecond;

	unsigned long				m_ulStartupTime;
public:
	CServer();
	~CServer();

	static CServer* GetInstance() { return s_pInstance; }

	bool	Startup();
	void	Process();
	void	Shutdown();

	CResourceManager	*GetResourceManager() { return CResourceManager::GetInstance(); }

	CPlayerManager		*GetPlayerManager() { return m_pPlayerManager; }
	CVehicleManager		*GetVehicleManager() { return m_pVehicleManager; }
	CObjectManager		*GetObjectManager() { return m_pObjectManager; }
	CPickupManager		*GetPickupManager() { return m_pPickupManager; }
	CBlipManager		*GetBlipManager() { return m_pBlipManager; }
	CCheckpointManager	*GetCheckpointManager() { return m_pCheckpointManager; }

	CTimerManager		*GetTimerManager() { return m_pTimerManager; }

	CNetworkModule		*GetNetworkModule() { return m_pNetworkModule; }

	unsigned GetSyncRate() { return m_uiSyncRate; }
	void	 SetSyncRate(unsigned int uiSyncRate = 10) { m_uiSyncRate = uiSyncRate; }

	unsigned int GetMaximumFPS() { return m_uiMaximumFPS; }
	void		 SetMaximumFPS(unsigned int uiMaximumFPS = 100) { m_uiMaximumFPS = uiMaximumFPS; }

	unsigned long GetStartupTime() { return m_ulStartupTime; }
};

#endif // CServer_h