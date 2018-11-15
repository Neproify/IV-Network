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

#include "CVehicleEntity.h"
#include "CPlayerEntity.h"

#include <Game/EFLC/CModelManager.h>
#include <Game/EFLC/CVehicleFactory.h>
#include <Game/Entity/CVehicleEntity.h>
#include <Game/EFLC/CScript.h>
#include <Game/CCharacterManager.h>

#include <CCore.h>
extern CCore * g_pCore;

CVehicleEntity::CVehicleEntity(int iVehicleModel, CVector3 vecPos, float fAngle, DWORD color1, DWORD color2, DWORD color3, DWORD color4, DWORD color5) :
	CNetworkEntity(VEHICLE_ENTITY)
{
	m_pVehicle = NULL;
	m_vehicleId = INVALID_ENTITY_ID;
	m_pDriver = NULL;
	m_bSpawned = false;
	m_pModelInfo = NULL;

	if (iVehicleModel == 124 || iVehicleModel == 125 || iVehicleModel == 126)
	{
		g_pCore->GetGraphics()->GetChat()->Print(CString("!!! This vehicle is disabled, because makes big FPS drop and invisible (%i) !!!", iVehicleModel).Get());
		return;
	}

	if (iVehicleModel == 157 || iVehicleModel == 158 || iVehicleModel == 159)
	{
		g_pCore->GetGraphics()->GetChat()->Print(CString("!!! This vehicle is disabled, because makes crash we will fix it (%i) (disabled boat in TBoGT) !!!", iVehicleModel).Get());
		return;
	}

	// Get the model hash from the model id
	DWORD dwModelHash = EFLC::CModelManager::VehicleIdToModelHash(iVehicleModel);

	// Get the model index
	int iVehicleModelIndex = EFLC::CModelManager::GetModelIndexFromHash(dwModelHash);

	if (iVehicleModelIndex == -1)
	{
		g_pCore->GetGraphics()->GetChat()->Print(CString("!!! 0x%X ModelHash has no model index !!!", dwModelHash).Get());
		return;
	}

	// Set the model info
	m_pModelInfo = g_pCore->GetGame()->GetModelInfo(iVehicleModelIndex);

	// Set the color
	m_dwColor[0] = color1;
	m_dwColor[1] = color2;
	m_dwColor[2] = color3;
	m_dwColor[3] = color4;
	m_dwColor[4] = color5;

	// Set the interpolate variables
	m_interp.pos.ulFinishTime = 0;
	m_interp.rot.ulFinishTime = 0;

	// Set the rotation
	m_fSpawnAngle = fAngle;

	m_lastVehicleSyncPacket.matrix.vecPosition = CVector3();

	// Set the spawn position
	memcpy(&m_vecSpawnPosition, &vecPos, sizeof(CVector3));

}

CVehicleEntity::~CVehicleEntity()
{
	// Is the vehicle spawned?
	if(IsSpawned())
	{
		// Destroy the vehicle
		Destroy();
	}
}

#define CVehicleModelInfo__AddReference ((int(__thiscall *)(EFLC::IBaseModelInfo *))(g_pCore->GetBase() + 0x83F2E0))
#define CWorld__GetGroundZ ((float (__cdecl*)(float, float))(g_pCore->GetBase() + 0x9C69F0))
#define CWorld__AddEntity ((int(_cdecl *)(EFLC::IVehicle*, bool bDontAdd))(g_pCore->GetBase() + 0x86C0B0))
#define CVehicle__TurnEngineOn ((void(__thiscall *)(EFLC::IVehicle*, bool))(g_pCore->GetBase() + 0x9FD530))
#define sub_B40B30 ((void(__thiscall *)(EFLC::IVehicle*, char, char))(g_pCore->GetBase() + 0xB40B30))
#define pIVehicleFactory (*(EFLC::IVehicleFactory**)(g_pCore->GetBase() + 0x118A6D4))

