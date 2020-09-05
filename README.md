# PlatformIO GD32F103xx series test

## Description 

Test project for integrating the Standard Peripheral Library (SPL) of GigaDevice GD32F103xx series chips with
PlatformIO. 

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


