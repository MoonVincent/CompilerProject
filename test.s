.data
    v2:
        .space 5000
    v1:
        .space 5000
    v0:
        .space 5000
    v17: .string "Incompatible Dimensions\n"
    v16: .string "\n"
    v15: .string " "
.globl main
.text
getDigitNum:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    addi sp, sp, -8
    sd a0, 0(sp)
    li t0, 0
    addi sp, sp, -8
    sd t0, -32(fp)
    ld t0, -24(fp)
    li t1, 0
    beq t0, t1, label0
    j label1
label0:
    li t0, 1
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
label1:
    ld t0, -24(fp)
    li t1, 0
    blt t0, t1, label2
    j label3
label2:
    li t0, 1
    sd t0, -32(fp)
label3:
label4:
    ld t0, -24(fp)
    li t1, 0
    bne t0, t1, label5
    j label6
label5:
    ld t0, -24(fp)
    li t1, 10
    div t2, t0, t1
    sd t2, -24(fp)
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label4
label6:
    ld t0, -32(fp)
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
printString:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, 0(sp)
    addi fp, sp, 16
    addi sp, sp, -8
    sd a0, 0(sp)
    li t0, 0
    addi sp, sp, -8
    sd t0, -32(fp)
label7:
    ld t0, -32(fp)
    li t1, 1
    mul t2, t0, t1
    ld t0, -24(fp)
    add t1, t0, t2
    lb t1, 0(t1)
    li t0, 0
    bne t1, t0, label8
    j label9
label8:
    ld t0, -32(fp)
    li t1, 1
    mul t2, t0, t1
    ld t0, -24(fp)
    add t1, t0, t2
    lb t1, 0(t1)
    mv a0, t1
    jal putch
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label7
label9:
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
    addi sp, sp, -8
    sd t0, -16(fp)
    addi sp, sp, -8
    sd t0, -24(fp)
    li t0, 0
    addi sp, sp, -8
    sd t0, -32(fp)
    li t0, 0
    addi sp, sp, -8
    sd t0, -40(fp)
label10:
    ld t0, -32(fp)
    ld t1, -16(fp)
    blt t0, t1, label11
    j label12
label11:
    li t0, 0
    sd t0, -40(fp)
label13:
    ld t0, -40(fp)
    ld t1, -24(fp)
    blt t0, t1, label14
    j label15
label14:
    ld t0, -40(fp)
    li t1, 8
    mul t2, t0, t1
    ld t0, -32(fp)
    mul t0, t0, t1
    li t1, 25
    mul t0, t0, t1
    add t2, t0, t2
    la t0, v0
    add t1, t0, t2
    sd t0, 0(t1)
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
    j label13
label15:
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label10
label12:
    addi sp, sp, -8
    sd t0, -48(fp)
    addi sp, sp, -8
    sd t0, -56(fp)
    li t0, 0
    sd t0, -32(fp)
    li t0, 0
    sd t0, -40(fp)
label16:
    ld t0, -32(fp)
    ld t1, -48(fp)
    blt t0, t1, label17
    j label18
label17:
    li t0, 0
    sd t0, -40(fp)
label19:
    ld t0, -40(fp)
    ld t1, -56(fp)
    blt t0, t1, label20
    j label21
label20:
    ld t0, -40(fp)
    li t1, 8
    mul t2, t0, t1
    ld t0, -32(fp)
    mul t0, t0, t1
    li t1, 25
    mul t0, t0, t1
    add t2, t0, t2
    la t0, v1
    add t1, t0, t2
    sd t0, 0(t1)
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
    j label19
label21:
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label16
label18:
    ld t0, -24(fp)
    ld t1, -48(fp)
    bne t0, t1, label22
    j label23
label22:
    la t0, v17
    mv a0, t0
    jal printString
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
label23:
    li t0, 0
    sd t0, -32(fp)
    li t0, 0
    sd t0, -40(fp)
label24:
    ld t0, -32(fp)
    ld t1, -16(fp)
    blt t0, t1, label25
    j label26
label25:
    li t0, 0
    sd t0, -40(fp)
label27:
    ld t0, -40(fp)
    ld t1, -56(fp)
    blt t0, t1, label28
    j label29
label28:
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
label30:
    ld t0, -64(fp)
    ld t1, -24(fp)
    blt t0, t1, label31
    j label32
label31:
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
    j label30
label32:
    ld t0, -40(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -40(fp)
    j label27
label29:
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label24
label26:
    li t0, 0
    sd t0, -32(fp)
    li t0, 0
    sd t0, -40(fp)
label33:
    ld t0, -32(fp)
    ld t1, -16(fp)
    blt t0, t1, label34
    j label35
label34:
    li t0, 0
    sd t0, -40(fp)
label36:
    ld t0, -40(fp)
    ld t1, -56(fp)
    blt t0, t1, label37
    j label38
label37:
    li t0, 0
    sd t0, -64(fp)
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
    jal getDigitNum
    mv t0, a0
    addi sp, sp, -8
    sd t0, -72(fp)
    li t0, 10
    ld t1, -72(fp)
    sub t2, t0, t1
    sd t2, -72(fp)
label39:
    ld t0, -64(fp)
    ld t1, -72(fp)
    blt t0, t1, label40
    j label41
label40:
    la t0, v15
    mv a0, t0
    jal printString
    ld t0, -64(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -64(fp)
    j label39
label41:
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
    j label36
label38:
    la t0, v16
    mv a0, t0
    jal printString
    ld t0, -32(fp)
    li t1, 1
    add t2, t0, t1
    sd t2, -32(fp)
    j label33
label35:
    li t0, 0
    mv sp, fp
    ld ra, -8(fp)
    ld fp, -16(fp)
    mv a0, t0
    ret 
