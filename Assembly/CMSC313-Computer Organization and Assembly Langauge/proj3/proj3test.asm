%define STDIN 0
%define STDOUT 1
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4


[SECTION .data]

lf:          db 10              ; line feed

msg1:       db " plus "
len1 equ $-msg1

msg2:      db " minus "
len2 equ $-msg2

msg3:      db " equals "
len3 equ $-msg3

printChar:       db 0

[SECTION .text]

global _start

_start:
	mov     ebx, 17
	mov     edx, 214123
	mov     edi, 2223187809
	mov     ebp, 1555544444


	push    dword 0x0
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

prt_dec:
	mov eax, [esp+4]
	push ebx        ; (First in/Last out)
	push edx        ; push values to stack
	push edi        ;
	push ebp        ; (Last in/First out)

	mov ebx, 10     ; what to divide eax by
	mov edi, 0      ; use edi as counter
	cmp eax, 0      ; check for case where value passed is 0
	je .zeroChar    ; if value passed is 0 jump to .zeroChar

	jmp .divNum

.zeroChar:
	push eax        ; push 0 to stack to be printed
	add edi, 1      ; inc counter by 1

.cont:
	pop ecx         ; pop number to print to ecx
	add ecx, 48     ; add 48 to print out correct number value
	mov [printChar], ecx

	mov eax, 4      ; write
	mov ebx, 1      ; out
	mov ecx, printChar
	mov edx, 4
	int 80H
	sub edi, 1      ; dec counter by 1
	cmp edi, 0      ; check if counter = 0
	jg .cont        ; return to .cont to continue printing

.done:
	pop ebp         ; return values to original registers
	pop edi
	pop edx
	pop ebx
	ret             ; return to main func

.divNum:
	mov edx, 0      ; zero out edx
	cmp eax, 0      ; check if eax = 0
	je .cont        ; if eax = 0 div is complete
	div ebx         ; divide eax by ebx (10)
	push edx        ; store remainder in stack
	add edi, 1      ; inc counter by 1
	jmp .divNum     ; continue loop