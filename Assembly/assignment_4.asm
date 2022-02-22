%macro exit 0
mov rax,60
mov rdi ,00
syscall
%endmacro


%macro r_w 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro

section .data
	array db 11h,01h,32h,36h,5h
	count db 05
	oth_count db 02

section .bss
        result resb 10 
        output resb 30 
        
section .text
	global _start
	_start: 
	mov rsi,array
	mov bl,00
	up:
	cmp bl,[rsi]
	jge skip
	mov bl,[rsi]
	
	
skip:
	inc rsi
	dec byte[count]
	jnz up
mov [result],bl
call display
r_w 01,01,output,2
	
exit

display:
	mov rsi,output
	mov bl,[result]
	pup:
	rol bl,04
	mov dh,bl 
	and dh,0Fh
	cmp dh,09
	jbe omit
	add dh,07h
	omit:
	add dh,30h
	mov [rsi],dh
	inc rsi
	dec byte[oth_count]
	jnz pup
	ret
	
