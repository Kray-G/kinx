@echo off

if "%1" == "" (
    if exist "kinx.exe" (
        kinx.exe utility\VersionSetup.kx 0.19.0
    )
    cl.exe /DWINMAIN /Feaddpath.exe utility\src\addpath.c Advapi32.lib User32.lib /link /SUBSYSTEM:WINDOWS
    cl.exe /Feaddpathc.exe utility\src\addpath.c Advapi32.lib User32.lib
    cl.exe /Feecho.exe utility\src\kecho.c
)

nmake -f Makefile.msc %*
