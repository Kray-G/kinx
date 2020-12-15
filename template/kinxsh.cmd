@echo off

setlocal
set PATH=%KinxPath%\bin;%PATH%
cd %TEMP%
start "Kinx version $$VER_MAJ.$$VER_MIN.$$VER_PAT for x64"
endlocal
