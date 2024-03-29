# INFESTATION ![Codecov](https://img.shields.io/codecov/c/github/vsaint1/cs2-infestation) ![GitHub commit activity](https://img.shields.io/github/commit-activity/t/vsaint1/cs2-infestation)


Infestation is an open source external Counter-Strike 2 read only kernel-level gameplay enhancer.
- `Infestation` Project name
- `Open Source` This application is open source and for everyone to modify, use or learn from
- `External` We do not inject any DLLs into the target process
- `Read only` Currently we do not Write to process memory
- `Kernel` Development.
 
## References

Check the upcoming features, improvements and upgrades made to `infestation`.

- [TODOS](https://github.com/vsaint1/cs2-infestation/blob/master/TODO.md)
- [LOGS](https://github.com/vsaint1/cs2-infestation/blob/master/CHANGELOG.md)

## Requirements

- [WDK   - Driver](https://learn.microsoft.com/windows-hardware/drivers/download-the-wdk)
- [MSVC  - Compiler](https://visualstudio.microsoft.com/vs/features/cplusplus/)
- [Conan - Dependency management](https://conan.io/center)
- [Cmake - Build System](https://cmake.org/)

## Building from source

> [!WARNING]  
> Run as admin the the following commands

FLAGS

DESCRIPTION | VALUE

- Release mode --release
- Debug mode --debug

```bash
# clone
$ git clone https://github.com/vsaint1/cs2-infestation.git


# windows 

# user
$ ./windows_build.bat --FLAGS

# kernel
$ ./driver_build.bat --FLAGS

# linux

$ ./linux_build.sh

```

## How to use ?

- Download the latest release from [here](https://github.com/vsaint1/cs2-infestation)

## Alternatives

- [Valthrun](https://github.com/Valthrun/Valthrun) - `RUST`

## Disclaimer

I wont support or provide any binaries for this project, you are free to use it as you wish, this is a free project.
