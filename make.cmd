@echo off
setlocal
set CFLAGS=/O2 /MT /Iinclude

if "%1"=="test" goto TEST_CODE

set YACC=myacc
if "%YACC%"=="kmyacc" (
    set CFLAGS=%CFLAGS% /DYYDEBUG
    kmyacc -vd -b kx -m kmyacc.c.parser -p kx_yy -L c src/kinx.y
) else (
    cl %CFLAGS% /Femyacc.exe utility/myacc.c
    myacc.exe -vd -b kx -y kx_yy -Y KINX_YY src/kinx.y
)
del parser.obj
del lexer.obj
move kx.tab.c src/parser.c
move kx.tab.h include/parser.tab.h

set OBJS=string.obj parser.obj lexer.obj ast_object.obj ast_display.obj ast_analyzer.obj ast_gencode.obj ir_fix.obj ir_dump.obj ir_exec.obj main.obj allocator.obj kstr.obj bigint.obj
REM del %OBJS%
call :COMPILE %OBJS%
cl %CFLAGS% /Fekinx.exe %OBJS%
goto END

:TEST_CODE
call :TEST_SETUP
REM call :TEST_EXEC apply
call :TEST_EXEC append
REM call :TEST_EXEC add
REM call :TEST_EXEC sub
REM call :TEST_EXEC mul
REM call :TEST_EXEC div
REM call :TEST_EXEC mod
REM call :TEST_EXEC shl
REM call :TEST_EXEC shr
REM call :TEST_EXEC inc
REM call :TEST_EXEC dec
REM call :TEST_EXEC lt
REM call :TEST_EXEC le
REM call :TEST_EXEC lge
REM call :TEST_EXEC gt
REM call :TEST_EXEC ge
REM call :TEST_EXEC eqeq
REM call :TEST_EXEC neq
REM call :TEST_EXEC and
REM call :TEST_EXEC or
REM call :TEST_EXEC xor
REM call :TEST_EXEC neg
REM call :TEST_EXEC not
REM call :TEST_EXEC push
REM call :TEST_EXEC store
REM call :TEST_EXEC call
REM call :TEST_EXEC mkary
REM call :TEST_EXEC ret
REM call :TEST_EXEC haltnop
REM call :TEST_EXEC trycatch
call :TEST_EXEC fib
goto END

:COMPILE
if "%1"=="" exit /b 0
set OBJ=%1
if not exist %OBJ% timeit cl -c -nologo %CFLAGS% src/%OBJ:.obj=.c%
shift
goto COMPILE

:TEST_SETUP
if not exist string.obj     timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/string.c
if not exist kstr.obj       timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/kstr.c
if not exist bigint.obj     timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/bigint.c
if not exist ir_dump.obj    timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/ir_dump.c
if not exist allocator.obj  timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/allocator.c
if not exist ir_exec.obj    timeit cl -c -nologo -DKX_EXEC_NODEBUG %CFLAGS% src/ir_exec.c
exit /b 0

:TEST_EXEC
call :MKDOTS %1
set /P _DUMMY=Starting [%1] %DOTS% < NUL
cl -nologo -DKX_EXEC_NODEBUG %CFLAGS% /Fetest.exe src/exec/test/%1.c ir_exec.obj ir_dump.obj allocator.obj kstr.obj bigint.obj string.obj > NUL
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
