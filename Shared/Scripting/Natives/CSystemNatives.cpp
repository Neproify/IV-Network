//========= IV: Network - https://github.com/Neproify/IV-Network ============
//
// File: CSystemNatives.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CSystemNatives.h"

#include <Scripting/CLuaVM.h>
#include <Scripting/CSquirrelVM.h>
#include <CLogFile.h>
#include <Scripting/ResourceSystem/CResourceManager.h>
#include <time.h>

void CSystemNatives::Register(IScriptVM * pVM)
{
	pVM->RegisterFunction("print", Print);
	pVM->RegisterFunction("log", Print);
	pVM->RegisterFunction("logf", Logf);
	pVM->RegisterFunction("date", Date);
	pVM->RegisterFunction("getTickCount", GetTickCount);
}

int CSystemNatives::Print(int * VM)
{
	// Just an example how the new scripting works with a lua or a squirrel vm its not needed to create a native for every language
	GET_SCRIPT_VM_SAFE;

	CString strPrint;
	pVM->ResetStackIndex();
	pVM->Pop(strPrint);
	CLogFile::Printf(strPrint);

	pVM->ResetStackIndex();

	return 1;
}

int CSystemNatives::Logf(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	CString strPrint;
	pVM->Pop(strPrint);
	CLogFile::PrintToFile(strPrint);

	pVM->ResetStackIndex();

	return 1;
}

int CSystemNatives::Date(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	CScriptArguments dateTable;

	time_t tTime;
	int iCustomTime = 0;
	CString strTimeType("l");

	if (pVM->GetArgumentCount() > 1)
	{
		pVM->Pop(strTimeType);
		if (pVM->GetArgumentCount() > 2)
			pVM->Pop(iCustomTime);
	}

	if (iCustomTime != 0)
		tTime = iCustomTime;
	else
		time(&tTime);

	tm *date;

	if(strTimeType.GetChar(0) == 'u')
		date = gmtime(&tTime);
	else
		date = localtime(&tTime);

	if(!date)
	{
		CLogFile::Print("Failed to get date");
		return 0;
	}
	
	dateTable.push("sec");
	dateTable.push(date->tm_sec);
	dateTable.push("min");
	dateTable.push(date->tm_min);
	dateTable.push("hour");
	dateTable.push(date->tm_hour);
	dateTable.push("day");
	dateTable.push(date->tm_mday);
	dateTable.push("mon");
	dateTable.push(date->tm_mon);
	dateTable.push("year");
	dateTable.push(date->tm_year + 1900);

	pVM->PushTable(dateTable);

	return 1;
}

int CSystemNatives::GetTickCount(int * VM)
{
	GET_SCRIPT_VM_SAFE;

	pVM->Push((int)SharedUtility::GetTime());

	pVM->ResetStackIndex();

	return 1;
}