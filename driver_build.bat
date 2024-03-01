set ARG=%1
cd driver

if %1 == --release (

msbuild driver.sln /p:Configuration=Release /p:Platform="x64"


)

if %1 == --debug (

msbuild driver.sln /p:Configuration=Debug /p:Platform="x64"

)
