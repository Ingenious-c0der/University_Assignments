section .data
        msg1 db "Enter 5 64-bit numbers ",10
        len1 equ $-msg1
        newline db '', 10
        nlen equ $-newline
        msg2 db "Entered 64-bit numbers are :",10
        len2 equ $-msg2
        count db 05
        rev_count db 05
%macro exit 0
mov rax,60
mov rdi ,00
syscall
%endmacro

%macro read_write 4
mov rax,%1
mov rdi,%2
mov rsi,%3
mov rdx,%4
syscall
%endmacro



section .bss
        array resb 100

section .text
        global _start
        _start:
read_write 01,01,msg1,len1
mov rbx,array

reader:
        mov rax,00
        mov rdi,00
        mov rsi,rbx
        mov rdx,17
        syscall
        add rbx,17
        dec byte[count]
        jnz reader
read_write 01,01,newline,nlen
read_write 01,01,msg2,len2
mov rbx,array
writer:
        mov rax,01
        mov rdi,01
        mov rsi,rbx
        mov rdx,17
        syscall
        add rbx,17
        dec byte[rev_count]
        jnz writer
read_write 01,01,newline,nlen
exit
