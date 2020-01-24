@echo off
setlocal

set YACC=myacc
REM set CFLAGS=/O2 /D_DEBUG /MTd /Iinclude
set CFLAGS=/O2 /MT /Iinclude

if "%1"=="clean" goto CLEAN_OBJS

call :BUILDLIB

if "%1"=="test" goto TEST_CODE

set OBJS=getopt.obj string.obj parser.obj lexer.obj main.obj allocator.obj allocutil.obj alloccore.obj kstr.obj bign.obj bigz.obj loadlib.obj global.obj
set OBJS=%OBJS% ast_object.obj ast_display.obj ast_analyzer.obj ast_gencode.obj
set OBJS=%OBJS% ir_fix.obj ir_dump.obj ir_exec.obj ir_util.obj
REM del %OBJS%
call :COMPILE %OBJS%
timex cl /nologo %CFLAGS% /Fekinx.exe %OBJS%
timex cl /LD /nologo %CFLAGS% /DKX_DLL src/extlib/kxsystem.c bign.obj bigz.obj allocutil.obj
timex cl /LD /nologo %CFLAGS% /DKX_DLL src/extlib/kxstring.c bign.obj bigz.obj
timex cl /LD /nologo %CFLAGS% /DKX_DLL src/extlib/kxarray.c  bign.obj bigz.obj kstr.obj allocutil.obj
timex cl /LD /nologo %CFLAGS% /DKX_DLL src/extlib/kxregex.c  bign.obj bigz.obj kstr.obj allocutil.obj onig.lib
goto END

:TEST_CODE
call :COMPILE %OBJS%
call :TEST_EXEC apply
call :TEST_EXEC append
call :TEST_EXEC add
call :TEST_EXEC sub
call :TEST_EXEC mul
call :TEST_EXEC div
call :TEST_EXEC mod
call :TEST_EXEC shl
call :TEST_EXEC shr
call :TEST_EXEC inc
call :TEST_EXEC dec
call :TEST_EXEC lt
call :TEST_EXEC le
call :TEST_EXEC lge
call :TEST_EXEC gt
call :TEST_EXEC ge
call :TEST_EXEC eqeq
call :TEST_EXEC neq
call :TEST_EXEC and
call :TEST_EXEC or
call :TEST_EXEC xor
call :TEST_EXEC neg
call :TEST_EXEC not
call :TEST_EXEC push
call :TEST_EXEC store
call :TEST_EXEC call
call :TEST_EXEC mkary
call :TEST_EXEC ret
call :TEST_EXEC haltnop
call :TEST_EXEC trycatch
call :TEST_EXEC fib
goto END

:COMPILE
if "%1"=="" exit /b 0
set OBJ=%1
if not exist %OBJ% timex cl -c -nologo %CFLAGS% src/%OBJ:.obj=.c%
shift
goto COMPILE

:TEST_EXEC
call :MKDOTS %1
set /P _DUMMY=Starting [%1] %DOTS% < NUL
cl /nologo %CFLAGS% /Fetest.exe src/exec/test/%1.c ir_exec.obj ir_util.obj ir_dump.obj allocator.obj allocutil.obj alloccore.obj kstr.obj bign.obj bigz.obj string.obj global.obj loadlib.obj
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

:BUILDLIB
echo %YACC% ...
if "%YACC%"=="kmyacc" (
    set CFLAGS=%CFLAGS% /DYYDEBUG
    kmyacc -vd -b kx -m kmyacc.c.parser -p kx_yy -L c src/kinx.y
) else (
    cl %CFLAGS% /Femyacc.exe utility/myacc.c
    myacc.exe -vd -b kx -y kx_yy -Y KINX_YY src/kinx.y
)
if exist parser.obj del parser.obj
if exist lexer.obj  del lexer.obj
move kx.tab.c src/parser.c
move kx.tab.h include/parser.tab.h
echo timex.exe...
cl /nologo %CFLAGS% /Fetimex.exe timex.c
echo Oniguruma...
pushd src\extlib\onig
call make_win64.bat
copy /y onig.lib ..\..\..\
copy /y onig.dll ..\..\..\
copy /y onig_s.lib ..\..\..\
popd
exit /b

:CLEAN_OBJS
del *.obj *.exe *.lib
pushd src\extlib\onig
call make_win64.bat clean
popd
exit /b

:END
REM del /q kstr.obj bigint.obj ir_dump.obj allocator.obj
REM del /q ir_exec.obj
endlocal
exit /b 0
