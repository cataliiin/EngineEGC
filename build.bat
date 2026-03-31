@echo off
setlocal enabledelayedexpansion

set "COMPILER=C:\msys64\ucrt64\bin\g++.exe"
set "INCLUDE=-I C:\msys64\ucrt64\include -I ./Engine -I ./Engine/Core"
set "LIB_PATH=-L C:\msys64\ucrt64\lib"
set "LIBS=-lfreeglut -lopengl32 -lglu32"
set "OUT=main.exe"

if "%1"=="-s" (
    if exist %OUT% (
        echo [RUN] Skipping build, launching existing %OUT%...
        echo ----------------------------------
        %OUT%
        goto :eof
    )
    echo [INFO] %OUT% not found. Starting mandatory build...
)

set "SOURCES="
for /r %%f in (*.cpp) do (
    set "SOURCES=!SOURCES! "%%f""
)
echo [BUILD] Compiling Engine...
"%COMPILER%" -g !SOURCES! -o %OUT% %INCLUDE% %LIB_PATH% %LIBS% > build_log.txt 2>&1

if %errorlevel% equ 0 (
    echo [SUCCESS] Build finished.
    
    if "%1"=="-r" (
        echo [RUN] Launching...
        echo ----------------------------------
        %OUT%
    )
    if "%1"=="-s" (
        echo [RUN] Launching...
        echo ----------------------------------
        %OUT%
    )
) else (
    echo [ERROR] Compilation failed. Check build_log.txt.
    type build_log.txt
    exit /b %errorlevel%
)

:eof
endlocal