bool CVehicleEntity::Create()
{
	if (!m_pModelInfo)
		return false;

	// Is the vehicle already spawned?
	if(IsSpawned())
		return false;

	m_pModelInfo->AddReference(true);

	DWORD dwModelHash = m_pModelInfo->GetHash();

	unsigned int uiVehicleHandle;

	EFLC::CScript::CreateCar(dwModelHash, 0.0f, 0.0f, 0.0f, &uiVehicleHandle, true);

	EFLC::IVehicle * pVehicle = g_pCore->GetGame()->GetPools()->GetVehiclePool()->AtHandle(uiVehicleHandle);

	m_pVehicle = new EFLC::CVehicle(pVehicle);

	//set the vehicle's color
	SetColors(m_dwColor[0], m_dwColor[1], m_dwColor[2], m_dwColor[3], m_dwColor[4]);

	//fix: no more random components
	for (int i = 0; i < 9; ++i)
		SetComponentState(i, false);

	// Mark as spawned
	m_bSpawned = true;

	// Reset the vehicle
	Reset();

	SetPosition(m_vecSpawnPosition);

	CLogFile::Printf("Created vehicle! (Id: %d, Handle: %X)", m_vehicleId, g_pCore->GetGame()->GetPools()->GetVehiclePool()->HandleOf(pVehicle));

	return true;
}

bool CVehicleEntity::Destroy()
{
	// Is the vehicle not spawned?
	if(!IsSpawned())
		return false;

	// Remove driver and passengers
	if (m_pDriver)
	{
		m_pDriver->RemoveFromVehicle();
		SetDriver(nullptr);
	}

	for (auto pPassenger : m_pPassengers)
	{
		if (pPassenger)
		{
			pPassenger->RemoveFromVehicle();
		}
	}

	unsigned int handle = g_pCore->GetGame()->GetPools()->GetVehiclePool()->HandleOf(m_pVehicle->GetVehicle());
	EFLC::CScript::MarkCarAsNoLongerNeeded(&handle);
	pIVehicleFactory->Delete(m_pVehicle->GetVehicle());

	// Remove the vehicle model reference
	m_pModelInfo->RemoveReference();

	// Delete the vehicle instance
	SAFE_DELETE(m_pVehicle);

	// Mark as not spawned
	m_bSpawned = false;

	return true;
}

void CVehicleEntity::Reset()
{
	// Check vehicle iv ptr
	if(!m_pVehicle)
		return;

	// Turn the engine off
	SetEngineState(false);
	
	// Reset Indicators
	SetIndicatorState(false,false,false,false);

	// Disable damage
	//m_pVehicle->SetCarCanBeDamaged(false);
	//m_pVehicle->SetCanBeVisiblyDamaged(false);

}

bool CVehicleEntity::IsMoving()
{
    CVector3 vecMoveSpeed;
    GetMoveSpeed(vecMoveSpeed);

    if(!vecMoveSpeed.IsEmpty())
		return true;

    return false;
}

void CVehicleEntity::StopMoving()
{
	SetMoveSpeed(CVector3());
}

void CVehicleEntity::SoundHorn(int iDuration)
{
    if(IsSpawned())
		m_pVehicle->SoundHorn(iDuration);
}

unsigned int CVehicleEntity::GetScriptingHandle()
{
	if(IsSpawned())
		return g_pCore->GetGame()->GetPools()->GetVehiclePool()->HandleOf(m_pVehicle->GetVehicle());

	return 0;
}

void CVehicleEntity::SetModel(DWORD dwModelHash)
{
	// Get the model index from the model hash
	int iModelIndex = CCharacterManager::ModelHashToVehicleId(dwModelHash);

	// Do we have an invalid model index?
	if(iModelIndex == -1)
	{
		CLogFile::Printf("CClientVehicle::SetModel Failed (Invalid model hash)!");
		return;
	}

	// Has the model not changed?
	if(m_pModelInfo->GetIndex() == iModelIndex)
	{
		CLogFile::Printf("CClientVehicle::SetModel Failed (Model change not needed)!");
		return;
	}

	// Get the new model info
	auto pNewModelInfo = g_pCore->GetGame()->GetModelInfo(iModelIndex);

	// Is the new model info valid?
	if(!pNewModelInfo || !pNewModelInfo->IsValid() || !pNewModelInfo->IsVehicle())
	{
		CLogFile::Printf("CClientVehicle::SetModel Failed (Invalid model)!");
		return;
	}

	if(IsSpawned())
	{
		// Stream ourselves out
		CLogFile::Printf("CClientVehicle::SetModel Stream Out Begin");
		Destroy();
		CLogFile::Printf("CClientVehicle::SetModel Stream Out Complete");
	}

	// Set the new model info
	m_pModelInfo = pNewModelInfo;

	// Stream ourselves back in
	CLogFile::Printf("CClientVehicle::SetModel Stream In Begin");
	Create();
	CLogFile::Printf("CClientVehicle::SetModel Stream In Complete");
}

