; $Id: vac_odincrt.asm,v 1.1.1.1 2003/09/13 01:30:18 bird Exp $

;/*
; * Project Odin Software License can be found in LICENSE.TXT
; * Win32 Exception handling + misc functions for OS/2
; *
; * Copyright 1998 Sander van Leeuwen
; *
; */

; 1999/08/09 PH see if we can do this as INLINE functions

.386p
                NAME    odinfs

CODE32          SEGMENT DWORD PUBLIC USE32 'CODE'
                ASSUME  DS:FLAT, SS:FLAT

                PUBLIC  __threadid 
__threadid proc near
	push    ebp
	push	fs
        mov     ax, 150bh
	mov	fs, ax
		
        mov     eax,dword ptr fs:[0000000cH]

	pop	fs
        mov     ebp,esp
        leave   
        ret     
__threadid endp

	PUBLIC __nw__FUiPCcT1
	EXTERN odin__debug_malloc:NEAR
;input: eax = size
;       ecx = line nr
;       edx = source filename
__nw__FUiPCcT1 proc near
	push	fs
	push	eax
	mov	ax, 150bh
	mov	fs, ax
	pop	eax

        sub     esp, 0Ch
	call	odin__debug_malloc
        add     esp, 0Ch

	pop	fs
	ret
__nw__FUiPCcT1 endp

	PUBLIC __dl__FPvPCcUi
	EXTERN odin__debug_free:NEAR
;input: eax = this ptr
;       ecx = line nr
;       edx = source filename
__dl__FPvPCcUi proc near
	push	fs
	push	eax
	mov	ax, 150bh
	mov	fs, ax
	pop	eax

        sub     esp, 0Ch
	call	odin__debug_free
        add     esp, 0Ch
	pop	fs
	ret
__dl__FPvPCcUi endp


	PUBLIC __nw__FUi
	EXTERN odin_malloc:NEAR
;input: eax = size
__nw__FUi proc near
	push	fs
	push	eax
	mov	ax, 150bh
	mov	fs, ax
	pop	eax

        sub     esp, 4
	call	odin_malloc
        add     esp, 4

	pop	fs
	ret
__nw__FUi endp

	PUBLIC __dl__FPv
	EXTERN odin_free:NEAR
;input: eax = this ptr
__dl__FPv proc near
	push	fs
	push	eax
	mov	ax, 150bh
	mov	fs, ax
	pop	eax

        sub     esp, 4
	call	odin_free
        add     esp, 4

	pop	fs
	ret
__dl__FPv endp


CODE32          ENDS
                END
