@echo off

setlocal
set PATH=%PATH%;%KinxPath$$VER_MAJ.$$VER_MIN.$$VER_PAT%\bin
cd %TEMP%
start "Kinx version $$VER_MAJ.$$VER_MIN.$$VER_PAT for x64"
endlocal
