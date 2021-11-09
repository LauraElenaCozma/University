.data

  x: .word 1
  y: .word 5
  z: .word 3 
  max: .space 4


.text
    main:
       
       lw $t0,x
       lw $t1,y
       lw $t2,z
      
       blt $t0,$t1 XMaiMareCaY
          
          blt $t1,$t2 YMaiMareCaZ
                  move $t3,$t2 
                  j final
             YMaiMareCaZ:
                  move $t3,$t1 
                  j final
       XMaiMareCaY:
          
           blt $t0,$t2 XMaiMareCaZ
                  move $t3,$t2
                  j final
             XMaiMareCaZ:
                  move $t3,$t0 
                  
       #afisare maxim
       
       final:
       sw $t3,max
       li $v0,1
       move $a0,$t3
       syscall
       
       #return 0
       li $v0, 10
       syscall
