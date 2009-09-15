/* $Id: wrap_JNIEnv.cmd,v 1.1.1.1 2003/09/13 01:30:18 bird Exp $
 *
 * Rexx script for generating conversion JNIEnv wrapper code.
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird@anduin.net>
 *
 * All Rights Reserved
 *
 */


/*
 * Arguments.
 */
parse arg sInput sDummy
if (sInput = '' | sDummy <> '') then
do
    say 'Syntax error!'
    say 'syntax: npjnienv <jni.h>'
    say ''
    say 'jni.h is a very normalized version of struct JNINativeInterface_.'
    say 'One line for function pointer and return value.'
    say 'Next line for the parameters, one line only.'
    say ''
    say 'The output is set to stdout.'
    say ''
    exit(12);
end



/*
 * Read the file.
 */
say '/* $Id: wrap_JNIEnv.cmd,v 1.1.1.1 2003/09/13 01:30:18 bird Exp $'
say ' *'
say ' * Autogenerated by npjnienv.cmd from 'sInput'.'
say ' *'
say ' * InnoTek Systemberatung GmbH confidential'
say ' *'
say ' * Copyright (c) 2003 InnoTek Systemberatung GmbH'
say ' * Author: knut st. osmundsen <bird@anduin.net>'
say ' *'
say ' * All Rights Reserved'
say ' *'
say ' */'
iRc = 0;
asStruct.0 = 0;
do while (lines(sInput) <> 0)
    sLine = strip(linein(sInput));
    if (sLine = '') then
        iterate;
    iJNICALL = pos('JNICALL', sLine);
    if (iJNICALL > 0) then
    do
        /*
         * Get the arguments.
         */
        sArguments = strip(linein(sInput));
        if (substr(sArguments, 1, 1) <> '(') then
        do
            say 'input file isn''t normalized!';
            say 'Processing:' sLine;
            say '           ' sArguments;
            iRc = 16;
            leave;
        end

        /*
         * Parse out function name and return value.
         * Remove semicolon from the arguments.
         */
        sFunction = strip(substr(sLine, iJNICALL + 7));
        sFunction = strip(strip(substr(sFunction, 2)), 'T', ')');
        sReturn = strip(left(sLine, iJNICALL - 2));
        sArguments = strip(strip(sArguments, 'T', ';'));

        /*
         * Construct call arguments.
         */
        fHaveEllipses = 0;
        sCallArgs = '';
        sTmp = strip(strip(sArguments, 'L', '('), 'T', ')')||',';
        sPrevVar = '';
        cArgs = 0;
        do while (sTmp <> '')
            iComma = pos(',', sTmp);
            if (iComma <= 0) then
                leave;
            /* get variable name and shorten the stuff left to parse */
            sVar = strip(strip(substr(sTmp, 1, iComma), 'B', ','));
            sTmp = strip(substr(sTmp, iComma), 'L', ',');
            do i = length(sVar) to 1 by -1
                ch = translate(substr(sVar, i, 1));
                if (pos(ch, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_.') <= 0) then
                do
                    sVar = substr(sVar, i + 1);
                    leave;
                end
            end

            if (sCallArgs = '') then
            do
                if (sVar <> 'env') then
                do
                    say '!!!!!!!!! Invalid first parameter to JNI function !!!!!!!!';
                    say 'sVar='sVar;
                    exit(16);
                end
                sCallArgs = 'pEnv->pOrgEnv'
            end
            else if (sVar = '...') then
            do
                sCallArgs = sCallArgs || ', args';
                fHaveEllipses = 1;
                sVarEllipses = sPrevVar;
            end
            else
                sCallArgs = sCallArgs || ', ' || sVar;
            /* stats */
            sPrevVar = sVar;
            cArgs = cArgs + 1;
        end

        sCallFunction = sFunction;
        if (fHaveEllipses) then
            sCallFunction = sFunction||'V';

        /*
         * Generate the line for the conv structure
         */
        i = asStruct.0 + 1;
        asStruct.i = '    (unsigned)npjni_'||sFunction||',';
        asStruct.0 = i;

        /*
         * If custom wrapper Then disable the wrapper code.
         */
        fDisabled = 0
        if (pos(';'sFunction';', ';RegisterNatives;GetJavaVM;') > 0) then
            fDisabled = 1;

        /*
         * Now emit the wrapper code.
         */
        say ''
        say ''
        say ''
        if (fDisabled) then
            say '#ifdef NPDLLJNICALLBACK_ALL'
        say '/**'
        say ' * '||sFunction||' wrapper.'
        say ' * '
        say ' * Prototype:'
        say ' *     '||sLine
        say ' *         '||sArguments
        say ' */'
        if (pos(',', sArguments) > 0) then
            sMyArgs = '(PNPJNIENV pEnv'||substr(sArguments, pos(',', sArguments))
        else
            sMyArgs = '(PNPJNIENV pEnv)';
      if (pos(';'sReturn';', ';jlong;') > 0) then do
        say 'long long __stdcall npjni_'||sFunction||sMyArgs
      end
      else do
        say sReturn||' __stdcall npjni_'||sFunction||sMyArgs
      end
        say '{'
        say '    USHORT selFSOld = pfnODIN_ThreadLeaveOdinContextNested(NULL, FALSE);'
      if (fHaveEllipses) then
      do
        say '    va_list args;'
        say '    va_start(args, '||sVarEllipses||');'
      end
        say '    dprintf(("npJNIEnvWrapper: npjni_'||sFunction||' enter"));'

      if (pos(';'sReturn';', ';jlong;') > 0) then
      do /* 64-bit return value */
        say '    '||sReturn||' llRc = pEnv->pOrgEnv->functions->'||sCallFunction||'('||sCallArgs||');'
        say '#if NO_LONG_LONG'
        say '    dprintf(("npJNIEnvWrapper: npjni_'||sFunction||' leave rc=%x%08x", llRc.hi, llRc.lo));'
        say '    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);'
        say '    return ((long long)llRc.hi << 32) + (long long)llRc.lo;'
        say '#else'
        say '    dprintf(("npJNIEnvWrapper: npjni_'||sFunction||' leave rc=%x%08x", (unsigned)(llRc >> 32), (unsigned)llRc));'
        say '    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);'
        say '    return llRc;'
        say '#endif'
      end
      else if (pos(';'sReturn';', ';jdouble;') > 0) then
      do /* double return value */
        say '    '||sReturn||' rdRc = pEnv->pOrgEnv->functions->'||sCallFunction||'('||sCallArgs||');'
        say '    dprintf(("npJNIEnvWrapper: npjni_'||sFunction||' leave rc=%f", rdRc));'
        say '    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);'
        say '    return rdRc;'
      end
      else if (pos(';'sReturn';', ';void;') <= 0) then
      do /* 32-bit return value */
        say '    '||sReturn||' rc = pEnv->pOrgEnv->functions->'||sCallFunction||'('||sCallArgs||');'
        say '    dprintf(("npJNIEnvWrapper: npjni_'||sFunction||' leave rc=%x", rc));'
        say '    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);'
        say '    return rc;'
      end
      else
      do
        say '    pEnv->pOrgEnv->functions->'||sCallFunction||'('||sCallArgs||');'
        say '    dprintf(("npJNIEnvWrapper: npjni_'||sFunction||' leave"));'
        say '    pfnODIN_ThreadEnterOdinContextNested(NULL, FALSE, selFSOld);'
      end
        say '}'
        if (fDisabled) then
            say '#endif'
    end
    else if (pos('reserved', sLine) > 0) then
    do
        /*
         * Reserved line.
         */
        i = asStruct.0 + 1;
        asStruct.i = '    0, /* '|| sLine || ' */';
        asStruct.0 = i;
    end
end
call stream sInput, 'c', 'close';


/*
 * On success emit the conv array.
 */
if (iRc = 0) then
do
    say ''
    say ''
    say '/**'
    say ' * Conversion structure.'
    say ' */'
    say 'unsigned apfnJNIEnv[] = '
    say '{'
    do i = 1 to asStruct.0
        say  asStruct.i;
    end
    say '    /* add a bunch of blank entries just in case - can''t be too careful... */'
    say '    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,'
    say '    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,'
    say '    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,'
    say '    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0'
    say '};'
    say ''
    say ''
end

exit(iRc);
