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
#include "..\EFLC\ScriptEnums.h"

class CObjectEntity : public CNetworkEntity
{
private:
	EntityId m_objectId;
	CVector3 m_vecPosition;
	CVector3 m_vecRotation;
	unsigned int m_object;
	EFLC::CScript::eModel m_model;
	bool m_bSpawned;
public:
	CObjectEntity(EFLC::CScript::eModel model, CVector3 vecPosition, CVector3 vecRotation);
	~CObjectEntity();

	unsigned int GetHandle();

	bool Create();
	bool Destroy();

	bool IsSpawned();

	void SetId(EntityId objectId) { m_objectId = objectId; }
	EntityId GetId() { return m_objectId; }

	void SetPosition(CVector3 vecPosition);
	void GetPosition(CVector3 &vecPosition) { vecPosition = m_vecPosition; }

	void SetRotation(CVector3 vecRotation);
	void GetRotation(CVector3 &vecRotation) { vecRotation = m_vecRotation; }

	void SetModel(EFLC::CScript::eModel model);
	void GetModel(EFLC::CScript::eModel &model) { model = m_model; }
};

#endif // CObjectEntity_h