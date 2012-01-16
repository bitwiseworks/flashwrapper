/* REXX */

'@echo off'

parse arg '['aOutFile'] ['aVersion'] ['aBuild']'

parse var aVersion maj'.'min'.'patch
if (maj = '' | min = '' | verify(aVersion, '1234567890.') \= 0) then do
    say 'GetVerInfo.cmd: ERROR: "'aVersion'" is not a valid version number.'
    exit 1
end
if (maj < 0 | maj > 127 | min < 0 | min > 127) then do
    say 'GetVerInfo.cmd: ERROR: "'aVersion'": version numbers must be 0 to 127.'
    exit 1
end

mozVersion = maj','min
if (patch = '') then do
    mozVersion = mozVersion',0,0'
end
else do
    parse var patch p1'.'p2
    if (p1 < 0 | p1 > 127 | (p2 \= '' & (p2 < 0 | p2 > 127))) then do
        say 'GetVerInfo.cmd: ERROR: "'aVersion'": version numbers must be 0 to 127.'
        exit 1
    end
    if (p2 = '') then mozVersion = mozVersion','p1',0'
    else mozVersion = mozVersion','p1','p2
end

build = ''
if (aBuild \= '') then
    build = ' 'aBuild

mozBuild = build' ('aVersion')'

'call BldLevelInf.cmd' aOutFile '-V"'maj'.'min'" -M"'patch'"',
    '-N"Mensys BV" -D"NPFLOS2 - Shockwave Flash Wrapper'build'" -L"en"'

call lineout aOutFile, 'RCDATA NP_INFO_ProductVersion { 'mozVersion' }'
call lineout aOutFile, 'RCDATA NP_INFO_FileVersion { 'mozVersion' }'

/*
 * NOTE: there is a JS script used on many sites to detect the Flash version
 * (http://code.google.com/p/swfobject/) which uses a silly method of parsing
 * the file description field for that. So we have to emulate the description
 * string of the real Flash plugin to trick this script and make it happy.
 *
 * The proper description should have been this:
 *
 *   call lineout aOutFile, 'RCDATA NP_INFO_FileDescription { "Shockwave Flash Wrapper for OS/2'mozBuild'\0" }'
 */
call lineout aOutFile, 'RCDATA NP_INFO_FileDescription { "Shockwave Flash 10.0 r45\0" }'

call lineout aOutFile
