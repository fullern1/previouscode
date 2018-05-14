	;; Nathaniel Fuller
	;; bookcmp.asm
	;; Project 4
global bookcmp
extern book1
extern book2

%define TITLE_OFFSET 0
%define AUTHOR_OFFSET 21
%define SUBJECT_OFFSET 36
%define YEAR_OFFSET 44
	
[SECTION .data]

[SECTION .text]

bookcmp:
	push ebx		; save registers used just in case
	push ecx
	push edx
	push edi
	
	mov ebx, [book1]	; book1 pointer
	mov ecx, [book2]	; book2 pointer
	mov edi, 0		; counter to increment
	mov eax, 0
	mov edx, 0
;;	jmp .nameLoop
	mov eax, [ebx+YEAR_OFFSET] ; move book1 year to eax
	mov edx, [ecx+YEAR_OFFSET] ; move book2 year to edx

	cmp eax, edx		; compare to see which is bigger
	jg .greater		; if greater jump to .greater and return 1
	jl .less		; if less jump to .less and return -1
	jmp .cmpName		; book years are equal, cmp name

.cmpName:
	mov edi, 0 		; reset counter to 0
.nameLoop:
	mov ah, [ebx+edi+TITLE_OFFSET]
	mov dh, [ecx+edi+TITLE_OFFSET]

	cmp ah, dh		; check if equal
	je .nullNameCheck 	; if so check if null

	cmp ah, 0H		; Check if reached end of book1 title
	je .less		; if so book 1 is less
	cmp dh, 0H		; Check if reached end of book2 title
	je .greater		; if so book 2 is less

	cmp ah, dh
	jg .greater
	jl .less
	add edi, 1
	jmp .nameLoop 		; continue till one is greater or equal to 0H
	
.nullNameCheck:
	cmp ah, 0H
	je .equal
	add edi, 1
	jmp .nameLoop

.equal:
	mov eax, 0		; values equal, move 0 to eax

	pop edi			; return previous values to registers
	pop edx
	pop ecx
	pop ebx
	ret			; return
	
.greater:
	mov eax, 1		; book2 greater, move 1 to eax
	
	pop edi
	pop edx
	pop ecx
	pop ebx
	ret

.less:
	mov eax, -1		; book 1 greater, move -1 to eax

	pop edi
	pop edx
	pop ecx
	pop ebx
	ret