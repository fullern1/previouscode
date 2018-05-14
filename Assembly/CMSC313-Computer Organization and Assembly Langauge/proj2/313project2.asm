;;;  Executable name: escapeseqs.out
;;;  Name: Nathaniel Fuller
;;;  CMSC 313
;;;  Project 2
;;;  Compiled with:
;;;  nasm -f elf -g -F stabs escapeseqs.asm
;;;  ld -e _start -m elf_i386 -o escapeseqs.out escapeseqs.o

;;; toUpper.asm used as base
%define STDIN 0
%define STDOUT 1
%define STDERR 2
%define SYSCALL_EXIT  1
%define SYSCALL_READ  3
%define SYSCALL_WRITE 4
%define BUFLEN 256

[SECTION .data]
;;;  Here we declare initialized data. For example: messages, prompts,
;;;  and numbers that we know in advance

msg1:			db "Enter string: " ; user prompt
len1:           equ $-msg1          ; length of first message

msg2:           db "Original: "     ; original string label
len2:           equ $-msg2          ; length of second message

msg3:           db "Convert: " 		; converted string label
len3:           equ $-msg3

[SECTION .bss]
;;;  Here we declare uninitialized data. We're reserving space (and
;;;  potentially associating names with that space) that our code
;;;  will use as it executes. Think of these as "global variables"

buf:             resb BUFLEN    ; buffer for read
newstr:          resb BUFLEN    ; converted string
readlen:         resb 4 ; storage for the length of string we read

[SECTION .text]

	global _start           ; make start global so ld can find it

_start:                         ; the program actually starts here
;;; ---------- READ ----------
;;;  prompt for user input
	mov eax, SYSCALL_WRITE
	mov ebx, STDOUT
	mov ecx, msg1
	mov edx, len1
	int 80H

;;;  read user input
	mov eax, SYSCALL_READ
	mov ebx, STDIN
	mov ecx, buf
	mov edx, BUFLEN
	int 80H

;;;  remember how many characters we read
	mov [readlen], eax
	cmp eax,0
	je .end

;;;  loop over all characters
	mov ebx, buf
	mov edi, newstr
	
;;; set string to be null terminated
	sub ebx, 1			; dec ebx by 1 (length of buf)
	mov [ebx+eax], 0H	; replace end of string char with null
	inc ebx				; return ebx to original value
	xor esi,esi 		; set esi to 0 to use as pointer/counter
	
;;; ---------- LOOP ----------
.loop:
	cmp eax, 0
	je .done

;;;  grab the next letter
	mov ch, [ebx]
	cmp ch, 5CH			; check if possible esc sequence (if value is '\')
	je .handleEsc		; if possible jump to .handleEsc
	cmp ch, 0H			; check if equal to null (end of string)
	je .done			; if equal jump to done
	jmp .lettercomplete ; if not add letter and move on

.lettercomplete:
;;;  store the letter and go on to the next one
	mov [edi], ch
	add ebx, 1			; add 1 to move to next char in buf
	add edi, 1			; add 1 to move to next char in newstr
	sub eax, 1			; sub 1 to decrease counter for loop/chars left
	add esi, 1 			; add 1 to pointer/counter
	jmp .loop

;;; ---------- HANDLE ESC ----------
.handleEsc:
;;; Check if char following '\' is alpha or numeric or equal to '\'
	add ebx, 1
	sub eax, 1
	add esi, 1
	
	mov ch, [ebx] 		; move char after '\' to ch
	cmp ch, 5CH			; check if equal to '\'
	je .lettercomplete	; if equal jump to .lettercomplete
	cmp ch, 30H			; check if numeric (cmp to '0')
	jl .invalid			; if less esc seq is invalid
	cmp ch, 37H			; compare to '7'
	jle .octalSeq   	; if less/equal code is octal sequence
	cmp ch, 61H			; check if alpha (cmp to 'a')
	jl .invalid			; if less esc seq is invalid
	cmp ch, 76H			; compare to 'v' (greater than 'v' not needed as 
							; all greater are invalid inputs)
	jle .alphaSeq		; if less/equal code is alpha (ex: '\a')
	
.invalid:
	mov ch, 5CH 		; move error char to be input into newstr
	jmp .lettercomplete	; jump to lettercomplete to input '\' to newstr

;;; Multiply counter by 8, add octal value, repeat as needed up to 3x to
;;; convert octal to decimal value. Store decimal value in new string
.octalSeq:
	xor ebp,ebp 		; set ebp to 0
	shl ebp, 3 			; multiply ebp by 8 
	add ebp, byte ch	; add octal digit to value
	add ebx, 1
	sub eax, 1
	add esi, 1
	mov ch, [ebx]		; move next digit to ch
	cmp ch, 30H			; compare to '0'
	jl .octalFinish		; if less than '0' it is not an octal value
	cmp ch, 37H			; compare to '7'
	jg .octalFinish		; if greater than '7' it is not an octal value
	shl ebp, 3			; multiply ebp by 8 
	add ebp, byte ch    ; add octal digit to value
	add ebx, 1
	sub eax, 1
	add esi, 1
	mov ch, [ebx]		; move next digit to ch
	cmp ch, 30H			; compare to '0'
	jl .octalFinish		; if less than '0' it is not an octal value
	cmp ch, 37H			; compare to '7'
	jg .octalFinish		; if greater than '7' it is not an octal value
	shl ebp, 3			; multiply ebp by 8 
	add ebp, byte ch    ; add octal digit to value
	add ebx, 1
	sub eax, 1
	add esi, 1
	jmp .octalFinish
.octalFinish:
	mov ch, [ebp]		; move converted value to ch
	jmp .lettercomplete	; jump to .lettercomplete to input ch
	
.alphaSeq:
;;; compare given char to see if accepted value
;;; if accepted, use lookup table w/ indexed adressing mode
;;; to insert corresponding value into output string

;;; ---------- WRITE ----------
.done:
;;;  print the original string message
	mov eax, SYSCALL_WRITE
	mov ebx, STDOUT
	mov ecx, msg2
	mov edx, len2
	int 80H

;;;  print the original string
	mov eax, SYSCALL_WRITE
	mov ebx, STDOUT
	mov ecx, buf
	mov edx, [readlen]
	int 80H

;;;  print the converted string message
	mov eax, SYSCALL_WRITE
	mov ebx, STDOUT
	mov ecx, msg3
	mov edx, len3
	int 80H

;;;  print the converted string
	mov eax, SYSCALL_WRITE
	mov ebx, STDOUT
	mov ecx, newstr
	mov edx, [readlen]
	int 80H

;;;  and we're done!
	jmp .end

;;; ---------- EXIT ----------
.end:
;;;  call sys_exit to finish things off
	mov eax, SYSCALL_EXIT ; sys_exit syscall
	mov ebx, 0            ; no error
	int 80H               ; kernel interrupt