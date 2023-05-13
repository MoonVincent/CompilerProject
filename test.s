.data
    v0:
        .space 80000
.globl main
.text
main:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    li t0, 1
    li t1, 2
    li t2, 8
    mul t3, t1, t2
    li t1, 1
    li t2, 8
    mul t4, t1, t2
    la t1, v0
    add t2, t1, t4
    ld t2, 0(t2)
    add t1, t2, t3
    mv t1, t0
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
