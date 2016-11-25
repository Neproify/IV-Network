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
#include "CServer.h"

CObjectEntity::CObjectEntity()
{

}

CObjectEntity::~CObjectEntity()
{

}

void CScriptObject::SetPosition(float fX, float fY, float fZ)
{
	CVector3 vecPosition = CVector3(fX, fY, fZ);

	GetEntity()->SetPosition(vecPosition);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(vecPosition);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_OBJECT_SET_POSITION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptObject::SetRotation(float fX, float fY, float fZ)
{
	CVector3 vecRotation = CVector3(fX, fY, fZ);

	GetEntity()->SetRotation(vecRotation);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(vecRotation);
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_OBJECT_SET_ROTATION), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}

void CScriptObject::SetModel(unsigned int uiModel)
{
	GetEntity()->SetModel(uiModel);

	RakNet::BitStream bitStream;
	bitStream.Write(GetEntity()->GetId());
	bitStream.Write(GetEntity()->GetModel());
	CServer::GetInstance()->GetNetworkModule()->Call(GET_RPC_CODEX(RPC_OBJECT_SET_MODEL), &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, -1, true);
}