.data
n: .word 3
s: .space 4

.text 
     main:
       li $t0,0    #s=0
       li $t1,1    #i=1
       lw $t2,n    #t2=n
       add $t2,$t2,1  #t2=n+1
       
     for:
        bge $t1,$t2,iesire  #if(i>=n+1) goto(iesire)
        add $t0,$t0,$t1     #t0=t0+t1 <=> s=s+i
        addi $t1,$t1,1      #i++
        j for
        
     iesire:
        move $a0,$t0
        li $v0,1
        syscall
        li $v0,10
        syscall