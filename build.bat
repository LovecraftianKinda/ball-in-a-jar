@echo off
gcc main.c -o jar.exe -I"include" -L"lib" -lraylib -lopengl32 -lgdi32 -lwinmm
if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b %errorlevel%
)
echo Compilation successful! Running...
jar.exe