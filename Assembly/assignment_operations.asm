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
        msg db 'Enter the First Number : ',0
        len equ $-msg

        msg_2 db "Enter the Second Number: "
        len_2 equ $-msg_2

        next_line db '',10
        next_len equ $-next_line

        msg_3 db "The addition result is :"
        len_3 equ $-msg_3

        msg_4 db "The subtraction result is :"
        len_4 equ $-msg_4

        msg_5 db "The multiplication result is :"
        len_5 equ $-msg_5

        msg_6 db "The division result is :"
        len_6 equ $-msg_6

        count db 02
        oth_count db 02



section .bss
        array resb 100
        output resb 30

section .text
        global _start
        _start:

        r_w 01,01,msg,len
        r_w 00,00,array,10
        mov rdx,00
        mov rsi,array
        l2:
        mov bl,[rsi]
        cmp bl,39h
        jbe l1
        sub bl,07h
        l1:
        sub bl,30h
        shl rdx,04
        add dl,bl

        inc rsi
        dec Byte[count]
        jne l2
        mov r8,rdx


        mov Byte[count],02

        r_w 01,01,msg_2,len_2
        r_w 00,00,array,10
        mov rdx,00
        mov rsi,array
        l4:
        mov bl,[rsi]
        cmp bl,39h
        jbe l3
        sub bl,07h
        l3:
        sub bl,30h
        shl rdx,04
        add dl,bl

        inc rsi
        dec Byte[count]
        jne l4
        mov r9,rdx
        mov rax,00
        add rax,r8
        add rax,r9
        call display


        r_w 01,01,msg_3,len_3
        r_w 01,01,output,10
        r_w 01,01,next_line,next_len


        mov rax,01
        mul r8
        mul r9
        b:
        call display
        r_w 01,01,msg_5,len_5
        r_w 01,01,output,04
        r_w 01,01,next_line,next_len

        mov rax,r8
        sub rax,r9

        call display
        r_w 01,01,msg_4,len_4
        r_w 01,01,output,02
        r_w 01,01,next_line,next_len


        mov rax,r8
        div r9
        call display
         r_w 01,01,msg_6,len_6
        r_w 01,01,output,02
        r_w 01,01,next_line,next_len

exit

display:
        mov rsi,output
        mov rbx,rax
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
  
