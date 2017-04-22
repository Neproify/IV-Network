//========= IV: Network - https://github.com/Neproify/IV-Network ============
//
// File: CEventNatives.h
// Project: Shared
// Author: xForce <xf0rc3.11@gmail.com>
// License: See LICENSE in root directory
//
//==============================================================================

#ifndef CEventNatives_h
#define CEventNatives_h

#include <Scripting/IScriptVM.h>
#include "Network\NetCommon.h"

class CEventNatives {

private:
	static int	AddEvent(int * pVM);
	static int	AddGlobalEvent(int * pVM);
	static int  AddRemoteEvent(int * pVM);

	static int	TriggerEvent(int * pVM);
	static int	TriggerGlobalEvent(int * pVM);
	static int	TriggerRemoteEvent(int * pVM);
	
	static int	AddCommandHandler(int * pVM);
public:
	static void Register(IScriptVM* pVM);
};

#endif // CEventNatives_h