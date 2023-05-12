.data
    v0:
        .space 8000
.globl main
.text
QuickSort:
    addi sp, sp, -16
    sw ra, 8(sp)
    sw fp, 0(sp)
    addi fp, sp, 16
    addi sp, sp, -16
    sw a1, 8(sp)
    sw a0, 0(sp)
    lw t0, -12(fp)
    lw t1, -16(fp)
    blt t0, t1, label0
    j label1
label0:
    lw t0, -12(fp)
    addi sp, sp, -8
    sw t0, -40(fp)
    lw t0, -16(fp)
    addi sp, sp, -8
    sw t0, -48(fp)
    lw t0, -12(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    lw t1, 0(t1)
    addi sp, sp, -8
    sw t1, -56(fp)
label2:
    lw t0, -40(fp)
    lw t1, -48(fp)
    blt t0, t1, label3
    j label4
label3:
label5:
    lw t0, -40(fp)
    lw t1, -48(fp)
    blt t0, t1, label8
    j label7
label8:
    lw t0, -48(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    lw t1, 0(t1)
    lw t0, -56(fp)
    bge t1, t0, label6
    j label7
label6:
    lw t0, -48(fp)
    li t1, 1
    sub t2, t0, t1
    sw t2, -48(fp)
    j label5
label7:
    lw t0, -40(fp)
    lw t1, -48(fp)
    blt t0, t1, label9
    j label10
label9:
    lw t0, -48(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    lw t1, 0(t1)
    lw t0, -40(fp)
    li t2, 8
    mul t3, t0, t2
    la t0, v0
    add t2, t0, t3
    sw t1, 0(t2)
    lw t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sw t2, -40(fp)
label10:
label11:
    lw t0, -40(fp)
    lw t1, -48(fp)
    blt t0, t1, label14
    j label13
label14:
    lw t0, -40(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    lw t1, 0(t1)
    lw t0, -56(fp)
    blt t1, t0, label12
    j label13
label12:
    lw t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sw t2, -40(fp)
    j label11
label13:
    lw t0, -40(fp)
    lw t1, -48(fp)
    blt t0, t1, label15
    j label16
label15:
    lw t0, -40(fp)
    li t1, 8
    mul t2, t0, t1
    la t0, v0
    add t1, t0, t2
    lw t1, 0(t1)
    lw t0, -48(fp)
    li t2, 8
    mul t3, t0, t2
    la t0, v0
    add t2, t0, t3
    sw t1, 0(t2)
    lw t0, -48(fp)
    li t1, 1
    sub t2, t0, t1
    sw t2, -48(fp)
label16:
    j label2
label4:
    lw t0, -56(fp)
    lw t1, -40(fp)
    li t2, 8
    mul t3, t1, t2
    la t1, v0
    add t2, t1, t3
    sw t0, 0(t2)
    lw t0, -12(fp)
    lw t1, -40(fp)
    li t2, 1
    sub t3, t1, t2
    mv a0, t3
    mv a1, t0
    jal QuickSort
    lw t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    lw t0, -16(fp)
    mv a0, t0
    mv a1, t2
    jal QuickSort
label1:
    li t0, 0
    mv sp, fp
    lw ra, -8(fp)
    lw fp, -16(fp)
    mv a0, t0
    ret 
main:
    addi sp, sp, -16
    sw ra, 8(sp)
    sw fp, 0(sp)
    addi fp, sp, 16
    jal getint
    mv t0, a0
    addi sp, sp, -8
    sw t0, -16(fp)
    li t0, 0
    addi sp, sp, -8
    sw t0, -24(fp)
label17:
    lw t0, -24(fp)
    lw t1, -16(fp)
    blt t0, t1, label18
    j label19
label18:
    jal getint
    mv t0, a0
    lw t1, -24(fp)
    li t2, 8
    mul t1, t1, t2
    la t2, v0
    add t1, t2, t1
    sw t0, 0(t1)
    lw t0, -24(fp)
    li t1, 1
    add t0, t0, t1
    sw t0, -24(fp)
    j label17
label19:
    li t0, 0
    lw t1, -16(fp)
    li t2, 1
    sub t1, t1, t2
    mv a0, t1
    mv a1, t0
    jal QuickSort
    li t0, 0
    sw t0, -24(fp)
label20:
    lw t0, -24(fp)
    lw t1, -16(fp)
    blt t0, t1, label21
    j label22
label21:
    lw t0, -24(fp)
    li t1, 8
    mul t0, t0, t1
    la t1, v0
    add t0, t1, t0
    lw t0, 0(t0)
    mv a0, t0
    jal putint
    lw t0, -24(fp)
    li t1, 1
    add t0, t0, t1
    sw t0, -24(fp)
    j label20
label22:
    li t0, 0
    mv sp, fp
    lw ra, -8(fp)
    lw fp, -16(fp)
    mv a0, t0
    ret 
