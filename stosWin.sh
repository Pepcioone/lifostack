#!/bin/bash
#Pepcio v1.0

mver=7.3
file=wynik.exe
echo "Win compiler started"
if [ -e $file ]; then rm $file; fi
x86_64-w64-mingw32-g++ stos.cpp -o $file -std=c++11
cp -f /usr/lib/gcc/x86_64-w64-mingw32/${mver}-win32/libgcc_s_seh-1.dll .
cp -f /usr/lib/gcc/x86_64-w64-mingw32/${mver}-win32/libstdc++-6.dll .
strip $file
size $file
echo "Win compiler finished"
exit 0
