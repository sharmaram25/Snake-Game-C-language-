@echo off
setlocal enabledelayedexpansion

echo =======================================================
echo                Building Snake Game
echo =======================================================
echo.

:: Get the current directory
set "PROJECT_DIR=%~dp0"
set "PROJECT_DIR=%PROJECT_DIR:~0,-1%"

:: Set environment variables
set "CMAKE_DIR=%PROJECT_DIR%\deps\cmake-3.28.3-windows-x86_64"
set "SDL2_DIR=%PROJECT_DIR%\deps\SDL2"
set "SDL2_TTF_DIR=%PROJECT_DIR%\deps\SDL2_ttf"
set "SDL2_MIXER_DIR=%PROJECT_DIR%\deps\SDL2_mixer"

:: Add to PATH
set "PATH=%CMAKE_DIR%\bin;%SDL2_DIR%\lib\x64;%SDL2_TTF_DIR%\lib\x64;%SDL2_MIXER_DIR%\lib\x64;%PATH%"

:: Check if SDL2 libraries exist
if not exist "%SDL2_DIR%" (
    echo ERROR: SDL2 libraries not found!
    echo Please run download_sdl.bat first to download SDL2 libraries.
    pause
    exit /b 1
)

:: Create build directory if it doesn't exist
if not exist "build" mkdir build

:: Change to build directory
cd build

echo Configuring with CMake...
:: Configure with CMake, specifying SDL2 paths
cmake .. -DCMAKE_PREFIX_PATH="%SDL2_DIR%;%SDL2_TTF_DIR%;%SDL2_MIXER_DIR%" -DSDL2_DIR="%SDL2_DIR%" -DSDL2_TTF_DIR="%SDL2_TTF_DIR%" -DSDL2_MIXER_DIR="%SDL2_MIXER_DIR%"

if %errorlevel% neq 0 (
    echo CMake configuration failed!
    cd ..
    pause
    exit /b 1
)

echo Building the project...
:: Build the project
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo Build failed!
    cd ..
    pause
    exit /b 1
)

:: Return to project root
cd ..

:: Copy DLLs to build directory
echo Copying required DLLs...
copy "%SDL2_DIR%\lib\x64\SDL2.dll" "build\Release\" >nul 2>&1
copy "%SDL2_DIR%\lib\x64\SDL2.dll" "build\" >nul 2>&1
copy "%SDL2_TTF_DIR%\lib\x64\SDL2_ttf.dll" "build\Release\" >nul 2>&1
copy "%SDL2_TTF_DIR%\lib\x64\SDL2_ttf.dll" "build\" >nul 2>&1
copy "%SDL2_MIXER_DIR%\lib\x64\SDL2_mixer.dll" "build\Release\" >nul 2>&1
copy "%SDL2_MIXER_DIR%\lib\x64\SDL2_mixer.dll" "build\" >nul 2>&1

echo.
echo =======================================================
echo            Build Complete Successfully!
echo =======================================================
echo.
echo Run 'run.bat' to play the Snake Game!
echo.
pause
