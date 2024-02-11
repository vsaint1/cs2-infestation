# INFESTATION

Infestation is an open source external Counter-Strike 2 read only kernel-level gameplay enhancer.
- `Infestation` Project name
- `Open Source` This application is open source and for everyone to modify, use or learn from
- `external` We do not inject any DLLs into the target process
- `read only` Currently we do not Write to process memory
- `kernel` Available, but not needed.
 

## Features 

Press `HOME` to open overlay menu.

- AIMBOT
	`FOV`, `TargetHitBox`, `Key selection`, `Visible-Check`, `Humanizer`

- ESP
	`Skeleton`, `Boxes`, `Weapon`,`Distance`,`Name`,`Health`,`Snaplines`
 
-	WORLD
	Weapons
	- `Icon`, `Distance`,`Snaplines`
	
	Grenades
	- `Icon`, `Distance`,`Snaplines`,`Trajectory`,`Timer`

- Misc
	`Team-Check`, `Save FPS`, `Anti-Screencapture`

## References

Check the upcoming features, improvements and upgrades made to `infestation`.

- [TODOS](https://github.com/vsaint1/cs2-infestation/blob/master/TODO.md)
- [LOGS](https://github.com/vsaint1/cs2-infestation/blob/master/CHANGELOG.md)

## How to use ?

- Download the latest release from [here](https://github.com/vsaint1/cs2-infestation)

- Clone the repository
- Open the solution in Visual Studio 2022 v143
- **DISABLE** `Security Check` if loading driver with driver mapper

<img src="./examples/security_check.png">

- Build the project
- Copy the driver to the same folder as the executable
- Load the driver manually with services or driver mapper
- Run the executable
- Press `HOME` to toggle the Menu

## Alternatives

- [Valthrun](https://github.com/Valthrun/Valthrun) - `RUST`

## Disclaimer

I wont support or provide any binaries for this project, you are free to use it as you wish, this is a free project.

