@echo off
setlocal

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
call :TEST_SETUP
REM call :TEST_EXEC add
REM call :TEST_EXEC sub
REM call :TEST_EXEC lt
REM call :TEST_EXEC le
REM call :TEST_EXEC lge
REM call :TEST_EXEC gt
REM call :TEST_EXEC ge
REM call :TEST_EXEC eqeq
REM call :TEST_EXEC neq
REM call :TEST_EXEC and
call :TEST_EXEC or
REM call :TEST_EXEC push
REM call :TEST_EXEC store
REM call :TEST_EXEC call
REM call :TEST_EXEC mkary
REM call :TEST_EXEC ret
REM call :TEST_EXEC haltnop
REM call :TEST_EXEC trycatch
call :TEST_EXEC fib
goto END

:TEST_SETUP
if not exist kstr.obj       timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/kstr.c
if not exist bigint.obj     timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/bigint.c
if not exist ir_dump.obj    timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/ir_dump.c
if not exist allocator.obj  timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/exec/allocator.c
if not exist ir_exec.obj    timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/ir_exec.c
exit /b 0

:TEST_EXEC
call :MKDOTS %1
set /P _DUMMY=Starting [%1] %DOTS% < NUL
cl -nologo -DKX_EXEC_NODEBUG %CFLAGS% /Fetest.exe src/exec/test/%1.c ir_exec.obj ir_dump.obj allocator.obj kstr.obj bigint.obj > NUL
test.exe
if ERRORLEVEL 1 goto FAILED
echo Successful
exit /b 0

:FAILED
echo ******************************** Failed!
exit /b 0

:MKDOTS
set _S=%1
set LEN=0
:STRLEN_LOOP
if defined _S (
    set _S=%_S:~1%
    set /A LEN+=1
    goto :STRLEN_LOOP
)
set /A LEN=16-%LEN%
set DOTS=
:MKDOTS_LOOP
if not %LEN% equ 0 (
    set DOTS=%DOTS%.
    set /A LEN-=1
    goto :MKDOTS_LOOP
)
exit /b

:END
REM del /q kstr.obj bigint.obj ir_dump.obj allocator.obj
REM del /q ir_exec.obj
endlocal
exit /b 0
