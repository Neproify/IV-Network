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

#ifndef CEvents_h
#define CEvents_h

#include <Common.h>
#include <map>
#include "IScriptVM.h"
#include "CEventHandler.h"

class CEvents {

private:
	static CEvents* s_pInstance;

	std::map<CString, std::list<CEventHandler*>> m_Events;
public:
	CEvents()
	{
		s_pInstance = this;
	}
	~CEvents();
	
	static CEvents* GetInstance() { return s_pInstance; }

	bool Add(CString strName, CEventHandler* pEventHandler);

	bool Remove(CString strName, CEventHandler* pEventHandler);
	bool RemoveEventsCreatedByResource(CResource* pResource);

	bool RemoveScript(IScriptVM* pVM);
	bool IsEventRegistered(CString eventName);

	void Clear();

	CScriptArguments Call(CString strName, CScriptArguments* pArguments, CEventHandler::eEventType EventType, IScriptVM * pVM);
};

#endif // CEvents_h