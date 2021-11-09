.data
v: 2 8 0
n: .space 4
.text
main:
subu $sp,$sp,4
la $t0,v
sw $t0,0($sp)

jal numarElemente

subu $sp,$sp,4
lw $t0,n
sw $t0,0($sp) #sp:(n)(v)

jal afisareVector


addi $sp,$sp,8
li $v0,10
syscall

numarElemente:
subu $sp,$sp,4
sw $fp,0($sp)
move $fp,$sp   #fp:sp;(fp vechi)(v)
lw $t0,4($fp)
li $t2,0 #t2=nr elemente nenule
for:
lw $t1,0($t0)  #t1=v[0]

beqz $t1,FinalulVectorului
   addi $t2,$t2,1
   addi $t0,$t0,4 #trecem la umratorul element
   j for
FinalulVectorului:
   sw $t2,0($t0)
   sw $t2,n

lw $fp,0($fp)
addi $sp,$sp,4
jr $ra


afisareVector:
subu $sp,$sp,4
sw $fp,0($sp)
move $fp,$sp #fp:sp:(fp vechi)(n)(v)

lw $t0,8($fp)#t0=v
lw $t1,4($fp) #t1=n
li $t2,0

For:
bne $t2,$t1, FinalFor   #sa se mai verifice aici, sunt micute probleme
   lw $t3,0($t0)
   li $v0,1
   move $a0,$t3
   syscall
   addi $t0,$t0,4
   addi $t2,$t2,1
   j For
FinalFor:
lw $fp,0($fp)
addi $sp,$sp,4

jr $ra