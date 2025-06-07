@echo off
setlocal enabledelayedexpansion

echo =======================================================
echo        Complete Snake Game Setup and Build
echo =======================================================
echo.
echo This script will:
echo 1. Download SDL2, SDL2_ttf, and SDL2_mixer libraries
echo 2. Set up the development environment
echo 3. Build the Snake Game project
echo 4. Prepare the game for running
echo.
echo Press any key to continue, or Ctrl+C to cancel...
pause >nul
echo.

:: Step 1: Download SDL2 libraries
echo =======================================================
echo Step 1/4: Downloading SDL2 Libraries
echo =======================================================
call download_sdl.bat
if %errorlevel% neq 0 (
    echo Setup failed during SDL2 download!
    pause
    exit /b 1
)

:: Step 2: Set up environment
echo.
echo =======================================================
echo Step 2/4: Setting Up Environment
echo =======================================================
call setup_environment.bat
if %errorlevel% neq 0 (
    echo Setup failed during environment configuration!
    pause
    exit /b 1
)

:: Step 3: Build the project
echo.
echo =======================================================
echo Step 3/4: Building the Project
echo =======================================================
call build.bat
if %errorlevel% neq 0 (
    echo Setup failed during build!
    pause
    exit /b 1
)

:: Step 4: Final setup
echo.
echo =======================================================
echo Step 4/4: Final Setup
echo =======================================================

:: Ensure assets directories exist
if not exist "assets" mkdir assets
if not exist "assets\fonts" mkdir assets\fonts
if not exist "assets\sounds" mkdir assets\sounds

:: Copy assets to build directory
if not exist "build\assets" mkdir build\assets
if not exist "build\assets\fonts" mkdir build\assets\fonts
if not exist "build\assets\sounds" mkdir build\assets\sounds

:: Copy placeholder files if they exist
if exist "assets\fonts\*" xcopy "assets\fonts\*" "build\assets\fonts\" /Y >nul 2>&1
if exist "assets\sounds\*" xcopy "assets\sounds\*" "build\assets\sounds\" /Y >nul 2>&1

echo.
echo =======================================================
echo           Setup Complete Successfully!
echo =======================================================
echo.
echo Your Snake Game is ready to play!
echo.
echo To run the game:
echo   - Double-click run.bat
echo   - Or navigate to the build directory and run SnakeGame.exe
echo.
echo Game Controls:
echo   - Arrow Keys: Move the snake
echo   - ESC: Quit the game
echo   - Space: Pause/Resume (if implemented)
echo.
echo Have fun playing Snake!
echo.
pause
