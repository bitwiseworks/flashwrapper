/* This is a script to start the WarpIn Archive Creator to create a WarpIn file */

wic_dir = Strip(SysIni('user','WarpIN','Path'),'t','00'x)
old = SysSetExtLIBPATH(wic_dir,'b')
Address cmd wic_dir||'\wic.exe -a -U flash_ecs_beta2-release 12 -c12 -r * 13 -c13 -r * -s flash_ecs.wis'
old = SysSetExtLIBPATH(old,'b')
