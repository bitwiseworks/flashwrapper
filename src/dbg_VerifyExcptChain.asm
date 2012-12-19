; $Id: dbg_VerifyExcptChain.asm,v 1.1.1.1 2003/09/13 01:30:12 bird Exp $
;
; Verify the OS/2 Exception Chain.
;
; Copyright (c) 2003 InnoTek Systemberatung GmbH
; Copyright (c) 2012 bww bitwise works GmbH
;
; Authors: knut st. osmundsen <bird@anduin.net>
;          Dmitriy Kuminov <coding@dmik.org>
;
; All Rights Reserved
;
;


.486p

;*******************************************************************************
;* Header Files                                                                *
;*******************************************************************************
include bsetib.inc

;*******************************************************************************
;* External Symbols                                                            *
;*******************************************************************************
extrn   Dos32TIB:abs


;*******************************************************************************
;* Exported Symbols                                                            *
;*******************************************************************************
public npVerifyExcptChain


;*******************************************************************************
;* Structures and Typedefs                                                     *
;*******************************************************************************



CODE32 segment dword public use32 'CODE'
ASSUME ds:FLAT, es:FLAT, fs:NOTHING, ss:FLAT


;;
; Will verify the exception handler chain of the current thread.
; @cproto   void npVerifyExcptChain(void);
npVerifyExcptChain proc near
    push    ebp
    mov     ebp, esp
    push    eax
    push    edx
    push    ecx
    push    esi
    push    edi
    ; OS/2 FS
    push    fs
    mov     eax, Dos32TIB
    mov     fs, eax
    ASSUME  fs:nothing

    ;
    ; Install exception handler.
    ;
    push    offset FLAT:exceptionhandler
    mov     esi, fs:0
    push    esi
    mov     fs:0, esp

    ;
    ; Walk the chain. (esi is ExcpRegRec pointer)
    ;
    mov     esi, fs:0
iterate:
    cmp     esi, 0ffffffffh
    je      exit
    cmp     esi, 0
    je      exit

    ; Check that the handler code is accessible.
    mov     edi, [esi + 4]
    test    byte ptr [edi], 1

    ; Check that the chain is in ascending order.
    mov     edi, [esi]
    cmp     edi, esi
    jae     orderok

    ; perhaps invalid order, unless we're on a thunking stack. (f**k)
    ;   The thunking doesn't update the tib it seems. (initterm)
    xor     eax, eax
    assume  eax:ptr tib_s
    mov     ecx, fs:[eax].tib_pstacklimit
    cmp     esp, ecx
    ja      stop
    mov     ecx, fs:[eax].tib_pstack
    cmp     esp, ecx
    jbe     exit

    ; someone switched the thread 1 stack in mozilla. Can't figure it out in
    ; above test, so we'll just check for fixed addresses.
    mov     ecx, fs:[eax].tib_ordinal
    cmp     ecx, 1
    je      bad
    cmp     edi, 00050000h
    jb      bad
    cmp     edi, 02000000h
    ja      bad

    ; it's ok, but we stop here.
stop:
    jmp     exit

bad:
    ; invalid order!
    mov     eax, 0dead0000h
    int     3
    jmp     exit
orderok:

next:
    mov     esi, [esi]
    jmp     iterate


exit:
    ;
    ; Remove exception handler.
    ;
    pop     esi
    mov     fs:0, esi
    pop     esi

    ;
    ; Restore register and leave.
    ;
    pop     fs
    pop     edi
    pop     esi
    pop     ecx
    pop     edx
    pop     eax
    leave
    ret

;
; Access error!
;
exceptionhandler::
    mov     eax, 0dead0001h
    int     3
    int     3
    int     3
    int     3
npVerifyExcptChain endp



CODE32 ends

end
