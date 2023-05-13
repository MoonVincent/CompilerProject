.globl main
.text
main:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    jal getint
    mv t0, a0
    addi sp, sp, -8
    sd t0, -16(fp)
    jal getint
    mv t0, a0
    addi sp, sp, -8
    sd t0, -24(fp)
    ld t0, -16(fp)
    mv a0, t0
    jal putint
    ld t0, -24(fp)
    mv a0, t0
    jal putint
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
