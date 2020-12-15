# Theme
!define MUI_ICON "template\theme\standard\installer.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "template\theme\standard\wizard.bmp"
!define MUI_UNICON "template\theme\standard\uninstaller.ico"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "template\theme\standard\wizard-uninst.bmp"

# Modern UI
!include MUI2.nsh
!include FileFunc.nsh
!include WinMessages.nsh

# Unicode
Unicode True

# Version
!define MAJ_VERSION "1"
!define VERSION_STRING "$$VER_MAJ.$$VER_MIN.$$VER_PAT"

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
!define ENV_HKLM 'HKLM "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"'
!define ENV_HKCU 'HKCU "Environment"'

# Section
Section
  # File List
  SetOutPath "$INSTDIR\bin"
  File "kinxsh.cmd"
  File "kinx.exe"
  File "kxrepl.exe"
  File "kxtest.exe"
  File "kxkitty.exe"
  File "*.dll"

  SetOutPath "$INSTDIR\bin\lib"
  File /r "lib\std"
  File /r "lib\exec"
  File /r "lib\katex"
  File /r "lib\chartjs"

  # Uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  # Shortcut to start menu
  CreateDirectory "$SMPROGRAMS\Kinx"
  CreateShortcut "$SMPROGRAMS\Kinx\Kinx Shell ${VERSION_STRING}.lnk" "$INSTDIR\bin\kinxsh.cmd" ""
  CreateShortcut "$SMPROGRAMS\Kinx\Kinx Repl ${VERSION_STRING}.lnk" "$INSTDIR\bin\kxrepl.exe" ""

  # Shortcut to desktop
  # CreateShortcut "$DESKTOP\Kinx Shell.lnk" "$INSTDIR\bin\kinxsh.cmd" ""

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
  WriteRegDWORD HKLM "${ARP}" "VersionMajor" "$$VER_MAJ"
  WriteRegDWORD HKLM "${ARP}" "VersionMinor" "$$VER_MIN"
  WriteRegStr HKLM "${ARP}" "Comments" "Looks like JavaScript, feels like Ruby, and it is a script language fitting in C programmers."
  WriteRegStr HKLM "${ARP}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegStr HKLM "${ARP}" "QuietUninstallString" '"$INSTDIR\Uninstall.exe" /S'
SectionEnd

# Uninstaller
Section "Uninstall"
  SetOutPath "$INSTDIR"

  # Delete Uninstaller
  Delete "$INSTDIR\Uninstall.exe"

  # Delete Files and Directories
  RMDir /r "$INSTDIR\bin"
  RMDir "$INSTDIR\bin"
  RMDir "$INSTDIR"

  # Delete it from start menu.
  Delete "$SMPROGRAMS\Kinx\Kinx Repl ${VERSION_STRING}.lnk"
  Delete "$SMPROGRAMS\Kinx\Kinx Shell ${VERSION_STRING}.lnk"
  RMDir "$SMPROGRAMS\Kinx"
  RMDir "$SMPROGRAMS\Kinx"

  # Remove Environment Variable
  DeleteRegValue ${ENV_HKLM} KinxPath
  DeleteRegValue ${ENV_HKCU} KinxPath
  SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=10

  # Remove Registry Key
  DeleteRegKey HKLM "${ARP}"
SectionEnd

Function .onInit
  InitPluginsDir
  ReadRegStr $R0 ${ENV_HKLM} KinxPath
  ${If} $R0 S!= ""
    MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION "${APPNAME} ${VERSION_STRING} has been already installed.$\nDo you want to uninstall it before installation?" IDOK uninstOld
    Abort
    uninstOld:
    CreateDirectory "$PLUGINSDIR\olduninst"
    CopyFiles /SILENT /FILESONLY "$R0\Uninstall.exe" "$PLUGINSDIR\olduninst"
    ExecWait '"$PLUGINSDIR\olduninst\Uninstall.exe" _?=$R0'
  ${EndIf}
FunctionEnd
