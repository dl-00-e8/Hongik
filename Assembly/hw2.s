        .global main
main:   save %sp, -96, %sp
        add %i0, %i1, %i0
        mov %i0, %o0
        mov 3, %o1
        call .rem
        nop
        mov %o0, %i0
        sub %i2, %i3, %i1
        mov %i1, %o0
        mov %i4, %o1
        call .mul
        nop
        mov %o0, %i1
        add %i0, %i1, %i0
        mov %i0, %o0
        mov %i5, %o1
        call .div
        nop
        mov %o0, %i0

result:
        ret
        restore