.globl main
.text
main:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    addi sp, sp, -16
    li t0, 1
    li t1, 8
    li t2, 0
    mul t2, t2, t1
    addi t1, fp, -24
    add t3, t1, t2
    sd t0, 0(t3)
    li t0, 2
    li t1, 8
    li t2, 1
    mul t2, t2, t1
    addi t1, fp, -24
    add t3, t1, t2
    sd t0, 0(t3)
    li t0, 8
    li t1, 0
    mul t1, t1, t0
    addi t0, fp, -24
    add t2, t0, t1
    ld t2, 0(t2)
    mv a0, t2
    jal putint
    li t0, 8
    li t1, 1
    mul t1, t1, t0
    addi t0, fp, -24
    add t2, t0, t1
    ld t2, 0(t2)
    addi sp, sp, -8
    sd t2, -40(fp)
    ld t0, -40(fp)
    mv a0, t0
    jal putint
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
