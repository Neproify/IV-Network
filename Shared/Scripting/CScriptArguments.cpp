//========= IV: Network - https://github.com/Neproify/IV-Network ============
//
// File: CScriptArguments.cpp
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#include "CScriptArguments.h"
#include "CScriptArgument.h"
#include "IScriptVM.h"

CScriptArguments::~CScriptArguments()
{
	reset();
}

CScriptArguments::CScriptArguments()
{
	reset();
}

void CScriptArguments::reset()
{
	for(auto pArgument : m_Arguments)
		delete pArgument;

	m_Arguments.clear();
}

CScriptArguments::CScriptArguments(const CScriptArguments& p)
{
	for(auto pArgument : p.m_Arguments)
		m_Arguments.push_back(new CScriptArgument(*pArgument));
}

void CScriptArguments::push(const CScriptArgument &arg)
{
	m_Arguments.push_back(new CScriptArgument(arg));
}

void CScriptArguments::push(int i)
{
	m_Arguments.push_back(new CScriptArgument(i));
}

void CScriptArguments::push(bool b)
{
	m_Arguments.push_back(new CScriptArgument(b));
}

void CScriptArguments::push(float f)
{
	m_Arguments.push_back(new CScriptArgument(f));
}

void CScriptArguments::push(const char* c)
{
	m_Arguments.push_back(new CScriptArgument(CString(c)));
}

void CScriptArguments::push(CString str)
{
	m_Arguments.push_back(new CScriptArgument(CString(str)));
}

void CScriptArguments::push(const CScriptArguments &array, bool isArray)
{
	m_Arguments.push_back(new CScriptArgument(array, isArray));
}

void CScriptArguments::push(CScriptArguments* pArray, bool isArray)
{
	m_Arguments.push_back(new CScriptArgument(*pArray, isArray));
}


void CScriptArguments::push(CScriptEntity* pEntity)
{
	m_Arguments.push_back(new CScriptArgument(pEntity));
}

void CScriptArguments::pushVector3(const CVector3 &vec3)
{
	m_Arguments.push_back(new CScriptArgument(vec3.fX));
	m_Arguments.push_back(new CScriptArgument(vec3.fY));
	m_Arguments.push_back(new CScriptArgument(vec3.fZ));
}

void CScriptArguments::Serialize(RakNet::BitStream *pBitStream)
{
	for (auto arg : m_Arguments)
	{
		switch (arg->GetType())
		{
		case CScriptArgument::ArgumentType::ST_BOOL:
		{
			pBitStream->Write(CScriptArgument::ArgumentType::ST_BOOL);
			pBitStream->Write(arg->GetBool());
			break;
		}
		case CScriptArgument::ArgumentType::ST_FLOAT:
		{
			pBitStream->Write(CScriptArgument::ArgumentType::ST_FLOAT);
			pBitStream->Write(arg->GetFloat());
			break;
		}
		case CScriptArgument::ArgumentType::ST_INTEGER:
		{
			pBitStream->Write(CScriptArgument::ArgumentType::ST_INTEGER);
			pBitStream->Write(arg->GetInteger());
			break;
		}
		case CScriptArgument::ArgumentType::ST_STRING:
		{
			pBitStream->Write(CScriptArgument::ArgumentType::ST_STRING);
			pBitStream->Write(RakString(arg->GetString()));
			break;
		}
		case CScriptArgument::ArgumentType::ST_ARRAY:
		{
			// TODO
			CLogFile::Printf("Unsupported type: ARRAY on CScriptArguments::Serialize");
			break;
		}
		case CScriptArgument::ArgumentType::ST_TABLE:
		{
			// TODO
			CLogFile::Printf("Unsupported type: TABLE on CScriptArguments::Serialize");
			break;
		}
		default:
		{
			CLogFile::Printf("Invalid CScriptArgument on Serialize.");
			break;
		}
		}
	}
}

void CScriptArguments::Deserialize(RakNet::BitStream *pBitStream)
{
	while (pBitStream->GetNumberOfUnreadBits() > 0)
	{
		int argType;
		pBitStream->Read(argType);
		switch (argType)
		{
		case CScriptArgument::ArgumentType::ST_BOOL:
		{
			bool data;
			pBitStream->Read(data);
			push(data);
			break;
		}
		case CScriptArgument::ArgumentType::ST_FLOAT:
		{
			float data;
			pBitStream->Read(data);
			push(data);
			break;
		}
		case CScriptArgument::ArgumentType::ST_INTEGER:
		{
			int data;
			pBitStream->Read(data);
			push(data);
			break;
		}
		case CScriptArgument::ArgumentType::ST_STRING:
		{
			RakString _data;
			pBitStream->Read(_data);
			CString data = CString(_data.C_String());
			push(data);
			break;
		}
		case CScriptArgument::ArgumentType::ST_ARRAY:
		{
			// TODO
			CLogFile::Printf("Unsupported type: ARRAY on CScriptArguments::Deserialize");
			break;
		}
		case CScriptArgument::ArgumentType::ST_TABLE:
		{
			// TODO
			CLogFile::Printf("Unsupported type: TABLE on CScriptArguments::Deserialize");
			break;
		}
		default:
		{
			CLogFile::Printf("Invalid type of CScriptArgument on Deserialize.");
			break;
		}
		}
	}
}