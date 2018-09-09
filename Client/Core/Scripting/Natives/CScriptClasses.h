//========= IV: Network - https://github.com/Neproify/IV-Network ============
//
// File: CScriptClasses.h
// Project: Client.Core
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CScriptClasses_h
#define CScriptClasses_h

#include <Scripting/IScriptVM.h>
#include "../Shared/Scripting/CScriptClass.h"

class CScriptClasses
{
private:
	static int	CreateEntity(int * pVM);
public:
	static void Register(IScriptVM* pVM);
};

#endif // CScriptClasses_h