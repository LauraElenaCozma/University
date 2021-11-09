.data
x: .word 3
y: .word 1
z: .word 20

.text
   main:
      lw $t0,x
      lw $t1,y
      lw $t2,z
      bgt $t0,$t1 et1   #if(x>y)
      et1:  #x<=y
          lw 
      