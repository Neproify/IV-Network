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

#include "CClientCommands.h"

#include <Game/EFLC/CModelManager.h>
#include <Ptrs.h>

bool CClientCommands::HandleUserInput(CString strCommand, CString strParameters)
{
	if(strCommand == "q"  || strCommand == "quit")
	{
		// Are we connected to the network?
		if(g_pCore->GetNetworkManager()->IsConnected())
		{
			// Disconnect and shutdown RakNet
			g_pCore->GetNetworkManager()->Shutdown(500, true);
		}
		
		TerminateProcess(GetCurrentProcess(), 0);
		return true;
	}
	else if(strCommand == "qq" || strCommand == "quickquit")
	{
		TerminateProcess(GetCurrentProcess(), 0);
		return true;
	}
	else if (strCommand == "saveposition" || strCommand == "save")
	{
		FILE * file = fopen(SharedUtility::GetAbsolutePath("multiplayer//SavePositions.log"), "a");
		if (!file)
		{
			g_pCore->GetGraphics()->GetChat()->Print("Failed to open 'SavePositions.log'");
			return true;
		}

		CVector3 vecPosition;

		// Get our local player
		CLocalPlayer * pLocalPlayer = g_pCore->GetGame()->GetLocalPlayer();

		if (pLocalPlayer->IsInVehicle())
		{
			CVehicleEntity * pVehicle = pLocalPlayer->GetVehicle();

			if (pVehicle)
			{
				pVehicle->GetPosition(vecPosition);
				CVector3 vecRotation;
				pVehicle->GetRotation(vecRotation);
				DWORD dwColors[5];
				pVehicle->GetColors(dwColors[0], dwColors[1], dwColors[2], dwColors[3], dwColors[4]);
				fprintf_s(file, "createVehicle(%d, %f, %f, %f, %f, %f, %f, %d, %d, %d, %d, %d);%s%s\n", EFLC::CModelManager::ModelHashToVehicleId(pVehicle->GetModelInfo()->GetHash()), vecPosition.fX, vecPosition.fY, vecPosition.fZ, vecRotation.fX, vecRotation.fY, vecRotation.fZ, dwColors[0], dwColors[1], dwColors[2], dwColors[3], dwColors[4], strParameters.GetLength() > 0 ? " // " : "", strParameters.GetLength() > 0 ? strParameters.Get() : "");
			}
		}
		else
		{
			pLocalPlayer->GetPosition(vecPosition);
			int iModelId = pLocalPlayer->GetPlayerPed()->GetModelIndex();
			fprintf_s(file, "PlayerData(%d, %f, %f, %f, %f);%s%s\n", iModelId, vecPosition.fX, vecPosition.fY, vecPosition.fZ, pLocalPlayer->GetHeading(), strParameters.GetLength() > 0 ? " // " : "", strParameters.GetLength() > 0 ? strParameters.Get() : "");
		}

		fclose(file);
		g_pCore->GetGraphics()->GetChat()->Print("Position data saved to 'SavePositions.log'");
		return true;
	}
	return false;
}