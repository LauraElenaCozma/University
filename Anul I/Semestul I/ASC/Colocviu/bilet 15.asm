.data
sir: .asciiz "universitate"
n: .word 2
rezultat: .space 10
mesaj: .asciiz "n nu se incadreaza in sir\n"
.text
main:

subu $sp,$sp,8
lw $t0,n
sw $t0,4($sp)
la $t0,sir
sw $t0,0($sp)

jal caracter


li $t0,-1
bne $v0,$t0,afisCaracter

  li $v0,4      #n nu e potrivit. ori prea mic, ori prea mare
  la $a0,mesaj
  addi $sp,$sp,8
  syscall
  j return0
  
afisCaracter:

   move $t0,$v0
   la $t1,rezultat
   sb $t0,0($t1)
   addi $t1,$t1,1
   sb $zero,0($t1)
   addi $sp,$sp,8
   
   li $v0,4
   la $a0,rezultat
   syscall

return0:
li $v0,10
syscall


caracter:

subu $sp,$sp,4
sw $fp,0($sp)
addi $fp,$sp,4  #sp:(fp vechi)fp:(sir)(n)

lw $t0,0($fp)   
lw $t1,4($fp)  #t1=n



li $t2,1

beqz $t1,neste0


for:
bge $t2,$t1,iesireFor
     lb $t3,0($t0)
     
     beq $t3,$zero,nInvalid
        addi $t0,$t0,1
        addi $t2,$t2,1
        j for
     nInvalid:
        lw $fp,-4($fp)
        addi $sp,$sp,4
        li $v0,-1
        jr $ra
        
        
     
iesireFor:
  lb $v0,0($t0)   #al n-lea caracter al stringului
  lw $fp,-4($fp)
  addi $sp,$sp,4  
  jr $ra
   
   
neste0:
  
  li $v0,-1
  lw $fp,-4($fp)
  addi $sp,$sp,4
  jr $ra