.globl main
.text
main:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    li t0, 3
    addi sp, sp, -8
    sd t0, -16(fp)
    li t0, 0
    addi sp, sp, -8
    sd t0, -24(fp)
    li t0, 2
    sd t0, -16(fp)
