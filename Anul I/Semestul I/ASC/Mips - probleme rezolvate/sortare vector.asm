.data
v: .word 9,8,7,691,5,487,6,3,214,1,52
n: .word 11
spatiu: .asciiz " "

.text
    main:
       lw $t1,n
       li $t0,2
       sub $t1,$t1,$t0  #$t1=n-2
       li $t0,4
       mul $t1,$t1,$t0 #$t1=$t1*4
       
       li $t2,1        #ok=1
       
    while:
       
       bnez $t2,sortare  #bubble sort. cand t2=0 ne oprim
          j final        #ok=0 deci iesim
       
       sortare:
          li $t2,0       #ok=0
          li $t0,0       #i=0
        for:
          ble $t0,$t1,continuaFor #t0<=t1
                j while
         continuaFor:
                move $t3,$t0     
                addi $t3,$t3,4    #=i+1
                lw $s0,v($t0)
                lw $s3,v($t3)
                bgt $s0,$s3,interschimb     #s0>s3
                    addi $t0,$t0,4         #s0<=s3    t0+=4
              
                    j for
                
                interschimb:
                    li $t2,1                #ok=1
                    sw $s0,v($t3)
                    sw $s3,v($t0)
                    addi $t0,$t0,4       
                    j for
                
                
       final:
             li $t0,4
             lw $t1,n
             subi $t1,$t1,1
             mul $t1,$t1,$t0
             li $t0,0
             
          forafis: 
             ble $t0,$t1,continua
                j iesire   
             continua:
                 
                 lw $t2,v($t0)
                 addi $t0,$t0,4 
                 li $v0,1
                 move $a0,$t2
                 syscall
           
                 li $v0,4
                 la $a0,spatiu
                 syscall
                 
                
                 
                 j forafis
            
       iesire:
         li $v0,10
         syscall
             
       
