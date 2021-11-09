.data
a: .word 2
n: .word 4
p: .word 3 -3 1 4 2
mesajzero: .asciiz "\nzero"
mesajdif: .asciiz "\ndiferit de 0"
.text
main:

subu $sp,$sp,12
lw $t0,a
sw $t0,8($sp)
lw $t0,n
sw $t0,4($sp)
la $t0,p
sw $t0,0($sp)


jal polinom

move $t0,$v0

move $a0,$v0

li $v0,1
syscall

li $v0,4
beqz $t0,egalCuZero
   la $a0,mesajdif
   syscall
   j return0
egalCuZero:
la $a0,mesajzero
syscall

return0:
li $v0,10
syscall

polinom:
subu $sp,$sp,4
lw $fp,0($sp)
move $fp,$sp #fp:sp: (fp vechi)(p)(n)(a)

lw $t0,4($fp)
lw $t1,8($fp) #t1=n
lw $t2,12($fp) #t2=a

move $t3,$t1
mulo $t3,$t3,4

add $t0,$t0,$t3
lw $v0,0($t0)
for:
subu $t0,$t0,4
subu $t1,$t1,1
bltz $t1,finalFor
   mulo $v0,$v0,$t2
   lw $t3,0($t0)
   add $v0,$v0,$t3
   
   j for
finalFor:

sw $fp,0($fp)
addi $sp,$sp,4

jr $ra





