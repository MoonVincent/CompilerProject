.data
    v2:
        .space 5000
    v1:
        .space 5000
    v0:
        .space 5000
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
    li t0, 0
    addi sp, sp, -8
    sd t0, -32(fp)
    li t0, 0
    addi sp, sp, -8
    sd t0, -40(fp)
label0:
    ld t0, -32(fp)
    ld t1, -16(fp)
    blt t0, t1, label1
    j label2
label1:
    li t0, 0
    sd t0, -40(fp)
label3:
    ld t0, -40(fp)
    ld t1, -24(fp)
    blt t0, t1, label4
    j label5
label4:
    jal getint
    mv t0, a0
    ld t1, -40(fp)
    li t2, 8
    mul t3, t1, t2
    ld t1, -32(fp)
    mul t1, t1, t2
    li t2, 25
    mul t1, t1, t2
    add t3, t1, t3
    la t1, v0
    add t2, t1, t3
    sd t0, 0(t2)
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
    j label3
label5:
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label0
label2:
    jal getint
    mv t0, a0
    addi sp, sp, -8
    sd t0, -48(fp)
    jal getint
    mv t0, a0
    addi sp, sp, -8
    sd t0, -56(fp)
    li t0, 0
    sd t0, -32(fp)
    li t0, 0
    sd t0, -40(fp)
label6:
    ld t0, -32(fp)
    ld t1, -48(fp)
    blt t0, t1, label7
    j label8
label7:
    li t0, 0
    sd t0, -40(fp)
label9:
    ld t0, -40(fp)
    ld t1, -56(fp)
    blt t0, t1, label10
    j label11
label10:
    jal getint
    mv t0, a0
    ld t1, -40(fp)
    li t2, 8
    mul t3, t1, t2
    ld t1, -32(fp)
    mul t1, t1, t2
    li t2, 25
    mul t1, t1, t2
    add t3, t1, t3
    la t1, v1
    add t2, t1, t3
    sd t0, 0(t2)
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
    j label9
label11:
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label6
label8:
    li t0, 0
    sd t0, -32(fp)
    li t0, 0
    sd t0, -40(fp)
label12:
    ld t0, -32(fp)
    ld t1, -16(fp)
    blt t0, t1, label13
    j label14
label13:
    li t0, 0
    sd t0, -40(fp)
label15:
    ld t0, -40(fp)
    ld t1, -56(fp)
    blt t0, t1, label16
    j label17
label16:
    li t0, 0
    addi sp, sp, -8
    sd t0, -64(fp)
    li t0, 0
    ld t1, -40(fp)
    li t2, 8
    mul t3, t1, t2
    ld t1, -32(fp)
    mul t1, t1, t2
    li t2, 25
    mul t1, t1, t2
    add t3, t1, t3
    la t1, v2
    add t2, t1, t3
    sd t0, 0(t2)
label18:
    ld t0, -64(fp)
    ld t1, -24(fp)
    blt t0, t1, label19
    j label20
label19:
    ld t0, -40(fp)
    li t1, 8
    mul t2, t0, t1
    ld t0, -32(fp)
    mul t0, t0, t1
    li t1, 25
    mul t0, t0, t1
    add t2, t0, t2
    la t0, v2
    add t1, t0, t2
    ld t1, 0(t1)
    ld t0, -64(fp)
    li t2, 8
    mul t3, t0, t2
    ld t0, -32(fp)
    mul t0, t0, t2
    li t2, 25
    mul t0, t0, t2
    add t3, t0, t3
    la t0, v0
    add t2, t0, t3
    ld t2, 0(t2)
    ld t0, -40(fp)
    li t3, 8
    mul t4, t0, t3
    ld t0, -64(fp)
    mul t0, t0, t3
    li t3, 25
    mul t0, t0, t3
    add t4, t0, t4
    la t0, v1
    add t3, t0, t4
    ld t3, 0(t3)
    mul t0, t2, t3
    add t2, t1, t0
    ld t0, -40(fp)
    li t1, 8
    mul t3, t0, t1
    ld t0, -32(fp)
    mul t0, t0, t1
    li t1, 25
    mul t0, t0, t1
    add t3, t0, t3
    la t0, v2
    add t1, t0, t3
    sd t2, 0(t1)
    ld t0, -64(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -64(fp)
    j label18
label20:
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
    j label15
label17:
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label12
label14:
    li t0, 0
    sd t0, -32(fp)
    li t0, 0
    sd t0, -40(fp)
label21:
    ld t0, -32(fp)
    ld t1, -16(fp)
    blt t0, t1, label22
    j label23
label22:
    li t0, 0
    sd t0, -40(fp)
label24:
    ld t0, -40(fp)
    ld t1, -56(fp)
    blt t0, t1, label25
    j label26
label25:
    ld t0, -40(fp)
    li t1, 8
    mul t2, t0, t1
    ld t0, -32(fp)
    mul t0, t0, t1
    li t1, 25
    mul t0, t0, t1
    add t2, t0, t2
    la t0, v2
    add t1, t0, t2
    ld t1, 0(t1)
    mv a0, t1
    jal putint
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
    j label24
label26:
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label21
label23:
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
