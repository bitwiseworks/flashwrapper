REM *** VAC++ 3.6 build ***

nmake BUILD_MODE=debug clean
nmake BUILD_MODE=debug
nmake BUILD_MODE=debug install 

nmake BUILD_MODE=release clean
nmake BUILD_MODE=release
nmake BUILD_MODE=release install 
