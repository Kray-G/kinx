@echo off

SET CFLAGS=/O2 /MT /Iinclude
cl %CFLAGS% /Femyacc.exe utility/myacc.c

myacc.exe -vd -b kx -y kx_yy -Y KINX_YY src/kinx.y
REM kmyacc -v -b kx -m kmyacc.c.parser -p kx_yy -L c src/kinx.y
move kx.tab.c src/parser.c
move kx.tab.h include/parser.tab.h

cl %CFLAGS% /Fekinx.exe src/string.c src/parser.c src/lexer.c src/ast_object.c src/ast_display.c src/ast_analyzer.c src/ast_gencode.c src/ir_fix.c src/ir_dump.c src/vector.c src/main.c
REM cl /DYYDEBUG %CFLAGS% /Fekinx.exe src/parser.c src/lexer.c src/ast_object.c src/ast_display.c src/vector.c src/main.c

del /q *.obj
