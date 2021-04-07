@echo off

if "%1" == "" (
    if exist "..\kinx.exe" (
        ..\kinx.exe utility\VersionSetup.kx 1.1.0
    )
    cl.exe /DWINMAIN /Feaddpath.exe utility\src\addpath.c Advapi32.lib User32.lib /link /SUBSYSTEM:WINDOWS
    cl.exe /Feaddpathc.exe utility\src\addpath.c Advapi32.lib User32.lib
    cl.exe /Feecho.exe utility\src\kecho.c
)
for /f "usebackq" %%A in (`git rev-parse HEAD`) do set VER_HASH=%%A

mkdir -p licenses
copy /y ..\docs\licenses\*.* licenses\*.*

if "%1" == "rebuild" goto REBUILD
nmake -f Makefile.msc %*
if ERRORLEVEL 1 goto ERROR
goto END

:REBUILD
nmake -f Makefile.msc clean all
if ERRORLEVEL 1 goto ERROR

:END
exit /b 0

:ERROR
exit /b 1
