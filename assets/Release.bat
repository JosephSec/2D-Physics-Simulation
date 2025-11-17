@echo off

set LIBFOLDER=release\libs
set ASSETS=release\assets


if not exist "release" (mkdir "release")
if not exist "%LIBFOLDER%"  (mkdir "%LIBFOLDER%")
if not exist "%ASSETS%"     (mkdir "%ASSETS%")

copy "c:\msys64\mingw64\bin\libgcc_s_seh-1.dll"  "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libstdc++-6.dll"     "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libfreetype-6.dll"   "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libwinpthread-1.dll" "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libbrotlidec.dll"    "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libbz2-1.dll"        "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libharfbuzz-0.dll"   "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libpng16-16.dll"     "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\zlib1.dll"           "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libbrotlicommon.dll" "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libglib-2.0-0.dll"   "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libgraphite2.dll"    "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libintl-8.dll"       "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libpcre2-8-0.dll"    "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libiconv-2.dll"      "%LIBFOLDER%"

copy "c:\msys64\mingw64\bin\libsfml-system-3.dll"     "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libsfml-window-3.dll"     "%LIBFOLDER%"
copy "c:\msys64\mingw64\bin\libsfml-graphics-3.dll"   "%LIBFOLDER%"
:: copy "c:\msys64\mingw64\bin\libsfml-audio-3.dll"   "%LIBFOLDER%"
:: copy "c:\msys64\mingw64\bin\libsfml-network-3.dll" "%LIBFOLDER%"

copy "c:\msys64\mingw64\lib\libsfml-system.dll.a"     "%LIBFOLDER%"
copy "c:\msys64\mingw64\lib\libsfml-window.dll.a"     "%LIBFOLDER%"
copy "c:\msys64\mingw64\lib\libsfml-graphics.dll.a"   "%LIBFOLDER%"
:: copy "c:\msys64\mingw64\lib\libsfml-audio.dll.a"   "%LIBFOLDER%"
:: copy "c:\msys64\mingw64\lib\libsfml-network.dll.a" "%LIBFOLDER%"


copy assets\Icon.png "%ASSETS%"
copy assets\Roboto.ttf "%ASSETS%"
copy build\UI.dll "%ASSETS%"
copy build\program.exe "%ASSETS%"

copy assets\Launch.bat  "release"
copy assets\README.txt "release"

echo finished copying files to "release"