#pragma pack(push, 1)
class ColorStuff
{
public:
	float red;
	float green;
	float blue;
	DWORD color;
};

class IVehicleColors
{
public:
	unsigned char pad_0[16];
	ColorStuff field_10;
	ColorStuff field_20;
	ColorStuff field_30;
	ColorStuff field_40;
	ColorStuff field_50;
	ColorStuff field_60;
};

#pragma pack(pop)

#define getRed(color) (float) ((color >> 16) & 0xFF) / 255.0
#define getGreen(color) (float) ((color >> 8) & 0xFF) / 255.0
#define getBlue(color) (float) (color & 0xFF) / 255.0

void CVehicleEntity::SetColors(DWORD dwColor1, DWORD dwColor2, DWORD dwColor3, DWORD dwColor4, DWORD dwColor5)
{
	if (!GetGameVehicle())
		return;

	IVehicleColors* VehicleColors = *(IVehicleColors**) (GetGameVehicle()->GetVehicle()->m_pLivery + 4);

	VehicleColors->field_10.red = getRed(dwColor1);
	VehicleColors->field_10.green = getGreen(dwColor1);
	VehicleColors->field_10.blue = getBlue(dwColor1);
	VehicleColors->field_10.color = dwColor4;

	VehicleColors->field_20.red = getRed(dwColor2);
	VehicleColors->field_20.green = getGreen(dwColor2);
	VehicleColors->field_20.blue = getBlue(dwColor2);
	VehicleColors->field_20.color = dwColor4;

	VehicleColors->field_30.red = getRed(dwColor3);
	VehicleColors->field_30.green = getGreen(dwColor3);
	VehicleColors->field_30.blue = getBlue(dwColor3);
	VehicleColors->field_30.color = dwColor4;

	VehicleColors->field_40.red = getRed(dwColor4);
	VehicleColors->field_40.green = getGreen(dwColor4);
	VehicleColors->field_40.blue = getBlue(dwColor4);
	VehicleColors->field_40.color = dwColor4;

	VehicleColors->field_50.red = getRed(dwColor5);
	VehicleColors->field_50.green = getGreen(dwColor5);
	VehicleColors->field_50.blue = getBlue(dwColor5);
	VehicleColors->field_50.color = dwColor4;

	VehicleColors->field_60.red = getRed(dwColor3);
	VehicleColors->field_60.green = getGreen(dwColor3);
	VehicleColors->field_60.blue = getBlue(dwColor3);
	VehicleColors->field_60.color = dwColor4;
}

void CVehicleEntity::GetColors(DWORD &dwColor1, DWORD &dwColor2, DWORD &dwColor3, DWORD &dwColor4, DWORD &dwColor5)
{
	{
		dwColor1 = m_dwColor[0];
		dwColor2 = m_dwColor[1];
		dwColor3 = m_dwColor[2];
		dwColor4 = m_dwColor[3];
		dwColor5 = m_dwColor[4];
	}
}


#define sub_9D92E0 ((int(__thiscall *)(EFLC::IVehicle*))((dwsub_9D92E0)))
#define sub_9FFFC0 ((int( __thiscall *)(EFLC::IVehicle*, char))(g_pCore->GetBase() + 0x9FFFC0))
#define sub_5C9D60 ((int( __thiscall *)(void*, char))(g_pCore->GetBase() + 0x5C9D60))

