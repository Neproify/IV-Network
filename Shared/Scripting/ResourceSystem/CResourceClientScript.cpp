//========= IV: Network - https://github.com/Neproify/IV-Network ============
//
// File: CResourceClientScript.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CResourceClientScript.h"
#include "CResource.h"
#include <Scripting/CEvents.h>


CResourceClientScript::CResourceClientScript(CResource * resource, const char * szShortName, const char * szResourceFileName)
	: CResourceScriptFile(resource, szShortName, szResourceFileName)
{
	m_type = RESOURCE_FILE_TYPE_CLIENT_SCRIPT;
}

CResourceClientScript::~CResourceClientScript()
{

}


bool CResourceClientScript::Start()
{
#ifdef _CLIENT
	if (m_resource->GetVM()->LoadScript(m_strShortName))
	{
		// Call the scripting event
		CScriptArguments args;
		args.push(m_strShortName.Get());
		CEvents::GetInstance()->Call("scriptLoaded", &args, CEventHandler::eEventType::NATIVE_EVENT, m_resource->GetVM());
		return true;
	}
#endif
	return true;
}

bool CResourceClientScript::Stop()
{
	
	return true;
}