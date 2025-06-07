@echo off
setlocal enabledelayedexpansion

echo =======================================================
echo           SDL2 Libraries Automatic Download
echo =======================================================
echo.

:: Create deps directory if it doesn't exist
if not exist "deps" mkdir deps
cd deps

:: Download SDL2
echo Downloading SDL2 for MinGW...
curl -L "https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-mingw.tar.gz" -o SDL2-devel-2.28.5-mingw.tar.gz
if %errorlevel% neq 0 (
    echo Error downloading SDL2. Please check your internet connection.
    pause
    exit /b 1
)

:: Extract SDL2
echo Extracting SDL2...
powershell -command "Expand-Archive -Path 'SDL2-devel-2.28.5-VC.zip' -DestinationPath '.' -Force"
if exist "SDL2-2.28.5" ren "SDL2-2.28.5" "SDL2"

:: Download SDL2_ttf
echo Downloading SDL2_ttf...
curl -L "https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.20.2/SDL2_ttf-devel-2.20.2-VC.zip" -o SDL2_ttf-devel-2.20.2-VC.zip
if %errorlevel% neq 0 (
    echo Error downloading SDL2_ttf. Please check your internet connection.
    pause
    exit /b 1
)

:: Extract SDL2_ttf
echo Extracting SDL2_ttf...
powershell -command "Expand-Archive -Path 'SDL2_ttf-devel-2.20.2-VC.zip' -DestinationPath '.' -Force"
if exist "SDL2_ttf-2.20.2" ren "SDL2_ttf-2.20.2" "SDL2_ttf"

:: Download SDL2_mixer
echo Downloading SDL2_mixer...
curl -L "https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.6.3/SDL2_mixer-devel-2.6.3-VC.zip" -o SDL2_mixer-devel-2.6.3-VC.zip
if %errorlevel% neq 0 (
    echo Error downloading SDL2_mixer. Please check your internet connection.
    pause
    exit /b 1
)

:: Extract SDL2_mixer
echo Extracting SDL2_mixer...
powershell -command "Expand-Archive -Path 'SDL2_mixer-devel-2.6.3-VC.zip' -DestinationPath '.' -Force"
if exist "SDL2_mixer-2.6.3" ren "SDL2_mixer-2.6.3" "SDL2_mixer"

:: Clean up zip files
echo Cleaning up...
del SDL2-devel-2.28.5-VC.zip
del SDL2_ttf-devel-2.20.2-VC.zip
del SDL2_mixer-devel-2.6.3-VC.zip

cd ..

echo.
echo =======================================================
echo            SDL2 Libraries Downloaded Successfully!
echo =======================================================
echo.
echo Next steps:
echo 1. Run setup_environment.bat to configure environment variables
echo 2. Run build.bat to compile the game
echo 3. Run run.bat to play the game
echo.
pause
