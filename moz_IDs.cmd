/* $Id: moz_IDs.cmd,v 1.3 2004/03/12 15:50:49 bird Exp $
 *
 * Generate npIDs.h from npIDs.lst
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003-2004 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <knut@innotek.de>
 *
 * All Rights Reserved
 *
 */


/*
 * Read the input
 */
aIDs.0 = 0;
parse arg sIn sDummy
if (sIn = '') then
    sIn = 'moz_IDs_Input.lst';
do while lines(sIn)
    sLine = strip(linein(sIn));
    if (sLine <> '' & left(sLine,1) <> '#' & left(sLine,1) <> ';') then
    do
        i = aIDs.0 + 1;
        aIDs.0 = i;
        parse var sLine aIDs.i.sClass aIDs.i.sDefine aIDs.i.sConst
        if (aIDs.i.sDefine = '') then
        do
            if (left(aIDs.i.sClass, 2) == 'ns') then
                aIDs.i.sDefine = 'NS_'||substr(aIDs.i.sClass, 3)||'_IID';
            else
                aIDs.i.sDefine = 'NS_'||aIDs.i.sClass||'_IID';
            aIDs.i.sDefine = translate(aIDs.i.sDefine);
        end
        if (aIDs.i.sConst = '') then
        do
            if (left(aIDs.i.sClass, 3) == 'nsI') then
                aIDs.i.sConst = 'k'||substr(aIDs.i.sClass, 4)||'IID';
            else if (left(aIDs.i.sClass, 2) == 'ns') then
                aIDs.i.sConst = 'k'||substr(aIDs.i.sClass, 3)||'IID';
            else
                aIDs.i.sConst = 'k'||aIDs.i.sClass||'IID';
        end
    end
end
call stream sIn, 'c', 'close';


/*
 * Make output.
 */
say ''
say '/* $Id: moz_IDs.cmd,v 1.3 2004/03/12 15:50:49 bird Exp $'
say ' *'
say ' * ID constants.'
say ' *'
say ' * InnoTek Systemberatung GmbHconfidential'
say ' *'
say ' * Copyright (c) 2003-2004 InnoTek Systemberatung GmbH'
say ' * Author: knut st. osmundsen <knut@innotek.de>'
say ' *'
say ' * All Rights Reserved'
say ' *'
say ' */'
say ''
say '/*******************************************************************************'
say '*   Defined Constants And Macros                                               *'
say '*******************************************************************************/'
say '#ifndef NP_DEF_ID'
say '#define NP_DEF_ID(_name, _iidspec) extern const nsIID _name'
say '#endif'
say ''
say ''
say '/*******************************************************************************'
say '*   Global Variables                                                           *'
say '*******************************************************************************/'
say '/** @name Component and Interface IDs Constants.'
say ' * @{'
say ' */'
do i = 1 to aIDs.0
    say '#ifdef '||aIDs.i.sDefine
    say 'NP_DEF_ID('||aIDs.i.sConst', '||aIDs.i.sDefine||');'
    say '#endif'
end
say ''
say ''
say ''
say '#ifdef NP_INCL_LOOKUP'
say '/**'
say ' * Lookup list for IIDs and CIDs to get an understandable name.'
say ' */'
say 'static struct nsIDNameLookupEntry'
say '{'
say '    const nsID *    pID;'
say '    const char *    pszName;'
say '}   aIDNameLookup[] ='
say '{'
do i = 1 to aIDs.0
    say '#ifdef '||aIDs.i.sDefine
    say '    { &'||aIDs.i.sConst', "'||aIDs.i.sDefine||'" },'
    say '#endif'
end
say '};'
say ''
say ''
say ''
say '/**'
say ' * Lookup list for IIDs and CIDs to get an understandable name.'
say ' */'
say 'static struct nsLookupStrIDEntry'
say '{'
say '    const nsID *    pID;'
say '    const char *    pszStrID;'
say '}   aIDStrIDLookup[] ='
say '{'
do i = 1 to aIDs.0
    say '#ifdef '||aIDs.i.sDefine||'_STR'
    say '    { &'||aIDs.i.sConst', '||aIDs.i.sDefine||'_STR },'
    say '#endif'
end
say '};'
say '#endif'
say ''

exit(0);
