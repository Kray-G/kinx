# Modern UI
!include MUI2.nsh
!include FileFunc.nsh

# Unicode
Unicode True

# Application Name
Name "The Script Kinx"

# Installer Name to be created
OutFile "kinx_x64_installer.exe"

# Intall Directory
InstallDir "$PROGRAMFILES64\Kinx"

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
!insertmacro MUI_LANGUAGE "Japanese"

# Interface Settings
!define MUI_ABORTWARNING

# Registry Settings
!define APPNAME "Kinx"
!define ARP "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"

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
  CreateShortcut "$SMPROGRAMS\Kinx\Kinx Shell.lnk" "$INSTDIR\bin\kinxsh.cmd" ""
  CreateShortcut "$SMPROGRAMS\Kinx\Kinx Repl.lnk" "$INSTDIR\bin\kxrepl.exe" ""

  # Shortcut to desktop
  # CreateShortcut "$DESKTOP\Kinx Shell.lnk" "$INSTDIR\bin\kinxsh.cmd" ""

  ${GetSize} "$INSTDIR\bin" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0
  WriteRegDWORD HKLM "${ARP}" "EstimatedSize" "$0"

  # Setup Registry
  WriteRegStr HKLM "${ARP}" "DisplayName" "Kinx 0.16.0 (x64)"
  WriteRegStr HKLM "${ARP}" "Publisher" "Kray-G"
  WriteRegStr HKLM "${ARP}" "DisplayVersion" "0.16.0"
  WriteRegDWORD HKLM "${ARP}" "VersionMajor" "0"
  WriteRegDWORD HKLM "${ARP}" "VersionMinor" "16"
  WriteRegStr HKLM "${ARP}" "Comments" "Looks like JavaScript, feels like Ruby, and it is a script language fitting in C programmers."
  WriteRegStr HKLM "${ARP}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
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
  Delete "$SMPROGRAMS\Kinx\Kinx Repl.lnk"
  Delete "$SMPROGRAMS\Kinx\Kinx Shell.lnk"
  RMDir "$SMPROGRAMS\Kinx"

  # Remove Registry Key
  DeleteRegKey HKLM "${ARP}"
SectionEnd
