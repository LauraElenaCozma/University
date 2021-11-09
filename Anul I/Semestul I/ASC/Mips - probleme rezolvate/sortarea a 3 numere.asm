.data
   x: .word 20
   y: .word 1
   z: .word 3
   spatiu: .asciiz " "

.text
    lw $t0,x
    lw $t1,y
    comp1:
    bgt $t0,$t1,XMaiMareCaY
         j comp2
    XMaiMareCaY:
   # add $t0,$t0,$t1
   # sub $t1,$t0,$t1       Interschimbare propriu-zisa
   # sub $t0,$t0,$t1 
    sw $t0,y
    sw $t1,x
   
     comp2:
     lw $t1,z
     bgt $t0,$t1,XMaiMareCaZ
         j comp3
    XMaiMareCaZ:
    sw $t0,z
    sw $t1,x
    
    
    comp3:
    lw $t0,y
     bgt $t0,$t1,YMaiMareCaZ
         j final
    YMaiMareCaZ:
    sw $t0,z
    sw $t1,y
    
    
    final:
    li $v0,1
    lw $a0,x
    syscall
    
    li $v0,4
    la $a0,spatiu
    syscall
    
    li $v0,1
    lw $a0,y
    syscall
    
    li $v0,4
    la $a0,spatiu
    syscall
    
    li $v0,1
    lw $a0,z
    syscall
    
    li $v0,10
    syscall
