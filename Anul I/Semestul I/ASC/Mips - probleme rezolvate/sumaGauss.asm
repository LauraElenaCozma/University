.data
n: .word 10


.text
     lw $t0,n
     lw $t1,n
     add $t1,$t1,1
     mul $t0,$t0,$t1
     li $t2,2
     div $t0,$t2
     mflo $t3
     
     
     move $a0,$t3
     li $v0,1
     syscall
     li $v0,10
     syscall
