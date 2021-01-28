@echo off
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
copy /y kxrepl.exe ..
copy /y kxtest.exe ..
copy /y addpath.exe ..
copy /y kx.lib ..
copy /y *.dll ..

:END
popd
