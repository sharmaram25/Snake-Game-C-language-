@echo off
setlocal enabledelayedexpansion

echo =======================================================
echo           Setting Up Environment Variables
echo =======================================================
echo.

:: Get the current directory
set "PROJECT_DIR=%~dp0"
set "PROJECT_DIR=%PROJECT_DIR:~0,-1%"

:: Set environment variables for current session
set "CMAKE_DIR=%PROJECT_DIR%\deps\cmake-3.28.3-windows-x86_64"
set "SDL2_DIR=%PROJECT_DIR%\deps\SDL2"
set "SDL2_TTF_DIR=%PROJECT_DIR%\deps\SDL2_ttf"
set "SDL2_MIXER_DIR=%PROJECT_DIR%\deps\SDL2_mixer"

:: Add to PATH for current session
set "PATH=%CMAKE_DIR%\bin;%SDL2_DIR%\lib\x64;%SDL2_TTF_DIR%\lib\x64;%SDL2_MIXER_DIR%\lib\x64;%PATH%"

echo Environment variables set for current session:
echo CMAKE_DIR=%CMAKE_DIR%
echo SDL2_DIR=%SDL2_DIR%
echo SDL2_TTF_DIR=%SDL2_TTF_DIR%
echo SDL2_MIXER_DIR=%SDL2_MIXER_DIR%
echo.

:: Check if libraries exist
if not exist "%SDL2_DIR%" (
    echo ERROR: SDL2 not found! Please run download_sdl.bat first.
    pause
    exit /b 1
)

if not exist "%SDL2_TTF_DIR%" (
    echo ERROR: SDL2_ttf not found! Please run download_sdl.bat first.
    pause
    exit /b 1
)

if not exist "%SDL2_MIXER_DIR%" (
    echo ERROR: SDL2_mixer not found! Please run download_sdl.bat first.
    pause
    exit /b 1
)

echo All SDL2 libraries found successfully!
echo.
echo =======================================================
echo           Environment Setup Complete!
echo =======================================================
echo.
echo You can now run build.bat to compile the game.
echo.
pause
