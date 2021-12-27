# Theme
!define MUI_ICON "build\template\theme\standard\installer.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "build\template\theme\standard\wizard.bmp"
!define MUI_UNICON "build\template\theme\standard\uninstaller.ico"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "build\template\theme\standard\wizard-uninst.bmp"

# Modern UI
!include MUI2.nsh
!include FileFunc.nsh
!include WinMessages.nsh

# Unicode
Unicode True

# Version
!define MAJ_VERSION "1"
!define VERSION_STRING "1.1.1"

# Application Name
Name "Kinx version ${VERSION_STRING} for x64"

# Installer Name to be created
OutFile "Kinx_installer_x64.${VERSION_STRING}.exe"

# Intall Directory
InstallDir "$PROGRAMFILES64\Kinx\V${MAJ_VERSION}"

# Setup Some Options
SetCompressor lzma
XPStyle on

# Installer Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE LICENSE
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

# Uninstaller Pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

# Japanese UI
!insertmacro MUI_LANGUAGE "English"
# !insertmacro MUI_LANGUAGE "Japanese"

# Interface Settings
!define MUI_ABORTWARNING

# Registry Settings
!define APPNAME "Kinx"
!define ARP "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
!define ARP32 "Software\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
!define ENV_HKLM 'HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"'
!define ENV_HKCU 'HKCU "Environment"'

# Section
Section
  # Registry
  SetRegView 64

  # File List
  SetOutPath "$INSTDIR\bin"
  File "kinx.exe"
  File "kinxw.exe"
  File "kxrepl.exe"
  File "kxtest.exe"
  File "kip.exe"
  File "addpath.exe"
  File "addpathc.exe"
  File "*.dll"

  SetOutPath "$INSTDIR\bin\lib"
  File /r /x ".gitignore" "lib\std"
  File /r /x ".gitignore" "lib\exec"
  File /r /x ".gitignore" "lib\webview"

  SetOutPath "$INSTDIR\docs"
  File /r "build\licenses"

  # Uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  CreateDirectory "$INSTDIR\bin\lib\package"

  # Shortcut to start menu
  CreateDirectory "$SMPROGRAMS\Kinx"
  CreateShortcut "$SMPROGRAMS\Kinx\Kinx Repl ${VERSION_STRING}.lnk" "$INSTDIR\bin\kxrepl.exe" ""

  ${GetSize} "$INSTDIR\bin" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0
  WriteRegDWORD HKLM "${ARP}" "EstimatedSize" "$0"

  # Setup Environment Variable
  WriteRegExpandStr ${ENV_HKLM} KinxPath $INSTDIR
  WriteRegExpandStr ${ENV_HKCU} KinxPath $INSTDIR
  SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=10

  # Setup Registry
  WriteRegStr HKLM "${ARP}" "DisplayName" "Kinx version ${VERSION_STRING} for x64"
  WriteRegStr HKLM "${ARP}" "Publisher" "Kray-G"
  WriteRegStr HKLM "${ARP}" "DisplayIcon" "$INSTDIR\bin\kinx.exe"
  WriteRegStr HKLM "${ARP}" "DisplayVersion" "${VERSION_STRING}"
  WriteRegDWORD HKLM "${ARP}" "VersionMajor" "1"
  WriteRegDWORD HKLM "${ARP}" "VersionMinor" "1"
  WriteRegStr HKLM "${ARP}" "Comments" "Have fun with programming!"
  WriteRegStr HKLM "${ARP}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegStr HKLM "${ARP}" "QuietUninstallString" '"$INSTDIR\Uninstall.exe" /S'

  ExecWait '"$INSTDIR\bin\addpath.exe" add system "$INSTDIR\bin"'
  ExecWait '"$INSTDIR\bin\addpath.exe" add user "$INSTDIR\bin"'
SectionEnd

# Uninstaller
Section "Uninstall"
  # Registry
  SetRegView 64

  ExecWait '"$INSTDIR\bin\addpath.exe" del user "$INSTDIR\bin"'
  ExecWait '"$INSTDIR\bin\addpath.exe" del system "$INSTDIR\bin"'

  # Delete Uninstaller
  Delete "$INSTDIR\Uninstall.exe"

  # Delete Files and Directories
  RMDir /r "$INSTDIR\bin"
  RMDir "$INSTDIR\bin"
  RMDir /r "$INSTDIR\docs"
  RMDir "$INSTDIR\docs"
  RMDir "$INSTDIR"

  # Delete it from start menu.
  Delete "$SMPROGRAMS\Kinx\Kinx Repl ${VERSION_STRING}.lnk"
  RMDir "$SMPROGRAMS\Kinx"

  # Remove Environment Variable
  DeleteRegValue ${ENV_HKLM} KinxPath
  DeleteRegValue ${ENV_HKCU} KinxPath
  SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=10

  # Remove Registry Key
  DeleteRegKey HKLM "${ARP}"
SectionEnd

Function .onInit
  # Registry
  SetRegView 64

  InitPluginsDir
  ReadRegStr $R1 HKLM ${ARP} DisplayVersion
  ${If} $R1 S== ""
    ReadRegStr $R1 HKLM ${ARP32} DisplayVersion
  ${EndIf}
  ReadRegStr $R0 ${ENV_HKLM} KinxPath
  ${If} $R0 S!= ""
    MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION "${APPNAME} $R1 has been already installed.$\nDo you want to uninstall it before installation?" IDOK uninstOld
    Abort
    uninstOld:
    CreateDirectory "$PLUGINSDIR\olduninst"
    CopyFiles /SILENT /FILESONLY "$R0\Uninstall.exe" "$PLUGINSDIR\olduninst"
    ExecWait '"$PLUGINSDIR\olduninst\Uninstall.exe" _?=$R0'
  ${EndIf}
FunctionEnd

