        .section ".data"
fmt1:   .asciz "%d "
fmt2:   .asciz "\n"
fmt3:   .asciz "maximum=%d\n"

ary_s = -48

        .align 4
        .global main, printf
main:   save %sp, -(92 + (3*4*4)) & -8, %sp
        call time
        mov 0, %o0
        call srand
        nop

        mov 0, %l0
        ba loopf_check
loopf:
        mov %l0, %o0
        mov 4, %o1
        call .mul ! i * C
        nop
        mov %o0, %l2
        mov 0, %l1
        ba loops_check
loops:
        add %l2, %l1, %l3 ! i * C + j
        sll %l3, 2, %l3 ! (i * C + j) * W

        call rand  ! rand()
        nop

        call .rem ! rand() % 100
        mov 100, %o1

        mov %o0, %l4
        add ary_s, %l3, %l3
        st %l4, [%fp + %l3]

        set fmt1, %o0 ! print rand value
        ld [%fp + %l3], %o1
        call printf
        nop

        add %l1, 1, %l1 ! j 갱신
loops_check:
        cmp %l1, 4 ! j < 4 탈출 조건 확인
        bl loops
        nop

        set fmt2, %o0 ! \n 출력
        call printf
        nop
        add %l0, 1, %l0 ! i 갱신
loopf_check:
        cmp %l0, 3 ! i < 3 탈출 조건 확인
        bl loopf
        nop

        add %fp, ary_s, %o0
        call find_max ! find_max 함수 호출
        nop
        mov %o0, %o1
        set fmt3, %o0
        call printf ! 함수 return 값 출력
        nop

result:
        ret
        restore

find_max: save %sp, -96, %sp
        mov -100, %l0
        st %l0, [%fp - 4] ! max 변수 메모리 적재
        ld [%fp -4], %l0
        mov 0, %l1
        ba sloopf_check
sloopf: mov %l1, %o0 ! for(int i = 0; i < 3; i++) 과정
        mov 4, %o1
        call .mul
        nop
        mov %o0, %l3
        mov 0, %l2
        ba sloops_check
sloops: add %l3, %l2, %l4 ! for(int j = 0; j < 4; j++) 과정
        sll %l4, 2, %l4

        add %i0, %l4, %l4
        ld [%l4], %l5

        ld [%fp - 4], %l0
        cmp %l5, %l0 ! max 변수 업데이트 여부 확인 조건문
        bg update
        nop

check:  add %l2, 1, %l2
sloops_check:
        cmp %l2, 4
        bl sloops
        nop

        add %l1, 1, %l1
sloopf_check:
        cmp %l1, 3
        bl sloopf
        nop

        ld [%fp - 4], %i0
        ba end
        nop

update: mov %l5, %l0 ! max 변수 업데이트
        st %l0, [%fp - 4]
        ba check
        nop

end:
        ret
        restore
