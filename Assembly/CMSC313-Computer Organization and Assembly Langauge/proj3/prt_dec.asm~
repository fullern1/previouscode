	;; Nathaniel Fuller
	;; CMSC 313
	;; Project 3

global prt_dec

[SECTION .data]
printChar:	db 0		; used to help print

[SECTION .text]
prt_dec:
	mov eax, [esp+4]
	push ebx		; (First in/Last out)
	push edx		; push values to stack
	push edi		;
	push ebp		; (Last in/First out)

	mov ebx, 10 		; what to divide eax by
	mov edi, 0		; use edi as counter
	cmp eax, 0		; check for case where value passed is 0
	je .zeroChar		; if value passed is 0 jump to .zeroChar

	jmp .divNum

.zeroChar:
	push eax		; push 0 to stack to be printed
	add edi, 1		; inc counter by 1
	
.cont:
	pop ecx			; pop number to print to ecx
	add ecx, 48		; add 48 to print out correct number value
	mov [printChar], ecx
	
	mov eax, 4		; write
	mov ebx, 1		; out
	mov ecx, printChar
	mov edx, 4
	int 80H
	sub edi, 1		; dec counter by 1
	cmp edi, 0		; check if counter = 0
	jg .cont		; return to .cont to continue printing

.done:
	pop ebp			; return values to original registers
	pop edi
	pop edx
	pop ebx
	ret			; return to main func

.divNum:
	mov edx, 0		; zero out edx
	cmp eax, 0		; check if eax = 0
	je .cont		; if eax = 0 div is complete
	div ebx 		; divide eax by ebx (10)
	push edx 		; store remainder in stack
	add edi, 1		; inc counter by 1
	jmp .divNum		; continue loop
	