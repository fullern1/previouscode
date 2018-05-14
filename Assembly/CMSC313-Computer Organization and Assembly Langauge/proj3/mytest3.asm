	;; Nathaniel Fuller
	;; CMSC 313
	;; Proj 3

%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4


[SECTION .data]

lf:	db 10 			; line feed

msg1:	 db " plus "
len1 equ $-msg1

msg2:	db " minus "
len2 equ $-msg2

msg3:	db " equals "
len3 equ $-msg3

[SECTION .text]

global _start
extern prt_dec

_start:
	mov     ebx, 7345
	mov     edx, 00193
	mov     edi, 1190492
	mov     ebp, 109837289

	push    dword 0xFAB32F
	call    prt_dec
	add     esp, 4
	call    prt_lf

	push    dword 0xFFFFFFFF
	call    prt_dec
	add     esp, 4
	call    prt_lf

	push    3413151
	call    prt_dec
	add     esp, 4
	call    prt_lf

	push    ebx
	call    prt_dec
	add     esp, 4
	call    prt_lf

	push    edx
	call    prt_dec
	add     esp, 4
	call    prt_lf

	push    edi
	call    prt_dec
	add     esp, 4
	call    prt_lf

	push    ebp
	call    prt_dec
	add     esp, 4
	call    prt_lf

	push    2
	call    prt_dec
	add     esp, 4

	mov     eax, SYSCALL_WRITE ; write message
	mov     ebx, STDOUT
	mov     ecx, msg1
	mov     edx, len1
	int     080h

	push    3
	call    prt_dec
	add     esp, 4

	mov     eax, SYSCALL_WRITE ; write message
	mov     ebx, STDOUT
	mov     ecx, msg3
	mov     edx, len3
	int     080h

	push    5
	call    prt_dec
	add     esp, 4
	call    prt_lf

	push    7
	call    prt_dec
        add     esp, 4

	mov     eax, SYSCALL_WRITE ; write message
	mov     ebx, STDOUT
	mov     ecx, msg2
	mov     edx, len2
	int     080h
	
	push    4
	call    prt_dec
	add     esp, 4

	mov     eax, SYSCALL_WRITE ; write message
	mov     ebx, STDOUT
	mov     ecx, msg3
	mov     edx, len3
	int     080h
	
	push    3
	call    prt_dec
	add     esp, 4
	call    prt_lf
	
exit:	
	mov eax, SYSCALL_EXIT
	mov ebx, 0
	int 80H

prt_lf:
	push eax
	push ebx
	push ecx
	push edx

	mov eax, SYSCALL_WRITE
	mov ebx, STDOUT
	mov ecx, lf
	mov edx, 1
	int 80H

	pop edx
	pop ecx
	pop ebx
	pop eax
	ret 