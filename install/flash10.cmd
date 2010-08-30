
del ..\bin\debug\flash10os2_debug.wpi
wic.exe ..\bin\debug\flash10os2_debug.wpi -a 2 -c"..\bin\debug" npflos2.dll 2 flash10.txt flash10.lic 3 NPSWF32.DLL -s flash10os2_release.wis

del ..\bin\debug\flash10os2_release.wpi
wic.exe ..\bin\debug\flash10os2_release.wpi -a 2 -c"..\bin\release" npflos2.dll 2 flash10.txt flash10.lic 3 NPSWF32.DLL -s flash10os2_release.wis
