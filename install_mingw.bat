@echo off
setlocal enabledelayedexpansion

echo =======================================================
echo         Installing MinGW-w64 C++ Compiler
echo =======================================================
echo.
echo This will download and install MinGW-w64 compiler...
echo.

:: Create deps directory if it doesn't exist
if not exist "deps" mkdir deps
cd deps

:: Download MinGW-w64
echo Downloading MinGW-w64...
curl -L "https://github.com/niXman/mingw-builds-binaries/releases/download/13.2.0-rt_v11-rev1/x86_64-13.2.0-release-posix-seh-ucrt-rt_v11-rev1.7z" -o mingw-w64.7z

if %errorlevel% neq 0 (
    echo Error downloading MinGW-w64. Trying alternative download...
    curl -L "https://sourceforge.net/projects/mingw-w64/files/Toolchains targetting Win64/Personal Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download" -o mingw-w64.7z
    if %errorlevel% neq 0 (
        echo Failed to download MinGW-w64. Please check your internet connection.
        pause
        exit /b 1
    )
)

:: Check if 7z is available
where 7z >nul 2>nul
if %errorlevel% neq 0 (
    echo 7-Zip not found. Downloading portable 7-Zip...
    curl -L "https://www.7-zip.org/a/7za920.zip" -o 7za.zip
    powershell -command "Expand-Archive -Path '7za.zip' -DestinationPath '7zip' -Force"
    set "SEVEN_ZIP=7zip\7za.exe"
) else (
    set "SEVEN_ZIP=7z"
)

:: Extract MinGW-w64
echo Extracting MinGW-w64...
%SEVEN_ZIP% x mingw-w64.7z -y

:: Clean up
del mingw-w64.7z
if exist "7za.zip" del 7za.zip

cd ..

echo.
echo =======================================================
echo         MinGW-w64 Installed Successfully!
echo =======================================================
echo.
echo The compiler has been installed to deps\mingw64\
echo Now you can run build_with_mingw.bat to compile the game.
echo.
pause
