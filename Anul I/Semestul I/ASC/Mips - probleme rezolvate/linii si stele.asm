.data
stea:    .asciiz "*"
linie:   .asciiz "-"
newLine: .asciiz "\n"
s1:      .word 1
s2:      .word 1

.text
   main:
     li $s0,0
     
     for: 
       li $t0,3
       
       bge $s0,$t0, iesireFor
         
         mulo $t0,$s0,$s0
         lw $t1,s1
         add $t1,$t1,$t0
         sw $t1,s1
         #li $v0,1
         #move $a0,$t1
         #syscall
         subu $sp,$sp,4
         sw $t0,0($sp)
         
         jal afisare_s1
         
         lw $t0,0($sp)
         addi $sp,$sp,4
         
         mulo $t0,$t0,$s0 #to=i*i*i
         lw $t1,s2
         add $t1,$t1,$t0
         sw $t1,s2
         
         jal afisare_s2
         
         
         add $s0,$s0,1
         j for
         
     iesireFor:
        li $v0,10
        syscall
        
   afisare_s1:
   subu $sp,$sp,4
   sw $s0,0($sp)
   
   lw $t0,s1
   li $s0,0

   for_s1:
     bge $s0,$t0, iesireFor_s1
     li $v0,4
     la $a0,stea
     syscall
     addi $s0,$s0,1
     j for_s1
     
   iesireFor_s1:
   #afisare \n
   
   li $v0,4
   la $a0,newLine
   syscall
   
   lw $s0,0($sp)
   addi $sp,$sp,4
   jr $ra
   
   afisare_s2:
   subu $sp,$sp,4
   sw $s0,0($sp)
   
   li $s0,0
   lw $t0,s2
   for_s2:
     bge $s0,$t0, iesireFor_s2
     li $v0,4
     la $a0,linie
     syscall
     
     addi $s0,$s0,1 #i++
     j for_s2
     
   iesireFor_s2:
   #afisare \n
   
   li $v0,4
   la $a0,newLine
   syscall
   
   lw $s0,0($sp)
   addi $sp,$sp,4
   jr $ra
   
   
     