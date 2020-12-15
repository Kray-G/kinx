@echo off
for /f "usebackq" %%I in (`dir /b Kinx_installer_*.exe`) do set artifact=%%I
exit /b 0
