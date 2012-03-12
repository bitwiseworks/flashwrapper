/* $Id: PreProcess.cmd,v 1.1 2003/09/16 08:44:40 bird Exp $
 *
 * PreProcessor which removes innotek only code.
 *
 * InnoTek Systemberatung GmbH confidential
 *
 * Copyright (c) 2003 InnoTek Systemberatung GmbH
 * Author: knut st. osmundsen <bird@anduin.net>
 *
 * All Rights Reserved
 *
 */
signal on novalue name NoValueHandler
Address CMD '@echo off'

/*
 * Globals.
 */
sMagicWord = 'NPODIN';
sGlobals   = 'sMagicWord sGlobals'


/*
 * Parse arguments
 */
parse arg sArgs
sArgs = strip(sArgs);
do while (sArgs <> '')
    /*
     * Exctract the first word.
     */
    ch = left(sArgs, 1);
    if (pos(ch, '"''`') > 0) then
    do  /* quoted */
        iEndQuote = pos(ch, sArgs, 2);
        if (iEndQuote <= 0) then
        do
            say 'error: invalid quoting!'
            exit(8);
        end
        if (iEndQuote > 2) then
            sArg = substr(sArgs, 2, iEndQuote - 2);
        else
            sArg = '';
        sArgs = strip(substr(sArgs, iEndQuote + 1));
    end
    else
    do
        sArg = word(sArgs, 1);
        sArgs = strip(substr(sArgs, length(sArg) + 1));
    end

    /* process it */
    sName = filespec('name', sArg);
    sExt = ''
    iExt = lastpos('.', sName);
    if (iExt > 1) then
        sExt = translate(substr(sName, iExt + 1));
    iRc = doit(sArg, sExt);
    if (iRc <> 0) then
    do
        call lineout 'STDERR', 'error: failed with rc='iRc;
        exit iRc;
    end
end /* argument loop */


exit 0;



/**
 * Processes the file and prints it to stdout.
 *
 * @returns 0 on success.
 * @returns 8 or higher on error.
 * @param   sFile   The filename.
 * @param   sExt    Uppercased extension if any.
 */
