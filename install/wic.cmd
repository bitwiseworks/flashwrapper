/* This is a script to start the WarpIn Archive Creator to create a WarpIn file */

'@echo off'

parse arg args

wic_dir = Strip(SysIni('user','WarpIN','Path'),'t','00'x)
if (wic_dir == '') then do
    say 'ERROR: WarpIN is not installed!'
    exit 1
end

old_libpath = SysSetExtLIBPATH(wic_dir,'b')
address 'cmd' wic_dir'\wic.exe' args
old_libpath = SysSetExtLIBPATH(old_libpath,'b')
