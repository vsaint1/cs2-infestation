set OBJ_DIR=bin\obj\
set PDB_DOR=bin\Debug
set PREPROCESSORS=/D _DEBUG /D _AMD64_

set ARG=%1

if not exist %OBJ_DIR% mkdir %OBJ_DIR%

for %%a in (driver\*.c) do (
  >> files.rsp echo %%a
)

if %1 == --release (

cl /Fo%OBJ_DIR%  /Fe:%OBJ_DIR%  @files.rsp "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\km\x64\NtosKrnl.lib" /I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km" %PREPROCESSORS% /D NDEBUG /GS- /link /subsystem:native /driver:wdm -entry:driver_entry /out:bin\Release\driver.sys
signtool sign /fd SHA256 bin\Release\driver.sys

)

if %1 == --debug (

cl /Fo%OBJ_DIR%  /Fe:%OBJ_DIR%  @files.rsp "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\km\x64\NtosKrnl.lib" /I "C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\km" %PREPROCESSORS% /Zi /DEBUG  /link /subsystem:native /driver:wdm -entry:driver_entry /out:bin\Debug\driver.sys 
signtool sign /fd SHA256 bin\Debug\driver.sys

)

del files.rsp