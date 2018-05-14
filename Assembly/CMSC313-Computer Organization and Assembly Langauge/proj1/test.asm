section .text
	global _start

_start:
	mov eax, 4
	mov ebx, 3
	add eax, ebx

	;; clear and quit
	mov eax, 1
	mov ebx, 0
	int 80H

