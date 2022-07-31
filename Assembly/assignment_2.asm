section .data
        msg db 'Enter the String : ',0
        len equ $-msg
        msg_2 db "Length of entered string is : "
        len_2 equ $-msg_2
        next_line db '',10
        next_len equ $-next_line

section .bss
strn resb 100
strlen resb 2
itrm resb 2

%macro read_write 4
mov rax , %1
mov rdi , %2
mov rsi , %3
mov rdx , %4
syscall
%endmacro

%macro exit 0
mov rax,60
mov rdi ,00
syscall
%endmacro

section .text
        global _start
        _start:


read_write 01,01,msg,len

read_write 00,00,strn,30
b1:

dec rax
mov [itrm],rax
cmp rax,09
jbe l1
add rax,07h
l1:add rax,30h
mov [strlen],rax
read_write 01,01,msg_2,len_2
read_write 01,01,strlen,itrm
read_write 01,01,next_line,next_len
exit
