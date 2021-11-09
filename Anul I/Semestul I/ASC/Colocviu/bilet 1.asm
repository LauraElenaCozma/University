.data
sir: .asciiz "cozma"
n: .word 5

.text
main:
subu $sp,$sp,8
la $t0,sir
sw $t0,4($sp)
lw $t0,n
sw $t0,0($sp)

jal inversare

li $v0,4
la $a0,sir
syscall 

addi $sp,$sp,8

li $v0,10
syscall

inversare:
subu $sp,$sp,12
sw $s0,0($sp)
sw $s1,4($sp)
sw $fp,8($sp)
addi $fp,$sp,12  #sp:(s0 vechi)(s1 vechi)(fp vechi)fp:(n)(sir)

lw $s0,4($fp)   #t0=sir
lw $t1,0($fp)   #t1=n
sub $t1,$t1,1 
move $s1,$s0
add $s1,$s1,$t1
for:
ble $s0,$s1, NuSuntEgale
   j iesireFor
NuSuntEgale:
   lb $t2,0($s0)
   lb $t3,0($s1)

   sb $t2,0($s1)
   sb $t3,0($s0)
   addi $s0,$s0,1
   subu $s1,$s1,1
   j for

iesireFor:
lw $fp,-4($fp)
lw $s0,-8($fp)
lw $s1,-12($fp)
jr $ra

