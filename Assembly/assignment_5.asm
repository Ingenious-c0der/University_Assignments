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
	msg1 db "The number of positive numbers are : "
        len1 equ $-msg1
        
        msg2 db "The number of negative numbers are : "
        len2 equ $-msg2
        
        newln db "",10
        lenw equ $-newln
        
	array db 11,01,-32,-36,80,80,-80
	count db 07
	positive_count db 00
	negative_count db 00
	
 
section .bss
	 d_c resb 04
	
section .text
	global _start
	_start: 
	mov rsi,array
loop:
	mov bl,[rsi]
	add bl,00h
	js l1
	inc Byte[positive_count]
	jmp l2
l1:
	inc Byte[negative_count]
l2:
	inc rsi
	dec Byte[count]
	jnz loop
	r_w 01,01,msg1,len1
	mov bl,Byte[positive_count]
	add bl,30h
	mov Byte[positive_count],bl
	r_w 01,01,positive_count,02
	r_w 01,01,newln,lenw
	
	r_w 01,01,msg2,len2
	mov cl,Byte[negative_count]
	add cl,30h
	mov Byte[negative_count],cl
	r_w 01,01,negative_count,02
	r_w 01,01,newln,lenw
	
	b1:
	
	
	
	
exit
