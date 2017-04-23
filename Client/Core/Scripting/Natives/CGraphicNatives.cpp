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

int dxDrawBox(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	float fLeft;
	pVM->Pop(fLeft, 0);
	float fTop;
	pVM->Pop(fTop, 0);
	float fWidth;
	pVM->Pop(fWidth, 50);
	float fHeight;
	pVM->Pop(fHeight, 50);
	unsigned long ulBoxColor;
	pVM->Pop(ulBoxColor, 0xFFFFFFFF);

	g_pCore->GetGraphics()->DrawBox(fLeft, fTop, fWidth, fHeight, ulBoxColor);

	pVM->Push(true);
	return 1;
}

int dxDrawLine(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->ResetStackIndex();

	float fLeft;
	pVM->Pop(fLeft, 0);
	float fTop;
	pVM->Pop(fTop, 0);
	float fRight;
	pVM->Pop(fRight, 50);
	float fBottom;
	pVM->Pop(fBottom, 50);
	float fWidth;
	pVM->Pop(fWidth, 1);
	unsigned long ulColor;
	pVM->Pop(ulColor, 0xFFFFFFFF);

	g_pCore->GetGraphics()->DrawLine(fLeft, fTop, fRight, fBottom, fWidth, ulColor);

	pVM->Push(true);
	return 1;
}

void CGraphicNatives::Register(IScriptVM * pVM)
{
	pVM->RegisterFunction("getScreenSize", getScreenSize);
	pVM->RegisterFunction("dxDrawText", dxDrawText);
	pVM->RegisterFunction("dxDrawBox", dxDrawBox);
	pVM->RegisterFunction("dxDrawLine", dxDrawLine);
}