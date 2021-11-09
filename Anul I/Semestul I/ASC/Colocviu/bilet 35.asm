.data
v: .word 32 -1 -4 -2 54
n: .word 5
mesajPozitiv: .asciiz "Exista"
mesajNegativ: .asciiz "Nu exista"
.text
main:

     subu $sp,$sp,8
     la $t0,v
     sw $t0,0($sp)
     lw $t0,n
     sw $t0,4($sp)
     
     jal elementeZero
     
      addi $sp,$sp,8
      move $t0,$v0
      
      beqz $t0,esteZero
      li $v0,4
      la $a0,mesajPozitiv
      syscall
      j return0
      
     esteZero:
      li $v0,4
      la $a0,mesajNegativ
      syscall
      
     
     return0:
     li $v0,10
     syscall
     
elementeZero:
     subu $sp,$sp,8
     sw $fp,0($sp)
     sw $s0,4($sp) #acum stiva e sp: (fp vechi)(s0 vechi)(n)(v)
     move $fp,$sp
     
     li $v0,0 #presupunem ca nu contine elemente pozitive
     
     lw $t1,8($fp)  #t0=n
     lw $t0,12($fp) #acum t1 contine adresa vectorului
     li $s0,0
     
     for:
     bge $s0,$t0,iesireFor
         
         lw $t2,0($t1)
         
         #li $v0,1
         #move $a0,$t2
         #syscall
         bgez $t2,Pozitiv
            j continuare
         Pozitiv:
            li $v0,1
            j iesireFor
            
         continuare:
         addi $t1,$t1,4
         addi $s0,$s0,1
         j for
          
     iesireFor:
     
     lw $s0,4($fp)
     lw $fp,0($fp)
     
     addi $sp,$sp,8
     jr $ra
     