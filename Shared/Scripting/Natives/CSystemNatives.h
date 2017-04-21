//========= IV: Network - https://github.com/Neproify/IV-Network ============
//
// File: CSystemNatives.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CSystemNatives_h
#define CSystemNatives_h

#include <Scripting/IScriptVM.h>

class CSystemNatives {

private:
	static int	Print(int * pVM);
	static int  Logf(int * pVM); 
	static int	CreateEntity(int * pVM);
	static int  Date(int * pVM); 
	static int	GetTickCount(int * pVM);
public:
	static void Register(IScriptVM* pVM);
};

#endif // CSystemNatives_h