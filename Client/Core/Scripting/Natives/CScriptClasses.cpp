//========= IV: Network - https://github.com/Neproify/IV-Network ============
//
// File: CScriptClasses.cpp
// Project: Client.Core
// Authors: xForce <xf0rc3.11@gmail.com>, g3o0or
// License: See LICENSE in root directory
//
//==============================================================================

#include "CScriptClasses.h"
#include <Game/EFLC/CScript.h>
#include <CCore.h>
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include "Scripting/Natives/Natives_Client.h"

extern CCore * g_pCore;

int SendMessage(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString sMessage;
	DWORD dwColor;
	bool bAllowFormatting;
	
	pVM->Pop(sMessage);
	pVM->Pop(dwColor);
	pVM->Pop(bAllowFormatting);
	
	g_pCore->GetGraphics()->GetChat()->Print(CString("#%x%s", dwColor, sMessage.C_String()));
	return 1;
}

int GetLocalPlayer(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	pVM->PushInstance("CPlayerEntity", g_pCore->GetGame()->GetLocalPlayer()->GetScriptPlayer());
	return 1;
}

int TriggerServerEvent(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString eventName;

	pVM->Pop(eventName);

	CScriptArguments args;
	for (int i = 3; i <= pVM->GetArgumentCount(); i++)
	{
		CScriptArgument arg;
		arg.pushFromStack(pVM, i);
		args.push(arg);
	}

	RakNet::BitStream bitStream;
	bitStream.Write(eventName);
	args.Serialize(&bitStream);
	g_pCore->GetNetworkManager()->Call(GET_RPC_CODEX(RPC_PLAYER_TRIGGER_EVENT), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, true);
	return 1;
}

void CScriptClasses::Register(IScriptVM * pVM)
{
	pVM->RegisterFunction("getLocalPlayer", GetLocalPlayer);
	pVM->RegisterFunction("sendMessage", SendMessage);
	pVM->RegisterFunction("triggerServerEvent", TriggerServerEvent);

	{ // ScriptPlayer
		static CScriptClass<CScriptPlayer>* pScriptPlayer = &(new CScriptClass<CScriptPlayer>("CPlayerEntity"))->
			//AddMethod("getPosition", &CScriptPlayer::GetPosition). // Synced
			AddMethod("getRotation", &CScriptPlayer::GetRotation). // Synced
			AddMethod("getMoveSpeed", &CScriptPlayer::GetMoveSpeed). // Synced
			AddMethod("getTurnSpeed", &CScriptPlayer::GetTurnSpeed). // Synced
			AddMethod("getArmour", &CScriptPlayer::GetArmour). // Synced
			AddMethod("getHealth", &CScriptPlayer::GetHealth). // Synced
			AddMethod("getHeading", &CScriptPlayer::GetHeading). // Synced
			//AddMethod("getModel", &CScriptPlayer::GetModel). // Synced
			//AddMethod("getDimension", &CScriptPlayer::GetDimension).
			//AddMethod("getName", &CScriptPlayer::GetName). // Synced
			AddMethod("getMoney", &CScriptPlayer::GetMoney). // Synced
			AddMethod("getWantedLevel", &CScriptPlayer::GetWantedLevel). // Synced
			AddMethod("getColor", &CScriptPlayer::GetColor). // Synced
			//AddMethod("sendMessage", &CScriptPlayer::SendPlayerMessage). // Synced
			AddMethod("getId", &CScriptPlayer::GetId). // Synced
			//AddMethod("setHudElementVisible", &CScriptPlayer::SetHudElementVisible). // Synced		
			//AddMethod("setClothes", &CScriptPlayer::SetClothes). // Synced	
			AddMethod("getClothes", &CScriptPlayer::GetClothes). // Synced	
			AddMethod("isOnFoot", &CScriptPlayer::IsOnFoot).
			//AddMethod("getVehicle", &CScriptPlayer::GetVehicle).
			AddMethod("getVehicleSeat", &CScriptPlayer::GetVehicleSeat);
		(pScriptPlayer)->Register(pVM);
	}
}
