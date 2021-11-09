.text
   main:
      li $s0,10
       jal afisare
       jal spatiu
       jal increase
       jal spatiu
       jal afisare
        li $v0,10
        syscall
       
   
   
   
   
   increase:
       subi $sp,$sp,8
       sw $s0,0($sp)
       sw $ra,4($sp)
       
       addi $s0,$s0,10
       
       jal afisare 
       
       lw $s0,0($sp)
       lw $ra,4($sp)
       addi $sp,$sp,8
       
       jr $ra
       
       
    afisare:
       li $v0,1
       move $a0,$s0
       syscall
       
       jr $ra
       
    spatiu:
       li $v0,4
       la $a0,s
       syscall
       
       jr $ra
        
 .data
  s: .asciiz "\n"