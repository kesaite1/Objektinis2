@echo off


rmdir /s /q build >nul 2>&1
mkdir build
cd build
cmake .. -G "MinGW Makefiles" 
cmake --build .

list\ListProgram.exe

pause