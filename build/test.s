.globl main
.text
add:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    addi sp, sp, -16
    sd a1, 8(sp)
    sd a0, 0(sp)
    ld t0, -24(fp)
    ld t1, -32(fp)
    add t2, t0, t1
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t2
    ret 
main:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    addi sp, sp, -80
    addi sp, sp, -16
    li t0, 1
    li t1, 0
    li t2, 8
    mul t3, t1, t2
    addi t1, fp, -24
    add t2, t1, t3
    sd t0, 0(t2)
    li t0, 2
    li t1, 8
    li t2, 0
    mul t2, t2, t1
    addi t1, fp, -104
    add t3, t1, t2
    sd t0, 0(t3)
    li t0, 0
    li t1, 8
    mul t2, t0, t1
    addi t0, fp, -24
    add t1, t0, t2
    ld t1, 0(t1)
    li t0, 8
    li t2, 0
    mul t2, t2, t0
    addi t0, fp, -104
    add t3, t0, t2
    ld t3, 0(t3)
    mv a0, t3
    mv a1, t1
    jal add
    mv t0, a0
    addi sp, sp, -8
    sd t0, -120(fp)
    ld t0, -120(fp)
    mv a0, t0
    jal putint
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
