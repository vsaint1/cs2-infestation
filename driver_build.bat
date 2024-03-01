set OBJ_DIR=bin\obj
set ARG=%1

if not exist %OBJ_DIR% mkdir %OBJ_DIR%

for %%a in (driver\*.c) do (
  >> files.rsp echo %%a
)

if %1 == --release (

cl @files.rsp "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\km\x64\NtosKrnl.lib" /I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km" /D NDEBUG /GS- /link /subsystem:native /driver:wdm -entry:driver_entry /out:bin\Release\driver.sys  /Fo%OBJ_DIR%
signtool sign /fd SHA256 bin\Release\driver.sys

)

if %1 == --debug (

cl @files.rsp "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\km\x64\NtosKrnl.lib" /I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km" /Zi /DEBUG  /D _DEBUG /link /subsystem:native /driver:wdm -entry:driver_entry /out:bin\Debug\driver.sys /Fo:%OBJ_DIR%
signtool sign /fd SHA256 bin\Debug\driver.sys

)

del files.rsp