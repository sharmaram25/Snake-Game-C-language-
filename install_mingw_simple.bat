@echo off
setlocal enabledelayedexpansion

echo =======================================================
echo      Quick MinGW-w64 Setup (WinLibs Distribution)
echo =======================================================
echo.

:: Create deps directory if it doesn't exist
if not exist "deps" mkdir deps
cd deps

:: Download WinLibs MinGW-w64 (smaller, zip format)
echo Downloading WinLibs MinGW-w64...
curl -L "https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0-16.0.6-11.0.0-ucrt-r1/winlibs-x86_64-posix-seh-gcc-13.2.0-mingw-w64ucrt-11.0.0-r1.zip" -o mingw-winlibs.zip

if %errorlevel% neq 0 (
    echo Error downloading MinGW-w64. Please check your internet connection.
    pause
    exit /b 1
)

:: Extract using PowerShell
echo Extracting MinGW-w64...
powershell -command "Expand-Archive -Path 'mingw-winlibs.zip' -DestinationPath '.' -Force"

:: Rename the extracted folder to mingw64 for consistency
if exist "mingw64" rmdir /s /q mingw64
ren "mingw64" mingw64_temp 2>nul
for /d %%i in (mingw*) do (
    if not "%%i"=="mingw-winlibs.zip" (
        ren "%%i" mingw64
        goto :found
    )
)
:found

:: Clean up
del mingw-winlibs.zip

cd ..

echo.
echo =======================================================
echo       MinGW-w64 Installed Successfully!
echo =======================================================
echo.
echo The compiler has been installed to deps\mingw64\
echo Now you can run build_with_mingw.bat to compile the game.
echo.
pause
