@echo off
setlocal

set YACC=myacc
REM set CFLAGS=/O2 /D_DEBUG /MTd /Iinclude
REM set CFLAGS=/O2 /MT /Iinclude /DKX_LEX_DEBUG
set CFLAGS=/O2 /MT /Iinclude /Isrc/jit
set OBJS=src/allocator.obj src/alloccore.obj src/allocutil.obj src/ast_analyzer.obj src/ast_display.obj src/ast_gencode.obj src/ast_object.obj src/ast_native.obj src/bign.obj src/bigz.obj src/getopt.obj src/global.obj src/ir_dump.obj src/ir_exec.obj src/ir_fix.obj src/ir_util.obj src/ir_aotcore.obj src/ir_aotdump.obj src/ir_natutil.obj src/nir_compile.obj src/nir_dump.obj src/kstr.obj src/lexer.obj src/fileutil.obj src/loadlib.obj src/parser.obj src/format.obj src/string.obj src/extlib/kc-json/kc-json.obj src/disasm/dis.obj src/disasm/disas.obj src/disasm/dss.obj src/disasm/lex.obj src/disasm/sym.obj src/disasm/arch/arm/aload.obj src/disasm/arch/arm/arm.obj src/disasm/arch/arm/astrings.obj src/disasm/arch/mips/mips.obj src/disasm/arch/mips/mload.obj src/disasm/arch/mips/mstrings.obj src/disasm/arch/x86/x86.obj src/disasm/arch/x86/x86asm.obj src/disasm/arch/x86/x86load.obj src/disasm/arch/x86/x86strings.obj src/disasm/common/file.obj src/disasm/common/table.obj src/disasm/common/trie.obj

call :BUILDLIB
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

:TEST_EXEC
call :MKDOTS %1
set /P _DUMMY=Starting [%1] %DOTS% < NUL
cl /nologo %CFLAGS% /Fetest.exe src/exec/test/%1.c %OBJS%
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
nmake -f Makefile.msc
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
