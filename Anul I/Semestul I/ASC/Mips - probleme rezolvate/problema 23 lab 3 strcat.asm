.data
sir1: .asciiz "bun"
sir2: .asciiz " venit"

.text
main:

subu $sp,$sp,8
la $t0,sir1
sw $t0,0($sp)
la $t0,sir2
sw $t0,4($sp)

jal strcat

li $v0,4
la $a0,sir1
syscall

li $v0,10
syscall

strcat:

subu $sp,$sp,4
sw $fp,0($sp)

addi $fp,$sp,4 #sp:(fp vechi)fp:(sir1) (sir2) (dest)

lw $t0,0($fp)
lb $t1,0($t0)

for1:
beq $t1,$zero,iesireFor1
    addi $t0,$t0,1
    lb $t1,0($t0)
    j for1
    
iesireFor1:
    
#acum t0 pointeaza catre null din primul sir

lw $t1,4($fp)
lb $t2,0($t1)

for2:
beq $t2,$zero,iesireFor2
    sb $t2,0($t0)
#    li $v0,4
 #   la $a0,sir1
  #  syscall
    addi $t0,$t0,1
    addi $t1,$t1,1
    lb $t2,0($t1)
    j for2
    
iesireFor2:
sb $zero,0($t0)

lw $fp,-4($fp)

jr $ra

