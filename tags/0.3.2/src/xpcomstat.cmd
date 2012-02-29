/* $Id: xpcomstat.cmd,v 1.2 2003/09/16 08:51:47 bird Exp $
 *
 * Wrapper status generator.
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird-srcspam@anduin.net>
 *
 * All Rights Reserved
 *
 */
/* todo load RexxUtil */
sFile = 'xpcomstat.log';
Address CMD'@echo off'


call SysFileDelete sFile;

call lineout sFile, 'Used UP wrappers'
call lineout sFile, '----------------'
call lineout sFile
Address CMD 'sed -e "/=.*upCreateWrapper[[:blank:]]*(/!d" -e "s/[[:blank:]]*//g" -e "s/.*,\(.*\),.*/\1/" -e "/^k/!d" wrap_XPCOM.cpp | sort -u > 'sFile'.upuse';
Address CMD 'type 'sFile'.upuse >>' sFile;

call lineout sFile, ''
call lineout sFile, 'Implemented UP wrappers'
call lineout sFile, '-----------------------'
call lineout sFile
Address CMD 'sed -e "/[[:blank:]]*&k.*,/!d" -e "/}/d" -e "s/[[:blank:]]*//g" -e "s/&//" -e "s/,//" wrap_XPCOM.cpp | sort > 'sFile'.upimp';
Address CMD 'type 'sFile'.upimp >>' sFile;

call lineout sFile, ''
call lineout sFile, 'Todo UP wrappers'
call lineout sFile, '----------------'
do while (lines(sFile'.upuse'))
    sIID = strip(linein(sFile'.upuse'));
    if (sIID = '') then
        iterate;

    Address CMD 'grep -q -w "'sIID'" 'sFile'.upimp';
    if (rc <> 0) then
        call lineout sFile, sIID;
end
call stream sFile'.upuse', 'c', 'close';

call lineout sFile, ''
call lineout sFile, 'Supported / Create Mismatches'
call lineout sFile, '-----------------------------'
call lineout sFile, ''
call lineout sFile
Address CMD 'sed -e "/pWrapper[[:blank:]]*=[[:blank:]]*new[[:blank:]]*Up/!d" -e "s/.*Up\(.*\)(.*/k\1IID/" -e "s/ //g" wrap_XPCOM.cpp | sort -u >' sFile'.upcreate';
Address CMD 'cat ' sFile'.upcreate' sFile'.upimp | sort | uniq -u >>' sFile;


call lineout sFile, ''
call lineout sFile, ''
call lineout sFile, ''


call lineout sFile, 'Used DOWN wrappers'
call lineout sFile, '------------------'
call lineout sFile
Address CMD 'sed -e "/=.*down.*[[:blank:]]*(/!d" -e "/downCreateWrapper/s/.*(.*,\(.*\),.*/\1/" -e "/downIsSupportedInterface/s/.*(\(.*\)).*/\1/" -e "s/ //g" -e "/^k/!d"  wrap_XPCOM.cpp | sort -u > 'sFile'.downuse';
Address CMD 'type 'sFile'.downuse >>' sFile;

call lineout sFile, ''
call lineout sFile, 'Implemented DOWN wrappers'
call lineout sFile, '-------------------------'
call lineout sFile
Address CMD 'sed -e "/[[:blank:]]*&k.*,/!d" -e "/}/!d" -e "s/[[:blank:]]*//g" -e "s/.*{&\(.*\),&.*/\1/" wrap_XPCOM.cpp | sort > 'sFile'.downimp';
Address CMD 'type 'sFile'.downimp >>' sFile;

call lineout sFile, ''
call lineout sFile, 'Todo DOWN wrappers'
call lineout sFile, '------------------'
do while (lines(sFile'.downuse'))
    sIID = strip(linein(sFile'.downuse'));
    if (sIID = '') then
        iterate;

    Address CMD 'grep -q -w "'sIID'" 'sFile'.downimp';
    if (rc <> 0) then
        call lineout sFile, sIID;
end
call stream sFile'.downuse', 'c', 'close';

call SysFileDelete sFile'.upuse';
call SysFileDelete sFile'.upimp';
call SysFileDelete sFile'.upcreate';
call SysFileDelete sFile'.downuse';
call SysFileDelete sFile'.downimp';