void CVehicleEntity::SetPosition(const CVector3& vecPosition, bool bDontCancelTasks, bool bResetInterpolation)
{
	if (IsSpawned())
	{
		if (!bDontCancelTasks)
		{
			EFLC::CScript::SetCarCoordinatesNoOffset(GetScriptingHandle(), vecPosition.fX, vecPosition.fY, vecPosition.fZ);
			g_pCore->GetGraphics()->GetChat()->Print("!bDontCancelTasks");
		}
		else
		{
			m_pVehicle->RemoveFromWorld();
			// Set the position in the matrix
			m_pVehicle->SetPosition(vecPosition);
			m_pVehicle->AddToWorld();
		}

		m_vecPosition = vecPosition;

		// Reset interpolation if requested
		if (bResetInterpolation)
			RemoveTargetPosition();

		return;

		//
		Vector4 coords(vecPosition.fX, vecPosition.fY, vecPosition.fZ, 0);
		m_pVehicle->GetVehicle()->SetCoordinates(&coords, 1, 0);
		m_pVehicle->GetVehicle()->UpdatePhysicsMatrix(true);
		m_pVehicle->GetVehicle()->Function100();
		
		DWORD dwsub_9D92E0 = g_pCore->GetBase() + 0x9D92E0;

		if (sub_9D92E0(m_pVehicle->GetVehicle()))
		{
			int v8 = sub_9D92E0(m_pVehicle->GetVehicle());
			(*(void(__thiscall **)(int))(*(DWORD *)v8 + 16))(v8);
			if (*(DWORD *)(sub_9D92E0(m_pVehicle->GetVehicle()) + 24))
			{
				int v9 = sub_9D92E0(m_pVehicle->GetVehicle());
				sub_5C9D60(*(void **)(v9 + 24), 1);
			}
		}

		sub_9FFFC0(m_pVehicle->GetVehicle(), 1);
	}

	m_vecPosition = vecPosition;

	// Reset interpolation if requested
	if (bResetInterpolation)
		RemoveTargetPosition();
}

void CVehicleEntity::GetPosition(CVector3& vecPosition)
{
	if(IsSpawned())
		m_pVehicle->GetPosition(vecPosition);
	else
		vecPosition = m_vecPosition;
}

CVector3 CVehicleEntity::GetPosition()
{
	CVector3 vecPosition;

	if(IsSpawned())
		m_pVehicle->GetPosition(vecPosition);
	else
		vecPosition = m_vecPosition;

	return vecPosition;
}

void CVehicleEntity::SetRotation(const CVector3& vecRotation, bool bResetInterpolation)
{
	if(IsSpawned())
	{
		// Get the vehicle matrix
		Matrix matMatrix;
		m_pVehicle->GetMatrix(matMatrix);

		// Convert the rotation from degrees to radians
		CVector3 vecNewRotation = Math::ConvertDegreesToRadians(vecRotation);

		// Apply the rotation to the vehicle matrix
		CGameFunction::ConvertEulerAnglesToRotationMatrix(vecNewRotation, matMatrix);

		// Set the new vehicle matrix
		m_pVehicle->SetMatrix(matMatrix);
	}

	m_vecRotation = vecRotation;

	// Reset interpolation if requested
	if(bResetInterpolation)
		RemoveTargetRotation();
}

void CVehicleEntity::GetRotation(CVector3& vecRotation)
{
	if(IsSpawned())
	{
		// Get the vehicle matrix
		Matrix matMatrix;
		m_pVehicle->GetMatrix(matMatrix);

		// Convert the matrix to euler angles
		CVector3 vecNewRotation;
		CGameFunction::ConvertRotationMatrixToEulerAngles(matMatrix, vecNewRotation);

		// Flip the rotation
		vecNewRotation.fX = ((2 * PI) - vecNewRotation.fX);
		vecNewRotation.fY = ((2 * PI) - vecNewRotation.fY);
		vecNewRotation.fZ = ((2 * PI) - vecNewRotation.fZ);

		// Convert the rotation from radians to degrees
		vecRotation = Math::ConvertRadiansToDegrees(vecNewRotation);
	}
	else
		vecRotation = m_vecRotation;
}

void CVehicleEntity::SetHealth(float uiHealth)
	{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetEngineHealth(uiHealth);

	m_uiHealth = uiHealth;
}

float CVehicleEntity::GetHealth()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetEngineHealth();

	return m_uiHealth;
}

void CVehicleEntity::SetPetrolTankHealth(float fHealth)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetPetrolTankHealth((float)fHealth);

	m_fPetrolTankHealth = fHealth;
}

float CVehicleEntity::GetPetrolTankHealth()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetPetrolTankHealth();

	return m_fPetrolTankHealth;
}

