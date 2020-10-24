# PlatformIO GD32F103xx series test

## Description 

Test project for integrating the Standard Peripheral Library (SPL) of GigaDevice GD32F103xx series chips with
PlatformIO. 

## SPL framework package 

This project uses a customly created `framework-spl` version by specifyingg

```ini
[env]
; globally override framework-spl for all environments.
platform_packages = 
    maxgerhardt/framework-spl@2.10300.0
```

in the `platformio.ini`. 

This `framework-spl` version contains `GD32F1x0_Firmware_Library_v3.1.0` (to support htis `GD32F130`) as well as `GD32F10x_Firmware_Library_V2.1.2` (to support e.g., `GD32F103`). 

It is not needed to manually modify `~/.platformio/packages/framework-spl` anymore.


## Supported boards

Only GD32F103RCT6 at the moment. Other boards need a new board definition.

## Exporting for a IDE.

If using VSCoede, just "Open Project" and point to this platformio.ini. Otherwise use the console commands.

```
pio init --ide=<ide>
```

see docs.

## Compilation

If using VSCode, the normal project tasks (Build, Upload, ..) should work as normal. 

From the commandline, use `pio run` and `pio run -t upload` respectively. 


