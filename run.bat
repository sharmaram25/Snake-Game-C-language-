@echo off
setlocal enabledelayedexpansion

echo =======================================================
echo                 Starting Snake Game
echo =======================================================
echo.

:: Set up paths
set "PROJECT_DIR=%~dp0"
set "PROJECT_DIR=%PROJECT_DIR:~0,-1%"
set "SDL2_DIR=%PROJECT_DIR%\deps\SDL2"
set "SDL2_TTF_DIR=%PROJECT_DIR%\deps\SDL2_ttf"
set "SDL2_MIXER_DIR=%PROJECT_DIR%\deps\SDL2_mixer"

:: Add DLL paths to PATH
set "PATH=%SDL2_DIR%\lib\x64;%SDL2_TTF_DIR%\lib\x64;%SDL2_MIXER_DIR%\lib\x64;%PATH%"

:: Look for the game executable
set GAME_EXE=
if exist "build\Release\SnakeGame.exe" (
    set GAME_EXE=build\Release\SnakeGame.exe
) else if exist "build\SnakeGame.exe" (
    set GAME_EXE=build\SnakeGame.exe
) else (
    echo ERROR: Game executable not found!
    echo.
    echo Please build the game first:
    echo 1. Run setup_complete.bat for full setup, or
    echo 2. Run build.bat to build the project
    echo.
    pause
    exit /b 1
)

echo Starting Snake Game...
echo Executable: %GAME_EXE%
echo.

:: Change to the directory containing the executable
cd "%~dp0"

:: Run the game
%GAME_EXE%

if %ERRORLEVEL% neq 0 (
    echo.
    echo Game exited with error code %ERRORLEVEL%
    echo This might indicate a missing DLL or other issue.
) else (
    echo.
    echo Thanks for playing Snake!
)

echo.
pause
