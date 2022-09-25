# GearLib

Convert mixing database from a software to another.

## Working
- Rekordbox -> VirtualDJ

## Todo
- VirtualDJ -> Rekordbox
- VirtualDJ -> Serato
- VirtualSJ -> Tracktor
- Rekordbox -> Serato
- Rekordbox -> Tracktor
- Serato -> Rekordbox
- Serato -> Tracktor
- Serato -> VirtualDJ
- Tracktor -> Rekordbox
- Tracktor -> VirtualDJ
- Tracktor -> Serato

# Compile

## Windows
```bash
cd ./build
cmake -G "MinGW Makefiles" ..
make # C:\MinGW\bin\mingw32-make.exe
```

## Unix
```shell
cd ./build
cmake ..
make
```

# Examples

Help:
```bash
GearLib.exe -h
```

Convert a RekordBox Library to a VirtualDJ Library:
```bash
GearLib.exe rekordbox H:\\collection.xml virtualdj H:\\database.xml
```