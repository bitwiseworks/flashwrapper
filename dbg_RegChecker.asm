; $Id: dbg_RegChecker.asm,v 1.1.1.1 2003/09/13 01:30:12 bird Exp $
;
; Register checker exploits profiler hooks :)
;
; InnoTek Systemberatung GmbH confidential
;
; Copyright (c) 2003 InnoTek Systemberatung GmbH
; Author: knut st. osmundsen <bird@anduin.net>
;
; All Rights Reserved
;
;



    .386

CLEAN_STACK         equ 1
CLEAN_STACK_DWORDS  equ 400h
CLEAN_STACK_DWORD   equ 022222222h

extrn odin_malloc:near
extrn odin_free:near
extrn npVerifyExcptChain:near


;*******************************************************************************
;* Public Symbols                                                              *
;*******************************************************************************
public _ProfileHook32
public _ProfileHookVAOptlink32
public _ProfileUnwind32
public _ProfileThrow32


CODE32 segment use32 para public 'CODE'



_ProfileHook32 proc near
    push    ebp
    mov     ebp, esp

    ; save and clear the registers modified by caller and us.
    push    eax
    push    edx
    push    ecx
    xor     eax, eax
    xor     ecx, ecx
    xor     edx, edx

    ; save registers to copy.
    ; after save
    ;   esp/eax ->  ss       0
    ;               gs       4
    ;               fs       8
    ;               ds       c
    ;               es      10
    ;               ebp     14
    ;               edi     18
    ;               esi     1c
    ;               ebp     20
    ;               esp     24
    ;               ebx     28
    ;               flags   2c
    ;               fs:[0]  30
    ;               fs:[4]  34
    ;               fs:[8]  38
    ;               fs:[c]  3c
    ;
    push    dword ptr fs:[00h]
    push    dword ptr fs:[04h]
    push    dword ptr fs:[08h]
    push    dword ptr fs:[0ch]
    pushfd
    push    ebx
    push    esi
    push    edi
    push    dword ptr [ebp]
    push    es
    push    ds
    push    fs
    push    gs
    push    ss

    ;
    ; Allocate memory for it.
    ;
    mov     eax, 128
    push    eax
    call    odin_malloc
    add     esp, 4

    ;
    ; copy the block
    ;
    lea     edi, [eax + 20h]            ; reserve 32 bytes for code patch.
    mov     esi, esp
    lea     ecx, [ebp - 0ch]
    sub     ecx, esp
    shr     ecx, 2
    rep movsd

    ;
    ; Now get return address of the calling function.
    ; ASSUMES no prolog.
    ;
    mov     ecx, [ebp + 8]
    mov     [eax + 10h], ecx            ; save real return address
    mov     [ebp + 8], eax
    mov     dword ptr [eax+4], 0cccccccch
    mov     byte ptr [eax], 0e8h
    mov     edx, offset FLAT:FrameLeave
    lea     ecx, [eax+5]
    sub     edx, ecx
    mov     [eax+1], edx

    ;
    ; Verify execption chain.
    ;
    call    npVerifyExcptChain

    ;
    ; Restore registers and get out of here.
    ;
    add     esp, 6 * 4

    pop     edi
    pop     esi
    pop     ebx
    popfd
    add     esp, 10h                    ; fs:[0-10h]
    pop     ecx
    pop     edx
    pop     eax
    leave

ifdef CLEAN_STACK
    push    edi
    push    ecx
    push    eax
    pushf

    cld
    mov     edi, esp
    mov     ecx, CLEAN_STACK_DWORDS
    sub     edi, CLEAN_STACK_DWORDS*4
    mov     eax, CLEAN_STACK_DWORD
    stosd

    popf
    mov     eax, [esp]
    mov     ecx, [esp+4]
    mov     edi, [esp+8]
    mov     dword ptr [esp],   CLEAN_STACK_DWORD
    mov     dword ptr [esp+4], CLEAN_STACK_DWORD
    mov     dword ptr [esp+8], CLEAN_STACK_DWORD
    add     esp, 0ch
endif
    ret
_ProfileHook32 endp


FrameLeave proc near
    push    ebp
    mov     ebp, esp

    ; save and clear the registers modified by caller and us.
    push    eax
    push    edx
    push    ecx
    xor     eax, eax
    xor     edx, edx
    xor     ecx, ecx

    ; save registers to compare.
    push    dword ptr fs:[00h]
    push    dword ptr fs:[04h]
    push    dword ptr fs:[08h]
    push    dword ptr fs:[0ch]
    pushfd
    push    ebx
    push    esi
    push    edi
    push    dword ptr [ebp]
    push    es
    push    ds
    push    fs
    push    gs
    push    ss

    ;
    ; Figure out memory block pointer.
    ;
    mov     eax, [ebp + 4h]
    lea     eax, [eax - 5]

    ;
    ; Compare register dumps.
    ;
    mov     edi, esp
    lea     esi, [eax + 20h]
    lea     ecx, [ebp - 0ch]
    sub     ecx, esp
    shr     ecx, 2
    repe cmpsd
    je      ok

    int     3
ok:

    mov     edx, [eax + 10h]            ; real return address
    mov     [ebp + 4], edx

    ;
    ; free the block.
    ;
    push    eax
    call    odin_free
    add     esp, 4

    ;
    ; Verify execption chain.
    ;
    call    npVerifyExcptChain

    ;
    ; Restore registers and get out of here.
    ;
    add     esp, 6 * 4

    pop     edi
    pop     esi
    pop     ebx
    popfd
    add     esp, 10h                    ; fs:[0-10h]
    pop     ecx
    pop     edx
    pop     eax
    leave

ifdef CLEAN_STACK
    push    edi
    push    ecx
    push    eax
    pushf

    cld
    mov     edi, esp
    mov     ecx, CLEAN_STACK_DWORDS
    sub     edi, CLEAN_STACK_DWORDS*4
    mov     eax, CLEAN_STACK_DWORD
    stosd

    popf
    mov     eax, [esp]
    mov     ecx, [esp+4]
    mov     edi, [esp+8]
    mov     dword ptr [esp],   CLEAN_STACK_DWORD
    mov     dword ptr [esp+4], CLEAN_STACK_DWORD
    mov     dword ptr [esp+8], CLEAN_STACK_DWORD
    add     esp, 0ch
endif

    ret
FrameLeave endp



_ProfileHookVAOptlink32 proc near
_ProfileUnwind32::
_ProfileThrow32::
ret
_ProfileHookVAOptlink32 endp



CODE32 ends



end
