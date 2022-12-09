        L = 10
        .global main

main:   save %sp, -96, %sp
        mov   %g0, %o0
        mov   1, %l0
loop:   subcc %l0, L, %g0
        bg    next_r
        nop
        add   %o0, %l0, %o0
        inc   %l0
        ba    loop
        nop
next_r: ret
        restore
