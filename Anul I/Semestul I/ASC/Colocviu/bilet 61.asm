.data
v: .word  3 32 3 9 9
n: .word 5
gasitst: .byte 0
gasitdr: .byte 0
mesajnegativ: .asciiz "nu exista"
mesajpozitiv: .asciiz "exista"

.text
main:

subu $sp,$sp,8
la $t0,v
sw $t0,4($sp)
lw $t0,n
sw $t0,0($sp)

jal distanta

move $t0,$v0
li $t1,-1



beq $t0,$t1,nuSuntPare
    li $v0,4
    la $a0,mesajpozitiv
    syscall
    j return0

nuSuntPare:
   li $v0,4
   la $a0,mesajnegativ
   syscall
return0:
li $v0,10
syscall

distanta:

subu $sp,$sp,12
sw $fp,8($sp)
sw $s0,4($sp)
sw $s1,0($sp)

addi $fp,$sp,12   #sp:(s1 vechi)(s0 vechi)(fp vechi)fp:(n)(v)

lw $s0,4($fp) #s0=v
lw $t0,0($fp) #t0=n

move $s1,$s0
move $t1,$t0
subu $t1,$t1,1
mulo $t1,$t1,4
add $s1,$s1,$t1  #s1 indica ultima pozitie in vector


li $t1,2
while:
bgt $s0,$s1,iesireWhile

   lb $t2,gasitst
   lb $t3,gasitdr
   bne $t2,$t3,nuegale
     beqz $t2,paritates0
        j iesireWhile  #ambele sunt 1
   nuegale:
       beqz $t2,paritates0
        j paritates1  #nu e gasit primul
     
   paritates0:
   lw $t2,0($s0) #numarul de la adresa s0
   div $t2,$t1
   mfhi $t3
   
   beqz $t3,primulPar
     addi $s0,$s0,4
     j paritates1
   primulPar:
     li $t2,1
     sb $t2,gasitst
     j paritates1
     
   lw $t3,gasitdr
   
   beqz $t3,paritates1
     j while #am gasit deja primul nr par
   
   paritates1:
   
   lw $t2,0($s1) #numarul de la adresa s1
   
   div $t2,$t1
   mfhi $t3
   
   beqz $t3,ultimulPar
     subu $s1,$s1,4
     j while
   ultimulPar:
     li $t2,1
     sb $t2, gasitdr
     
     j while
     
     
   
iesireWhile:
bgt $s0,$s1,depasire
   subu $t0,$s1,$s0
   li $t1,4
   div $t0,$t1
   mflo $v0
   j iesireFunctie
depasire:
  li $v0,-1
iesireFunctie:
sw $s0,-8($fp)
sw $s1,-12($fp)
lw $fp,-4($fp)
jr $ra
  
   




