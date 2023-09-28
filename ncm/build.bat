@echo off
rem SCRIPT TO RECOMPILE NCM.EXE
set PATH=C:\Program Files\mingw-w64\x86_64-6.3.0-posix-seh-rt_v5-rev2\mingw64\bin;%PATH%
rem set PATH=C:\Users\nikita\Documents\tools\x86_64-6.2.0-release-win32-seh-rt_v5-rev1\mingw64\bin;%PATH%
set cflags= -O2 -fno-stack-protector -fomit-frame-pointer -fno-exceptions -fno-unwind-tables -fno-ident -Wno-return-type -Wno-pointer-sign -D WINDOWS
rem -fno-asynchronous-unwind-tables -nostartfiles -e run 
gcc  %cflags% -s -O2 src/main.c -o ./ncm.exe
