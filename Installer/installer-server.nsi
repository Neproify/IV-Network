; DO NOT TRY TO COMPILE THIS FILE (installer_template.nsi).
; ${VERSION} will be replaced by custom script, no macro definition needed

;======================================================
; Includes
!include nsDialogs.nsh
!include "MUI2.nsh"
!include LogicLib.nsh

;======================================================
; Configuration
!define NAME 'IVNetworkServer'

;======================================================
; Modern Interface Configuration
!define MUI_ICON .\icon.ico
!define MUI_INSTALLCOLORS "DDDDDD 333333"
!define MUI_INSTFILESPAGE_COLORS "DDDDDD 333333"
!define MUI_INSTFILESPAGE_PROGRESSBAR colored

;======================================================
; Installer Information
Name "${NAME} ${VERSION}"
OutFile "${NAME}-${VERSION}-r${REVISION}.exe"
SetCompressor /SOLID lzma
CRCCheck force
BrandingText /TRIMCENTER "${NAME} ${VERSION} Setup"
ShowInstDetails show
ShowUninstDetails show
RequestExecutionLevel admin

;======================================================
; Pages

; Get Install Directory Page
Page directory

DirText "Welcome to the installer for ${NAME} ${VERSION} server.$\n$\n" "Please select the directory to install IV:Network server to."
InstallDir "$PROGRAMFILES\IVNetworkServer"

;======================================================
; Installer

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"

;======================================================
; Sections

Section "Install" SecDummy
	SetOverwrite on

	; Copy New Files
	
	SetOutPath "$INSTDIR"

	File ..\Files\IVNetworkDedicatedServer.exe
	
SectionEnd