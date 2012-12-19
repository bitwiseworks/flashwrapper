/* This is a script to start the WarpIn Archive Creator to create a WarpIn file */

'@echo off'

'mkdir 12'
'xcopy eula.pdf 12\'
'xcopy flash.lic 12\'
'xcopy flash.txt 12\'
'xcopy npflos2.dll 12\'

'mkdir 13'
'xcopy NPSWF32.dll 13\'

wic_dir = Strip(SysIni('user','WarpIN','Path'),'t','00'x)
old = SysSetExtLIBPATH(wic_dir,'b')
Address cmd wic_dir||'\wic.exe -a -U flash_ecs_ga-release 12 -c12 -r * 13 -c13 -r * -s flash_ecs.wis'
old = SysSetExtLIBPATH(old,'b')
