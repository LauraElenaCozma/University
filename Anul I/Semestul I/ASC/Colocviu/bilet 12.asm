.data
prim: .ascii "d"
ult: .ascii "l"
a: .ascii "a"
sir: .space 400

.text
main:
subu $sp,$sp,12
la $t0,sir
sw $t0,8($sp)
lb $t0,prim
sb $t0,4($sp)
lb $t0,ult
sb $t0,0($sp)

jal succesor

addi $sp,$sp,12
li $v0,4
la $a0,sir
syscall
li $v0,10
syscall

succesor:
subu $sp,$sp,4
sw $fp,0($sp)
addi $fp,$sp,4   #sp:(fp vechi) fp: (ult)(prim)(sir)

lb $t0,4($fp)
lb $t1,0($fp)
lb $t2,a
lw $t3,8($fp)
for:
sb $t0,0($t3)
ble $t0,$t1, continuaFor
   j FinalulProcedurii
   
continuaFor:
   #li $v0,11
   #move $a0,$t0
   #syscall
   sub $t0,$t0,$t2
   addi $t0,$t0,1
   
   add $t0,$t0,$t2
    addi $t3,$t3,1
  j for

FinalulProcedurii:
sb $zero,0($t3)
lw $fp,-4($fp)
addi $sp,$sp,4
jr $ra
