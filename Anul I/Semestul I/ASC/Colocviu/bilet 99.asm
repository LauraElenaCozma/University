.data
n: .word 1205
k: .word 0
mesajPozitiv: .asciiz "exista"
mesajNegativ: .asciiz "nu exista"

.text
main:

subu $sp,$sp,8
lw $t0,n
sw $t0,4($sp)
lw $t0,k
sw $t0,0($sp)

li $v0,0

jal GasesteCifra


beq $v0,$zero,NuAGasit
   li $v0,4
   la $a0,mesajPozitiv
   syscall
   j FinalizareProgram
NuAGasit:
   li $v0,4
   la $a0,mesajNegativ
   syscall

FinalizareProgram:
addi $sp,$sp,8
li $v0,10
syscall

GasesteCifra:
subu $sp,$sp,4
sw $fp,0($sp)  #acum stiva e sp:(fp vechi)(k)(n)
addi $fp,$sp,4
lw $t0,4($fp)  #t0=n
lw $t1,0($fp)  #t1=k


subu $sp,$sp,8
sw $s0,-8($fp)
sw $s1,-12($fp)   #sp:(s1 vechi)(s0 vechi)(fp vechi)fp:(k)(n)
bnez $t0,while
   beq $t0,$t1,NumarZeroCifraZero
        jr $ra
   NumarZeroCifraZero:
        li $v0,1
        jr $ra
while:
beqz $t0,EgalCuZero
   #daca nu e egal t0 cu 0, adica daca mai sunt cifre
   #trebuie sa scoatem in t2 ultima cifra
   li $t2,10
   div $t0,$t2
   mflo $s0
   mfhi $s1
   move $t0,$s0  #t0 primeste noul nr fara ultima cifra

   beq $t1,$s1,CifreEgale#daca cifra e egala cu k
      j while
   CifreEgale:
     li $v0,1
     j while
   
   EgalCuZero:
   lw $s0,-8($fp)
   lw $s1,-12($fp)
   lw $fp,-4($fp)
   addi $sp,$sp,12
   
   jr $ra
     