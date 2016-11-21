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

#ifndef CObjectEntity_h
#define CObjectEntity_h

#include "CNetworkEntity.h"

class CScriptObject;

class CObjectEntity : public CNetworkEntity
{
private:
	CScriptObject * m_pScriptObject;
	unsigned int m_uiModel;
	CVector3 m_vecPosition;
	CVector3 m_vecRotation;
public:
	CObjectEntity();
	~CObjectEntity();

	bool Create() {return true;}
	bool Destroy() {return true;}

	void SetScriptObject(CScriptObject* pScriptObject) { m_pScriptObject = pScriptObject; }
	CScriptObject * GetScriptObject() { return m_pScriptObject; }

	void SetPosition(CVector3 vecPosition) { m_vecPosition = vecPosition; }
	void GetPosition(CVector3 &vecPosition) { vecPosition = m_vecPosition; }

	void SetRotation(CVector3 vecRotation) { m_vecRotation = vecRotation; }
	void GetRotation(CVector3 &vecRotation) { vecRotation = m_vecRotation; }

	void SetModel(unsigned int uiModel) { m_uiModel = uiModel; }
	unsigned int GetModel() { return m_uiModel; }
};

class CScriptObject : public CScriptEntity
{
private:
public:
	CScriptObject() {};
	~CScriptObject() {};

	CObjectEntity * GetEntity() { return (CObjectEntity*)CScriptEntity::GetEntity(); }

	const char * GetScriptClassName() { return "CObjectEntity"; }
};
#endif // CObjectEntity_h