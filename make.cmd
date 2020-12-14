@echo off

if exist "kinx.exe" (
    kinx.exe utility\VersionSetup.kx 0.17.0
)

nmake -f Makefile.msc %*
