.data
x: .word 3
v: .word 11,1,9,3,2,9
n: .word 6
y: .byte 0

.text
   main:
     li $t0,0
     lw $t1,n
     lw $t4,x
     
   for:
     bge $t0,$t1,iesire       #if(t0>=t1) go to iesire
       add $t2,$t0,$t0        #t2=2*t0
       add $t2,$t2,$t2        #t2=2*t2=4*t0
       lw $t3,v($t2)
       
       beq $t3,$t4,gasit          #if t3==t4
            addi $t0,$t0,1       #daca nu l-am gasit, continuam
            j for
       
       gasit:
           li $t4,1
           sw $t4,y
           #j iesire
           
    iesire:
     li $v0,1
     lw $a0,y
     syscall
     
     li $v0,10
     syscall
         
      
