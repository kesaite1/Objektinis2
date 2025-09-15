@echo off

rmdir /s /q build >nul 2>&1
mkdir build
cd build
cmake .. -G "MinGW Makefiles" 
cmake --build .

vektoriai\VectorProgram.exe

pause