void CVehicleEntity::SetQuaternion(float * quat)
{
	assert(quat);

	if (IsSpawned())
	{
		Matrix34 mat = *m_pVehicle->GetVehicle()->m_pMatrix;
		((int(__thiscall*)(Matrix34 *, float *))(g_pCore->GetBase() + 0x462F30))(&mat, quat);
		m_pVehicle->GetVehicle()->SetMatrix(&mat, 0, 0);
		((void(__thiscall*)(EFLC::IVehicle *))(g_pCore->GetBase() + 0x9D3700))(m_pVehicle->GetVehicle());
	}
}

void CVehicleEntity::GetQuaternion(float * quat)
{
	assert(quat);

	if (IsSpawned())
	{
		((Matrix34 *(__thiscall *)(float*, Matrix34*))(g_pCore->GetBase() + 0x44F810))(quat, m_pVehicle->GetVehicle()->m_pMatrix);
	}
}

void CVehicleEntity::SetMoveSpeed(const CVector3& vecMoveSpeed)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetMoveSpeed(vecMoveSpeed);

	m_vecMoveSpeed = vecMoveSpeed;
}

void CVehicleEntity::GetMoveSpeed(CVector3& vecMoveSpeed)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->GetMoveSpeed(vecMoveSpeed);
	else
		vecMoveSpeed = m_vecMoveSpeed;
}

void CVehicleEntity::SetTurnSpeed(const CVector3& vecTurnSpeed)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetTurnSpeed(vecTurnSpeed);

	m_vecTurnSpeed = vecTurnSpeed;
}

void CVehicleEntity::GetTurnSpeed(CVector3& vecTurnSpeed)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->GetTurnSpeed(vecTurnSpeed);
	else
		vecTurnSpeed = m_vecTurnSpeed;
}

void CVehicleEntity::SetSirenState(bool bSirenState)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetSirenState(bSirenState);

	m_bSirenState = bSirenState;
}

bool CVehicleEntity::GetSirenState()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetSirenState();

	return m_bSirenState;
}

void CVehicleEntity::SetDirtLevel(float fDirtLevel)
{
	// Are we spawned?
	if(IsSpawned())
		m_pVehicle->SetDirtLevel(fDirtLevel);

	m_fDirtLevel = fDirtLevel;
}

float CVehicleEntity::GetDirtLevel()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetDirtLevel();

	return m_fDirtLevel;
}

BYTE CVehicleEntity::GetMaxPassengers()
{
	// Are we spawned?
	if(IsSpawned())
		return m_pVehicle->GetMaxPasssengers();

	return 0;
}

void CVehicleEntity::SetDoorLockState(DWORD dwDoorLockState)
{
	// Get the actual lock state
	DWORD dwState = 0;

	switch(dwDoorLockState)
	{
		case 0:
			dwState = 0;
			break;
		case 1:
			dwState = 3;
			break;
		case 2:
			dwState = 7;
			break;
		default:
		return;
	}

	m_dwDoorLockState = dwState;

	// Are we spawned?
	if(IsSpawned())
		EFLC::CScript::LockCarDoor(GetScriptingHandle(), m_dwDoorLockState);
}

DWORD CVehicleEntity::GetDoorLockState()
{
	DWORD dwState = m_dwDoorLockState;

	// Are we spawned?
	if(IsSpawned())
		dwState = m_pVehicle->GetDoorLockState();

	switch(dwState)
	{
	case 0:
		return 0;
	case 3:
		return 1;
	case 7:
		return 2;
	default:
		CLogFile::Printf("Unknown vehicle %d door state %d", m_vehicleId, m_pVehicle->GetDoorLockState()); 
	}
	return dwState;
}

void CVehicleEntity::Pulse()
{
	Interpolate();
}

