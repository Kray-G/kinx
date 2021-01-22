@echo off
pushd build
call make.cmd %*
if ERRORLEVEL 1 goto END
copy /y kinx.exe ..
copy /y kxrepl.exe ..
copy /y kxtest.exe ..
copy /y *.dll ..
:END
popd
