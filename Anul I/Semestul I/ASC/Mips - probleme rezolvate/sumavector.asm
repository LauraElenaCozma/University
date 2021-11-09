.data
v: .word 6,1,8,-2,3
n: .word 5
s: .space 4


.text
   main:
    li $t0,0 #registru pentru suma. s=0
    li $t1,0 #i=0
    lw $t2,n
    
   for:
     bge $t1,$t2,iesire  #if (i>=n) goto(iesire)
         add $t3,$t1,$t1 #t3=i+i=2i
         add $t3,$t3,$t3 #t3=4i
         lw $t3,v($t3)   #t3=v[i]
         add $t0,$t0,$t3 #s=s+v[i]
         addi $t1,$t1,1  #i++
         j for           #daca nu facem, mergem la final
     
   iesire:

         move $a0,$t0  #a0=t0
         li $v0,1
         syscall
         li $v0,10
         syscall