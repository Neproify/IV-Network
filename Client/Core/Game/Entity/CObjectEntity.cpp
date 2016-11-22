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

#include "CObjectEntity.h"
#include <Game/EFLC/CScript.h>

CObjectEntity::CObjectEntity(EFLC::CScript::eModel model, CVector3 vecPosition, CVector3 vecRotation) :
	CNetworkEntity(),
	m_model(model),
	m_vecPosition(vecPosition),
	m_vecRotation(vecRotation),
	m_object(NULL),
	m_bSpawned(false)
{
	CNetworkEntity::SetType(OBJECT_ENTITY);
}

CObjectEntity::~CObjectEntity()
{
	Destroy();
}

unsigned int CObjectEntity::GetHandle()
{
	return m_object;
}

bool CObjectEntity::Create()
{
	if (IsSpawned())
		Destroy();

	EFLC::CScript::CreateObjectNoOffset(m_model, m_vecPosition.fX, m_vecPosition.fY, m_vecPosition.fZ, &m_object, true);

	m_bSpawned = true;

	return true;
}

bool CObjectEntity::Destroy()
{
	if (!IsSpawned())
		return true;

	EFLC::CScript::DeleteObject(&m_object);

	return true;
}

bool CObjectEntity::IsSpawned()
{
	return m_bSpawned;
}

void CObjectEntity::SetPosition(CVector3 vecPosition)
{
	m_vecPosition = vecPosition;

	if (!IsSpawned())
		return;

	EFLC::CScript::SetObjectCoordinates(m_object, m_vecPosition.fX, m_vecPosition.fY, m_vecPosition.fZ);
}

void CObjectEntity::SetRotation(CVector3 vecRotation)
{
	m_vecRotation = vecRotation;

	if (!IsSpawned())
		return;

	EFLC::CScript::SetObjectRotation(m_object, m_vecRotation.fX, m_vecRotation.fY, m_vecRotation.fZ);
}

void CObjectEntity::SetModel(EFLC::CScript::eModel model)
{
	m_model = model;

	if (!IsSpawned())
		return;

	Destroy();
	Create();
}