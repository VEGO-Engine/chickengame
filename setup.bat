curl -L -o Tiled-1.11.2_Windows-10+_x86_64.msi https://github.com/mapeditor/tiled/releases/download/v1.11.2/Tiled-1.11.2_Windows-10+_x86_64.msi

mkdir vego\bin
mkdir vego\downloads
mkdir vego\engine

TODO add release download link for template release

curl -L -o vego\downloads\x86_64-14.2.0-release-win32-seh-ucrt-rt_v12-rev2.7z https://github.com/niXman/mingw-builds-binaries/releases/download/14.2.0-rt_v12-rev2/x86_64-14.2.0-release-win32-seh-ucrt-rt_v12-rev2.7z
curl -L -o vego\downloads\cmake-4.0.0-rc4.zip https://github.com/Kitware/CMake/releases/download/v4.0.0-rc4/cmake-4.0.0-rc4.zip

7z >nul 2>&1
IF ERRORLEVEL 1 (
    echo 7z not found, downloading 7zr.exe...
    curl -L -o vego\bin\7zr.exe https://www.7-zip.org/a/7zr.exe
)

vego\bin\7zr.exe x vego\downloads\x86_64-14.2.0-release-win32-seh-ucrt-rt_v12-rev2.7z -o vego\bin
vego\bin\7zr.exe x vego\downloads\cmake-4.0.0-rc4.zip -o vego\bin

echo Setup completed successfully!
