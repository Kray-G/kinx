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
call :TEST_EXEC sub
REM call :TEST_EXEC lt
REM call :TEST_EXEC push
REM call :TEST_EXEC store
REM call :TEST_EXEC call
REM call :TEST_EXEC mkary
REM call :TEST_EXEC ret
REM call :TEST_EXEC haltnop
REM call :TEST_EXEC trycatch
REM call :TEST_EXEC fib
goto END

:TEST_EXEC
if not exist kstr.obj       timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/kstr.c
if not exist bigint.obj     timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/bigint.c
if not exist ir_exec.obj    timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/ir_exec.c
if not exist ir_dump.obj    timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/ir_dump.c
if not exist allocator.obj  timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/exec/allocator.c
cl -nologo -DKX_EXEC_NODEBUG %CFLAGS% /Fetest.exe src/exec/test/%1.c ir_exec.obj ir_dump.obj allocator.obj kstr.obj bigint.obj > NUL
test.exe
if ERRORLEVEL 1 goto FAIL
echo Successful [%1]
exit /b 0

:END
REM del /q kstr.obj bigint.obj ir_dump.obj allocator.obj
REM del /q ir_exec.obj
exit /b 0

:FAIL
echo Failed [%1]
exit /b 0
