@echo off
REM Set the source and output directories
set SOURCE_DIR=src
set OUTPUT_DIR=test
set OUTPUT_FILE=my_program

REM Check if the output directory exists; if not, create it
if not exist %OUTPUT_DIR% (
    mkdir %OUTPUT_DIR%
)

REM Initialize an empty variable to collect all .cpp file paths
set FILES=

REM Enable delayed expansion to use the FILES variable within the loop
setlocal enabledelayedexpansion

REM Loop through all .cpp files in the source directory
for %%f in (%SOURCE_DIR%\*.cpp) do (
    set FILES=!FILES! %%f
)

REM Compile all collected .cpp files into a single executable
g++ !FILES! -o "%OUTPUT_DIR%\%OUTPUT_FILE%"

REM Check if the compilation was successful
if errorlevel 1 (
    echo Compilation failed.
    exit /b %errorlevel%
) else (
    echo Successfully compiled all files into %OUTPUT_DIR%\%OUTPUT_FILE%
)

endlocal
