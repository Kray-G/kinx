@echo off
if "%1"=="installer" goto INSTALLER
if "%1"=="inst" goto INSTALLER

pushd build
call make.cmd %*
if ERRORLEVEL 1 goto END
if "%1"=="" goto COPY
if "%1"=="all" goto COPY
if "%1"=="rebuild" goto COPY
goto END

:COPY
copy /y echo.exe ..
copy /y kinx.exe ..
copy /y kinxw.exe ..
copy /y kxrepl.exe ..
copy /y kxtest.exe ..
copy /y addpath.exe ..
copy /y kx.lib ..
copy /y *.dll ..
goto END

:INSTALLER
if exist "c:\Program Files (x86)\NSIS\Bin\makensis.exe" (
    "c:\Program Files (x86)\NSIS\Bin\makensis.exe" install.nsi
)

:END
popd
