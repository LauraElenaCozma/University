.data
n: .word 53764

.text
main:

subu $sp,$sp,4
lw $t0,n
sw $t0,0($sp)

jal sumaCifre

addi $sp,$sp,4

move $t0,$v0

li $v0,1
move $a0,$t0
syscall

li $v0,10
syscall



sumaCifre:

subu $sp,$sp,8

sw $fp,0($sp)

sw $ra,4($sp) 

move $fp,$sp #fp:sp:(fp vechi)(ra vechi)(n)

lw $t0,8($fp)

beqz $t0,conditieOprire
    
    li $t1,10
    div $t0,$t0,$t1
    mflo $t0
    mfhi $t1
    subu $sp,$sp,4
    sw $t1,0($sp)
    subu $sp,$sp,4
    sw $t0,0($sp)
    
  #  li $v0,1
   # move $a0,$t0
    #syscall
    jal sumaCifre
    
    lw $t0,-4($fp) #cifra
    add $v0,$v0,$t0
    addi $sp,$sp,8
    
    lw $ra,4($fp)
    lw $fp,0($fp)
    
    addi $sp,$sp,8
   
    jr $ra
    
conditieOprire:
    li $v0,0
    
    lw $ra,4($fp)
    lw $fp,0($fp)
    
    addi $sp,$sp,8
    
    jr $ra