doit: procedure expose(sGlobals)
parse arg sFile, sExt

    /*
     * Stack of if/else/endif stuff.
     *
     *      .sType  -  Type of action: 'INC', '!INC' or 'ignore'.
     *      .sStmt  -  Statement:      'if' or 'else'.
     */
    Stack.0 = 0;
    iStack  = 0;                        /* stack index (we don't use Stack.0) */


    /*
     * Characteristics for this extension.
     */
    fPrefix = 1;                        /* have prefix */
    chPrefix = '#';                     /* this is the prefix */
    fPrefixBlanks = 1;                  /* blanks allowed between prefix and expr */
    fCaseSensitive = 1;                 /* whether or not the statement is case sensitive or not. */

    if (sExt = 'MAK' | sExt = 'MK' | sExt = '') then
    do  /* makefile */
        fPrefixBlanks = 0;
        chPrefix = '!';
        fCaseSensitive = 0;
    end
    else if (sExt = 'ASM') then
    do  /* intel assembly */
        fPrefix = 0;
        fCaseSensitive = 0;
    end


    /*
     * Process the file line by line!
     */
    sRc = stream(sFile, 'c', 'open read');
    if (pos('READY', sRc) <> 1) then
    do
        call lineout 'STDERR', 'error: Failed to open file '''sFile''', sRc='''sRc'''.';
        return 8;
    end

    fPrinting = 1;
    fInINC = 0;
    iRc = 0;
    iLine = 0;
    do while (lines(sFile) > 0)
        sLine = linein(sFile);
        iLine = iLine + 1;

        fGiveup = 0;
        sTmp = strip(translate(sLine, ' ', X2C('9')));
        /* check prefix */
        if (fPrefix) then
        do
            if (left(sTmp, 1) <> chPrefix) then
                fGiveup = 1;
            else
            do
                sTmp = substr(sTmp, 2);
                if (fPrefixBlanks) then
                    sTmp = strip(sTmp);
            end
        end

        /* check for statement */
        if (\fGiveup) then
        do
            s1 = word(sTmp, 1);
            if (\fCaseSensitive) then
                s1 = tolower(s1);
            select
                when (s1 = 'if') then
                do
                    iStack = iStack + 1;
                    Stack.iStack.sType = doexpr(sTmp, 0, 0);
                    Stack.iStack.sStmt = 'if';
                end

                when (s1 = 'ifdef') then
                do
                    iStack = iStack + 1;
                    Stack.iStack.sType = doexpr(sTmp, 1, 0);
                    Stack.iStack.sStmt = 'if';
                end

                when (s1 = 'ifndef') then
                do
                    iStack = iStack + 1;
                    Stack.iStack.sType = doexpr(sTmp, 1, 1);
                    Stack.iStack.sStmt = 'if';
                end

                when (s1 = 'elif' | s1 = 'elseif') then
                do
                    if (iStack <= 0 | Stack.iStack.sStmt <> 'if') then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: el(se)if without if!';
                        iRc = 8;
                        leave;
                    end
                    if (pos('INC', Stack.iStack.sType) > 0 |,
                        pos('INC', doexpr(sTmp, 0, 0)) > 0) then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: we don''t support elseif expressions!';
                        iRc = 8;
                        leave;
                    end

                    Stack.iStack.sType = 'unknown';
                    Stack.iStack.sStmt = 'if';
                end

                when (s1 = 'elifdef' | s1 = 'elseifdef') then
                do
                    if (iStack <= 0 | Stack.iStack.sStmt <> 'if') then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: el(se)ifdef without if!';
                        iRc = 8;
                        leave;
                    end
                    if (pos('INC', Stack.iStack.sType) > 0 |,
                        pos('INC', doexpr(sTmp, 0, 0)) > 0) then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: we don''t support elseif expressions!';
                        iRc = 8;
                        leave;
                    end
                    Stack.iStack.sType = 'unknown';
                    Stack.iStack.sStmt = 'if';
                end

                when (s1 = 'elifndef' | s1 = 'elseifndef') then
                do
                    if (iStack <= 0 | Stack.iStack.sStmt <> 'if') then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: el(se)ifndef without if!';
                        iRc = 8;
                        leave;
                    end
                    if (pos('INC', Stack.iStack.sType) > 0 |,
                        pos('INC', doexpr(sTmp, 0, 0)) > 0) then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: we don''t support elseif expressions!';
                        iRc = 8;
                        leave;
                    end
                    Stack.iStack.sType = 'unknown';
                    Stack.iStack.sStmt = 'if';
                end

                when (s1 = 'else') then
                do
                    if (iStack <= 0 | Stack.iStack.sStmt <> 'if') then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: else without if!';
                        iRc = 8;
                        leave;
                    end
                    Stack.iStack.sStmt = 'else';

                    if (pos('INC', Stack.iStack.sType) > 0) then
                    do
                        if (left(Stack.iStack.sType, 1) = '!') then
                            fPrinting = 1;
                        else
                            fPrinting = 0;
                        iterate;        /* we skip this statement. */
                    end
                    fGiveup = 1;
                end

                when (s1 = 'endif') then
                do
                    if (iStack <= 0) then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: endif without if!';
                        iRc = 8;
                        leave;
                    end

                    if (pos('INC', Stack.iStack.sType) > 0) then
                    do
                        iStack = iStack - 1;
                        fPrinting = 1;
                        fInINC = 0;
                        iterate /* we don't print this statement. */
                    end
                    iStack = iStack - 1;
                    fGiveup = 1;
                end

                otherwise
                    fGiveup = 1;
            end

            /* handle ifs */
            if (\fGiveup) then
            do
                if (pos('error', Stack.iStack.sType) > 0) then
                do
                    call lineout 'STDERR', sFile'('iLine') : error!';
                    iRc = 8;
                    leave;
                end

                if (pos('INC', Stack.iStack.sType) > 0) then
                do
                    if (fInINC) then
                    do
                        call lineout 'STDERR', sFile'('iLine') : error: Nested test no supported!';
                        iRc = 8;
                        leave;
                    end
                    fInINC = 1;
                    if (left(Stack.iStack.sType, 1) = '!') then
                        fPrinting = 0;
                    else
                        fPrinting = 1;
                    iterate;        /* we skip this statement. */
                end
            end
        end

        /* if we got here it means print the line */
        if (fPrinting) then
            say sLine;
    end /* read loop */

    call stream sFile, 'c', 'close';
return iRc;


/**
 * Figure out what type of test this is.
 *
 * @returns 'unknown'   If something we don't care about.
 * @returns 'INC'       If magic true test.
 * @returns '!INC'      If magic false test.
 * @returns 'errorINC'  on error in the test.
 * @param   sExpr       The expressision.
 * @param   fDef        implicit defined().
 * @param   fNeg        implicit negation.
 */
doexpr: procedure expose(sGlobals)
parse arg sExpr, fDef, fNeg
    sExpr = strip(substr(sExpr, length(word(sExpr, 1)) + 1));

    /*
     * Just do very simple checking.
     */
    iPos = pos(sMagicWord, sExpr);
    if (iPos > 0) then
    do  /* not for now.
        if (iPos > 1) then
        do
            if (pos(substr(sExpr, iPos - 1, 1), '(! ') <= 0) then
                return 'unknown';       /* part of bigger word */
        end

        if (iPos + length(sMagicWord) < length(sExpr)) then
        do
            if (pos(substr(sExpr, iPos + length(sMagicWord), 1), ');/ ') <= 0) then /* ; and / are comments */
                return 'unknown';       /* part of bigger word */
        end
        */

        /*
         * Is this some complex shit? Then we'll kick someone a$$!
         */
        if (iPos > 1   |   iPos + length(sMagicWord) < length(sExpr)) then
        do
            call lineout 'STDERR', 'error: Hey YOU! I only accept simple tests!';
            return 'errorINC';
        end

        if (fNeg) then
            return 'INC';
        return '!INC';
    end
return 'unknown';


/**
 * Lowercases the string.
 *
 * @returns Lowercased string.
 * @param   Str     String to lowercase.
 */
tolower: procedure
parse arg sStr
return translate(sStr,,
    'abcdefghijklmnopqrstuvwxyz',,
    'ABCDEFGHIJKLMNOPQRSTUVWXYZ');


