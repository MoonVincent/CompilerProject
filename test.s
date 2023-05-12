.data
    v0:
        .space 8000
.globl main
.text
QuickSort:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    addi sp, sp, -16
    sd a1, 8(sp)
    sd a0, 0(sp)
    ld t0, -24(fp)
    ld t1, -32(fp)
    blt t0, t1, label0
    j label1
label0:
    ld t0, -24(fp)
    addi sp, sp, -8
    sd t0, -40(fp)
    ld t0, -32(fp)
    addi sp, sp, -8
    sd t0, -48(fp)
    ld t0, -24(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    ld t1, 0(t1)
    addi sp, sp, -8
    sd t1, -56(fp)
label2:
    ld t0, -40(fp)
    ld t1, -48(fp)
    blt t0, t1, label3
    j label4
label3:
label5:
    ld t0, -40(fp)
    ld t1, -48(fp)
    blt t0, t1, label8
    j label7
label8:
    ld t0, -48(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    ld t1, 0(t1)
    ld t0, -56(fp)
    bge t1, t0, label6
    j label7
label6:
    ld t0, -48(fp)
    li t1, 1
    sub t2, t0, t1
    sd t2, -48(fp)
    j label5
label7:
    ld t0, -40(fp)
    ld t1, -48(fp)
    blt t0, t1, label9
    j label10
label9:
    ld t0, -48(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    ld t1, 0(t1)
    ld t0, -40(fp)
    li t2, 8
    mul t3, t0, t2
    la t0, v0
    add t2, t0, t3
    sd t1, 0(t2)
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
label10:
label11:
    ld t0, -40(fp)
    ld t1, -48(fp)
    blt t0, t1, label14
    j label13
label14:
    ld t0, -40(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    ld t1, 0(t1)
    ld t0, -56(fp)
    blt t1, t0, label12
    j label13
label12:
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
    j label11
label13:
    ld t0, -40(fp)
    ld t1, -48(fp)
    blt t0, t1, label15
    j label16
label15:
    ld t0, -40(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    ld t1, 0(t1)
    ld t0, -48(fp)
    li t2, 8
    mul t3, t0, t2
    la t0, v0
    add t2, t0, t3
    sd t1, 0(t2)
    ld t0, -48(fp)
    li t1, 1
    sub t2, t0, t1
    sd t2, -48(fp)
label16:
    j label2
label4:
    ld t0, -56(fp)
    ld t1, -40(fp)
    li t2, 8
    mul t3, t1, t2
    la t1, v0
    add t2, t1, t3
    sd t0, 0(t2)
    ld t0, -24(fp)
    ld t1, -40(fp)
    li t2, 1
    sub t3, t1, t2
    mv a0, t3
    mv a1, t0
    jal QuickSort
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    ld t0, -32(fp)
    mv a0, t0
    mv a1, t2
    jal QuickSort
label1:
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
main:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    jal getint
    mv t0, a0
    addi sp, sp, -8
    sd t0, -16(fp)
    li t0, 0
    addi sp, sp, -8
    sd t0, -24(fp)
label17:
    ld t0, -24(fp)
    ld t1, -16(fp)
    blt t0, t1, label18
    j label19
label18:
    jal getint
    mv t0, a0
    ld t1, -24(fp)
    li t2, 8
    mul t1, t1, t2
    la t2, v0
    add t1, t2, t1
    sd t0, 0(t1)
    ld t0, -24(fp)
    li t1, 1
    add t0, t0, t1
    sd t0, -24(fp)
    j label17
label19:
    li t0, 0
    ld t1, -16(fp)
    li t2, 1
    sub t1, t1, t2
    mv a0, t1
    mv a1, t0
    jal QuickSort
    li t0, 0
    sd t0, -24(fp)
label20:
    ld t0, -24(fp)
    ld t1, -16(fp)
    blt t0, t1, label21
    j label22
label21:
    ld t0, -24(fp)
    li t1, 8
    mul t0, t0, t1
    la t1, v0
    add t0, t1, t0
    ld t0, 0(t0)
    mv a0, t0
    jal putint
    ld t0, -24(fp)
    li t1, 1
    add t0, t0, t1
    sd t0, -24(fp)
    j label20
label22:
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