void CVehicleEntity::UpdateTargetPosition()
{
    // Do we have a target position?
    if(HasTargetPosition())
    {
        // Get our position
        CVector3 vecCurrentPosition;
        GetPosition(vecCurrentPosition);

        // Get the factor of time spent from the interpolation start
        // to the current time.
        unsigned long ulCurrentTime = SharedUtility::GetTime();
        float fAlpha = Math::Unlerp(m_interp.pos.ulStartTime, ulCurrentTime, m_interp.pos.ulFinishTime);

        // Don't let it overcompensate the error too much
        fAlpha = Math::Clamp(0.0f, fAlpha, 1.5f);

        // Get the current error portion to compensate
        float fCurrentAlpha = (fAlpha - m_interp.pos.fLastAlpha);
        m_interp.pos.fLastAlpha = fAlpha;

        // Apply the error compensation
        CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_interp.pos.vecError);

        // If we finished compensating the error, finish it for the next pulse
        if(fAlpha == 1.5f)
                m_interp.pos.ulFinishTime = 0;

        // Calculate the new position
        CVector3 vecNewPosition = (vecCurrentPosition + vecCompensation);

		// Check if the distance to interpolate is too far
		if ((vecCurrentPosition - m_interp.pos.vecTarget).Length() > 20)
		{
			// Abort position interpolation
			m_interp.pos.ulFinishTime = 0;
			vecNewPosition = m_interp.pos.vecTarget;

			// Abort target interpolation
			if (HasTargetRotation())
			{
				SetRotation(m_interp.rot.vecTarget);
				m_interp.rot.ulFinishTime = 0;
			}

			g_pCore->GetGraphics()->GetChat()->Print(CString("Intepolate abort"));
		}

        // Set our new position
        SetPosition(vecNewPosition, true, false);
    }
}

void CVehicleEntity::UpdateTargetRotation()
{
	// Do we have a target rotation?
    if(HasTargetRotation())
    {
        // Get our current rotation
        CVector3 vecCurrentRotation;
        GetRotation(vecCurrentRotation);

        // Get the factor of time spent from the interpolation start
        // to the current time.
        unsigned long ulCurrentTime = SharedUtility::GetTime();
        float fAlpha = Math::Unlerp(m_interp.rot.ulStartTime, ulCurrentTime, m_interp.rot.ulFinishTime);

        // Don't let it to overcompensate the error
        fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

        // Get the current error portion to compensate
        float fCurrentAlpha = (fAlpha - m_interp.rot.fLastAlpha);
        m_interp.rot.fLastAlpha = fAlpha;

        // Compensate the error
        CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, m_interp.rot.vecError);

        // If we finished compensating the error, finish it for the next pulse
        if(fAlpha == 1.0f)
            m_interp.rot.ulFinishTime = 0;

        // Set the new rotation
        SetRotation((vecCurrentRotation + vecCompensation), false);
    }
}

void CVehicleEntity::Interpolate()
{
	// Do we have a driver?
	if(GetDriver())
	{

		// Update our target position
		UpdateTargetPosition();

		// Update our target rotation
		UpdateTargetRotation();

		// Update our interior
		UpdateInterior(true);
	}
	else
	{
		// Update our interior
		UpdateInterior(false);

		// Remove our target position
		RemoveTargetPosition();

		// Remove our target rotation
		RemoveTargetRotation();
	}
}

void CVehicleEntity::SetTargetPosition(const CVector3& vecPosition, unsigned long ulDelay)
{
    // Are we spawned?
    if(IsSpawned())
    {
        // Update our target position
        UpdateTargetPosition();

        // Get the current time
        unsigned long ulTime = SharedUtility::GetTime();

        // Get our local position
        CVector3 vecLocalPosition;
        GetPosition(vecLocalPosition);

        // Set the target position
        m_interp.pos.vecTarget = vecPosition;

        // Calculate the relative error
        m_interp.pos.vecError = (vecPosition - vecLocalPosition);

        // Apply the error over 400ms (i.e. 1/4 per 100ms)
        m_interp.pos.vecError *= Math::Lerp<const float>(0.25f, Math::UnlerpClamped(100, ulDelay, 400), 1.0f);

        // Get the interpolation interval
        m_interp.pos.ulStartTime = ulTime;
        m_interp.pos.ulFinishTime = (ulTime + ulDelay);

        // Initialize the interpolation
        m_interp.pos.fLastAlpha = 0.0f;
    }

    // Set our position straight
    m_vecPosition = vecPosition;
}

