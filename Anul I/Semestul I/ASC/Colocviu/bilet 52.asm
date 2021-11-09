.data
sir: .asciiz "01000011"
x: .byte 0x01
zero: .byte '0'
.text
main:

subu $sp,$sp,4
la $t0,sir
sw $t0,0($sp)

jal transformare

addi $sp,$sp,4

move $t3,$v0
li $v0,1
move $a0,$t3
syscall
li $v0,10
syscall

transformare:

subu $sp,$sp,4
sw $fp,0($sp)
move $fp,$sp #sp:fp:(fp vechi)(sir)
lw $t0,4($fp)

li $v0,0
li $t1,0
li $t2,8
for:
bge $t1,$t2,iesireFor #t1>t2
    sll $v0,$v0,1
    lb $t3,0($t0)
    lb $t5,zero
    sub $t3,$t3,$t5
    bnez $t3,nuEZero
      j continuare
    nuEZero:
      lb $t3,x
      or $v0,$v0,$t3
    continuare:
    addi $t0,$t0,1
    addi $t1,$t1,1
    j for
iesireFor:

lw $fp,0($fp)
addi $sp,$sp,4
jr $ra