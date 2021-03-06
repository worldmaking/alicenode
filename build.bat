@if "%_echo%"=="" echo off 
@setlocal
SET VSCMD_START_DIR=%cd%
SET VCVARS64=VC\Auxiliary\Build\vcvars64.bat
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\%VCVARS64%" call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\%VCVARS64%"
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\%VCVARS64%" call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\%VCVARS64%"
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\%VCVARS64%" call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\%VCVARS64%"
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\BuildTools\%VCVARS64%" call "%ProgramFiles(x86)%\Microsoft Visual Studio\2017\BuildTools\%VCVARS64%"

rem /WHOLEARCHIVE:lib/win64/freenect2static.lib ^
rem lib/win64/SpoutLibrary.lib "%KINECTSDK20_DIR%\lib\x64\kinect20.lib" 
rem /I "%KINECTSDK20_DIR%\inc"

rem compile & link:
cl /W3 /EHsc /O2  ^
/I include ^
/I include/uv ^
/I include/opencv2 ^
src/alice.cpp ^
/link ^
/MACHINE:X64 ^
/WHOLEARCHIVE:lib/win64/lib-vc2017/glfw3.lib ^
/WHOLEARCHIVE:lib\win64\lib-vc2017\libuv.lib ^
lib/win64/zlib.lib lib/win64/ippicvmt.lib lib/win64/opencv_core320.lib lib/win64/opencv_flann320.lib lib/win64/opencv_calib3d320.lib lib/win64/opencv_imgproc320.lib lib/win64/opencv_features2d320.lib lib/win64/opencv_video320.lib lib/win64/opencv_tracking320.lib ^
lib/win64/libusb-1.0.lib ^
lib/win64/freenect2static.lib ^
 /DYNAMICBASE ^
lib/win64/turbojpeg.lib ^
lib/win64/Leap.lib lib/win64/LeapC.lib ^
lib\win64\openvr_api.lib user32.lib kernel32.lib shell32.lib shlwapi.lib gdi32.lib advapi32.lib iphlpapi.lib ole32.lib oleaut32.lib odbc32.lib odbccp32.lib psapi.lib userenv.lib uuid.lib winspool.lib comdlg32.lib ws2_32.lib opengl32.lib
rem echo Exit Code is %errorlevel% 

rem if compiled OK, run it:
if %errorlevel% neq 0 (
    echo Exit Code is %errorlevel%
) else (
    alice.exe
    echo Exit Code is %errorlevel%
)

@del alice.obj alice.exp



@endlocal