void CVehicleEntity::SetTargetRotation(const CVector3& vecRotation, unsigned long ulDelay)
{
    // Are we spawned?
    if(IsSpawned())
	{
        // Update our target rotation
        UpdateTargetRotation();

        // Get the current time
        unsigned long ulTime = SharedUtility::GetTime();

        // Get our local rotation
        CVector3 vecLocalRotation;
        GetRotation(vecLocalRotation);

        // Set the target rotation
        m_interp.rot.vecTarget = vecRotation;

        // Get the error
        m_interp.rot.vecError = Math::GetOffsetDegrees(vecLocalRotation, vecRotation);

        // Get the interpolation interval
        m_interp.rot.ulStartTime = ulTime;
        m_interp.rot.ulFinishTime = (ulTime + ulDelay);

        // Initialize the interpolation
        m_interp.rot.fLastAlpha = 0.0f;
    }

    // Set our rotation straight
    m_vecRotation = vecRotation;
}

void CVehicleEntity::RemoveTargetPosition()
{
    m_interp.pos.ulFinishTime = 0;
}

void CVehicleEntity::RemoveTargetRotation()
{
    m_interp.rot.ulFinishTime = 0;
}

void CVehicleEntity::ResetInterpolation()
{
    if(HasTargetPosition())
        SetPosition(m_interp.pos.vecTarget, true);

    if(HasTargetRotation())
        SetRotation(m_interp.rot.vecTarget);

    RemoveTargetPosition();
    RemoveTargetRotation();
}

void CVehicleEntity::UpdateInterior(bool bHasDriver)
{
}

void CVehicleEntity::SetInterior(unsigned int uiInterior)
{
}

unsigned CVehicleEntity::GetInterior()
{
	m_pVehicle->GetVehicle()->m_dwInteriorHandle;
	return 0;
}

void CVehicleEntity::SetIndicatorState(bool bFrontLeft, bool bFrontRight, bool bBackLeft, bool bBackRight)
{
    m_bIndicatorState[0] = bFrontLeft;
    m_bIndicatorState[1] = bFrontRight;
    m_bIndicatorState[2] = bBackLeft;
    m_bIndicatorState[3] = bBackRight;
        
    if(m_pVehicle)
    {
        auto pVehicle = m_pVehicle->GetVehicle();
        if(pVehicle)
        {
            pVehicle->indicators[0] = !bFrontLeft;
            pVehicle->indicators[1] = !bFrontRight;
            pVehicle->indicators[2] = !bBackLeft;
            pVehicle->indicators[3] = !bBackRight;
        }
	}
}

bool CVehicleEntity::GetIndicatorState(unsigned char ucSlot)
{
    if(ucSlot >= 0 && ucSlot <= 3)
    {
        return m_bIndicatorState[ucSlot];
    }

    return false;
}

void CVehicleEntity::SetComponentState(unsigned char ucSlot, bool bComponent)
{
    if(ucSlot <= 8)
    {
        m_bComponents[ucSlot] = bComponent;

        // Are we spawned?
        if(IsSpawned())
            m_pVehicle->SetComponentState((ucSlot + 1), bComponent);
    }
}

bool CVehicleEntity::GetComponentState(unsigned char ucSlot)
{
    if(ucSlot <= 8)
        return m_bComponents[ucSlot];

    return false;
}

void CVehicleEntity::SetVariation(unsigned char ucVariation)
{
    // Are we spawned?
    if(IsSpawned())
    {
        if(m_pVehicle->GetTextureVariationCount() != 255)
        {
            //m_pVehicle->SetTextureVariation(ucVariation);
			EFLC::CScript::SetCarLivery(GetScriptingHandle(), (int)ucVariation);
            m_ucVariation = ucVariation;
		}
        else
            m_ucVariation = 0;
    }
    else
        m_ucVariation = ucVariation;
}

unsigned char CVehicleEntity::GetVariation()
{
    // Are we spawned?
    if(IsSpawned())
	{
        if(m_pVehicle->GetTextureVariationCount() != 255)
        {
            //return (unsigned char)m_pVehicle->GetTextureVariation();
            int iVariation = 0;
			EFLC::CScript::GetCarLivery(GetScriptingHandle(), &iVariation);
            return iVariation;
        }
        else
            return 0;
    }
    else
        return m_ucVariation;
}

bool CVehicleEntity::IsOnScreen()
{
    // Are we spawned?
    if(IsSpawned())
    {
        CVector3 vecPos;
        m_pVehicle->GetPosition(vecPos);
        return g_pCore->GetGame()->GetCamera()->IsOnScreen(vecPos);
    }

    return false;
}

