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

#include "CCrashFixes.h"
#include <CCore.h>

extern CCore* g_pCore;

int				hFile2;
_declspec(naked) void TextureSelect_Hook()
{
	_asm	mov eax, [esp + 4];
	//_asm	mov iTexture, eax;
	_asm	mov eax, [esp + 8];
	_asm	mov hFile2, eax;
	_asm	pushad;

	if (hFile2 < 10000000)
		g_pCore->GetGame()->ThrowInternalException(COffsets::FUNC_GENERATETEXTURE, 0xC0000005);

	_asm	popad;
	_asm	push ebx;
	_asm	push esi;
	_asm	push edi;
	_asm	mov edi, ecx;
	_asm	jmp COffsets::IV_Hook__TextureSelect__JmpBack;
}

void _declspec(naked) __stdcall CRASH_625F15_HOOK()
{
	_asm	test eax, eax;
	_asm	jz keks;
	_asm	cmp eax, 100000h;
	_asm	jl keks;
	_asm	mov edx, [eax];
	_asm	push 1;
	_asm	mov ecx, edi;
	_asm	call edx;

	_asm	keks_patch:;
	_asm	mov al, 1;
	_asm	pop edi;
	_asm	pop esi;
	_asm	pop ebp;
	_asm	pop ebx;
	_asm	add esp, 0Ch;
	_asm	retn 4;
	_asm	keks:;
	_asm	pushad;

	g_pCore->GetGame()->ThrowInternalException(COffsets::IV_Hook__UnkownPatch2, 0xC0000005);

	_asm	popad;
	_asm	jmp keks_patch;
}

DWORD sub_40AC26 = 0;

void _declspec(naked) __stdcall CRASH_40AC26_HOOK()
{
	_asm	mov eax, ecx;
	_asm	mov ecx, [esp + 4];
	_asm	cmp ecx, 1000h;
	_asm	jl fail;
	_asm	jmp sub_40AC26;
	_asm	fail:;
	_asm	retn 4;
}

void CCrashFixes::Initialize()
{
	// Hook texture select/generate function
	//CPatcher::InstallJmpPatch(COffsets::FUNC_GENERATETEXTURE, (DWORD) TextureSelect_Hook);

	// Fix vehicle crash -> 8 xrefs
	//CPatcher::InstallJmpPatch(COffsets::IV_Hook__PatchPreventVehicleCrash, (COffsets::IV_Hook__PatchPreventVehicleCrash + 40));

	// this disables a call to a destructor of a member in rageResourceCache [field_244] 
	//CPatcher::InstallJmpPatch(COffsets::IV_Hook__UnkownPatch2, (DWORD)CRASH_625F15_HOOK);

	// Disables zone population calcs fixes crash with some vehicles
	CPatcher::InstallRetnPatch(COffsets::IV_Hook__PatchEnableAndFixVehicleModels);

	CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0x40AC20, (DWORD)CRASH_40AC26_HOOK);
	sub_40AC26 = g_pCore->GetBase() + 0x40AC26;

	//CPatcher::InstallJmpPatch(g_pCore->GetBase() + 0xA6180C, g_pCore->GetBase() + 0xA619F7);
}