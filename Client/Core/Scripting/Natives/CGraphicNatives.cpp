//========= IV: Network - https://github.com/Neproify/IV-Network ============
//
// File: CGraphicsNatives.cpp
// Project: Client.Core
// Authors: Neproify
// License: See LICENSE in root directory
//
//==============================================================================
#include "CGraphicNatives.h"
#include <CCore.h>
#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>

extern CCore * g_pCore;

int getScreenSize(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CScriptArguments args;
	args.push((int)g_pCore->GetGraphics()->GetGUI()->GetDisplayWidth());
	args.push((int)g_pCore->GetGraphics()->GetGUI()->GetDisplayHeight());

	pVM->PushArray(args);

	return 1;
}

int dxDrawText(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	CString strText;
	pVM->Pop(strText, "Default text");
	float fPositionX;
	pVM->Pop(fPositionX, 0);
	float fPositionY;
	pVM->Pop(fPositionY, 0);
	unsigned long ulColor;
	pVM->Pop(ulColor, 0xFFFFFFFF);
	float fScale;
	pVM->Pop(fScale, 1);
	bool bShadow;
	pVM->Pop(bShadow, true);

	g_pCore->GetGraphics()->DrawText(fPositionX, fPositionY, ulColor, fScale, DT_NOCLIP, bShadow, strText.C_String());

	pVM->Push(true);
	return 1;
}

void CGraphicNatives::Register(IScriptVM * pVM)
{
	pVM->RegisterFunction("getScreenSize", getScreenSize);
	pVM->RegisterFunction("dxDrawText", dxDrawText);
}