@echo off

SET CFLAGS=/O2 /MT /Iinclude

if "%1"=="test" goto TEST_CODE

cl %CFLAGS% /Femyacc.exe utility/myacc.c
myacc.exe -vd -b kx -y kx_yy -Y KINX_YY src/kinx.y
REM kmyacc -v -b kx -m kmyacc.c.parser -p kx_yy -L c src/kinx.y
move kx.tab.c src/parser.c
move kx.tab.h include/parser.tab.h

cl %CFLAGS% /Fekinx.exe src/string.c src/parser.c src/lexer.c src/ast_object.c src/ast_display.c src/ast_analyzer.c src/ast_gencode.c src/ir_fix.c src/ir_dump.c src/ir_exec.c src/main.c src/exec/allocator.c src/kstr.c src/bigint.c
goto END

:TEST_CODE
REM call :TEST_EXEC add
call :TEST_EXEC subx
REM call :TEST_EXEC push
REM call :TEST_EXEC store
REM call :TEST_EXEC call
REM call :TEST_EXEC mkary
REM call :TEST_EXEC ret
REM call :TEST_EXEC haltnop
REM call :TEST_EXEC trycatch
del /q src\exec\test\*.res
goto END

:TEST_EXEC
if not exist kstr.obj       cl -c -nologo -DKX_EXEC_DEBUG %CFLAGS% src/kstr.c
if not exist bigint.obj     cl -c -nologo -DKX_EXEC_DEBUG %CFLAGS% src/bigint.c
if not exist ir_exec.obj    cl -c -nologo -DKX_EXEC_DEBUG %CFLAGS% src/ir_exec.c
if not exist ir_dump.obj    cl -c -nologo -DKX_EXEC_DEBUG %CFLAGS% src/ir_dump.c
if not exist allocator.obj  cl -c -nologo -DKX_EXEC_DEBUG %CFLAGS% src/exec/allocator.c
cl -nologo -DKX_EXEC_DEBUG %CFLAGS% /Fetest.exe src/exec/test/%1.c ir_exec.obj ir_dump.obj allocator.obj kstr.obj bigint.obj
echo Start testing... %1
REM test.exe
test.exe > src/exec/test/%1.exp
test.exe > src/exec/test/%1.res
fc src\exec\test\%1.exp src\exec\test\%1.res > NUL
if ERRORLEVEL 1 goto FAIL
echo Successful [%1]
exit /b 0

:END
del /q kstr.obj bigint.obj ir_dump.obj allocator.obj
exit /b 0

:FAIL
echo Failed [%1]
fc src\exec\test\%1.exp src\exec\test\%1.res
exit /b 0
