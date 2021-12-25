REM delete previous files
DEL PlayingSoundsInGBDK.gb

REM compile .c files into .o files
C:\gbdk\bin\lcc -c -o main.o main.c
C:\gbdk\bin\lcc -c -o SimpleSprite.o SimpleSprite.c

REM Compile a .gb file from the compiled .o files
C:\GBDK\bin\lcc  -o PlayingSoundsInGBDK.gb main.o SimpleSprite.o

REM delete intermediate files created for the conmpilation process
DEL *.asm
DEL *.lst
DEL *.ihx
DEL *.sym
DEL *.o