void CVehicleEntity::SetTaxiLightsState(bool bState)
{
    // Are we spawned?
    if(IsSpawned())
		EFLC::CScript::SetTaxiLights(GetScriptingHandle(), bState);

    m_bTaxiLights = bState;
}

bool CVehicleEntity::GetTaxiLightsState()
{
    // Are we spawned?
    if(IsSpawned())
        return m_bTaxiLights;

    return false;
}

void CVehicleEntity::SetCarDoorAngle(int iDoor,bool bClose, float fAngle)
{
    // Are we spawned?
    if(IsSpawned())
    {
        if(fAngle > 1.9f && fAngle < 350.0f)
			EFLC::CScript::ControlCarDoor(GetScriptingHandle(), (EFLC::CScript::eVehicleDoor)iDoor, bClose, fAngle);
        else if(fAngle >= 350.0f)
			EFLC::CScript::OpenCarDoor(GetScriptingHandle(), (EFLC::CScript::eVehicleDoor)iDoor);
        else if(fAngle < 2.0f)
			EFLC::CScript::ShutCarDoor(GetScriptingHandle(), (EFLC::CScript::eVehicleDoor)iDoor);
    }

    // Apply changes
    m_fDoor[iDoor] = fAngle;
}

float CVehicleEntity::GetCarDoorAngle(int iDoor)
{
    // Are we spawned?
    if(IsSpawned())
        return m_fDoor[iDoor];

    return 0.0f;
}

void CVehicleEntity::SetLightsState(bool bLights)
{
    // Are we spawned?
    if(IsSpawned())
    {
        if(bLights)
			EFLC::CScript::ForceCarLights(GetScriptingHandle(), 2);
        else
			EFLC::CScript::ForceCarLights(GetScriptingHandle(), 1);

        m_bLights = bLights;
    }
}

bool CVehicleEntity::GetLightsState()
{
	if (IsSpawned())
		return (m_pVehicle->GetLightsState() == 2);

	return false;
}

bool CVehicleEntity::GetWindowState(int iWindow)
{
	return false;
}

void CVehicleEntity::SetWindowState(int iWindow, bool bBroken)
{
	if (!IsSpawned())
		return;

	if (bBroken)
		m_pVehicle->RemoveVehicleWindow((EFLC::eVehicleWindow)iWindow);
	else
		; // TODO
}

void CVehicleEntity::SetDamageable(bool bToggle)
{
	if (IsSpawned())
		m_pVehicle->SetCarCanBeDamaged(bToggle);
}

void CVehicleEntity::SetSteeringAngle(float fSteeringAngle)
{
    // Are we spawned?
    if(IsSpawned())
        m_pVehicle->SetSteeringAngle(fSteeringAngle);
}

float CVehicleEntity::GetSteeringAngle()
{
    // Are we spawned?
    if(IsSpawned())
        m_pVehicle->GetSteeringAngle();

    return 0.0f;
}

void CVehicleEntity::SetEngineState(bool bState)
{
    // Are we spawned?
    if(IsSpawned()) 
        m_pVehicle->SetEngineStatus(bState, 1);
}

bool CVehicleEntity::GetEngineState()
{
    // Are we spawned?
    if(IsSpawned())
        return m_pVehicle->GetEngineStatus();

    return false;
}
void CVehicleEntity::SetVehicleGPSState(bool bState)
{
    if(IsSpawned())
		m_pVehicle->SetGPSState(bState);
}

bool CVehicleEntity::GetVehicleGPSState()
{
	if (IsSpawned())
		return m_pVehicle->GetGPSState();

	return false;
}

void CVehicleEntity::Fix()
{
	if (m_pVehicle)
	{
		auto pVehicle = m_pVehicle->GetVehicle();
		if (pVehicle)
		{
			pVehicle->Repair();
		}
	}
}

void CVehicleEntity::SetOccupant(BYTE byteSeatId, CPlayerEntity * pOccupant)
{
	if(byteSeatId == 0)
		SetDriver(pOccupant);
	else
		SetPassenger(pOccupant, (byteSeatId - 1));
}

CPlayerEntity * CVehicleEntity::GetOccupant(BYTE byteSeatId)
{
	if (byteSeatId >= 8)
		return nullptr;

	if (byteSeatId == 0)
		return m_pDriver;
	else
		return m_pPassengers[byteSeatId];

	return nullptr;
}