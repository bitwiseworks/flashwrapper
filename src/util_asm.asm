; $Id: util_asm.asm,v 1.1.1.1 2003/09/13 01:30:18 bird Exp $
;
; NP JNI wrapping.
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
;* External Symbols                                                            *
;*******************************************************************************
extrn   Dos32TIB:abs


;*******************************************************************************
;* Exported Symbols                                                            *
;*******************************************************************************
public NPJNIEqual
public npGetFS
public GetFS
public npSetFS
public SetFS
public npRestoreOS2FS
public RestoreOS2FS


;*******************************************************************************
;* Structures and Typedefs                                                     *
;*******************************************************************************
;;
; The start of this structure.
J2LXJNIWRAPPERDATA struc
pfnOrg          dd ?
cbCallframe     dd ?
J2LXJNIWRAPPERDATA ends


CODE32 segment dword public use32 'CODE'
ASSUME ds:FLAT, es:FLAT, fs:NOTHING, ss:FLAT


;;
; Performs an SMP safe set of a specified dword number if it holds a given value.
; @cproto   KBOOL _Optlink NPJNIEqual(unsigned long *pul, unsigned long ulSet, unsigned long ulCurrent)
; @returns  TRUE if successfully updated value.
; @returns  FALSE if current value was not ulCurrent.
; @param    pul         Pointer to unsigned long value to set.
; @param    ulSet       The new value to set instead of ulCurrent.
; @param    ulCurrent   The current value of *pul if the operation should succeed.
; @uses     eax, edx, ecx
NPJNIEqual proc near
    xchg    ecx, eax                    ; ecx = pul
                                        ; eax = ulCurrent
                                        ; edx = ulSet
    lock cmpxchg [ecx], edx
    jnz     nok                         ; jump on failure.

    mov     eax, 1
    ret                                 ; success

nok:
    xor     eax, eax
    ret                                 ; failure
NPJNIEqual endp


;;
; @returns current fs
npGetFS proc near
GetFS::
    mov     eax, fs
    ret
npGetFS endp

;;
; @returns returns new fs
; @param   eax new fs.
npSetFS   proc near
SetFS::
    mov     eax, [esp+4]
    mov     fs, eax
    ret
npSetFS   endp

;;
; @returns old fs
npRestoreOS2FS proc near
RestoreOS2FS::
    push    Dos32TIB
    mov     ax, fs
    pop     fs
    ret
npRestoreOS2FS endp

CODE32 ends

end

