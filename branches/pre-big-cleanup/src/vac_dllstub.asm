; $Id: vac_dllstub.asm,v 1.1.1.1 2003/09/13 01:30:18 bird Exp $
;
; These are STUB dlls, and don't need 5 segments!
; (Actually we don't need more than one, but I can't convince ilink that
;  this segment should be writable. :/ )
;
; InnoTek Systemberatung GmbHconfidential
;
; Copyright (c) 2003 InnoTek Systemberatung GmbH
; Author: knut st. osmundsen <bird@anduin.net>
;
; All Rights Reserved
;
;

    .486


CODE32 segment para use32 public 'CODE'
CODE32 ends

CODE32 segment
extrn _DLL_InitTerm:near
start:
    jmp _DLL_InitTerm

public _dllentry
_dllentry   dd 0
public __ctdtused
__ctdtused  dd 0
public _fltused
_fltused    dd 0
CODE32 ends


end start

