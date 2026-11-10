@echo off
echo Compiling Map Navigation System...
g++ -std=c++17 main.cpp Graph.cpp MinHeap.cpp -o main.exe
if %ERRORLEVEL% EQU 0 (
    echo Running...
    main.exe
) else (
    echo Compilation failed!
)

