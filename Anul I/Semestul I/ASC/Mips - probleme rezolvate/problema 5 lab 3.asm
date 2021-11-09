.data
n: .word 7
c: .byte 'b'
sir: .space 200
.text
main:

  subu $sp,$sp,8
  lw $t0,n
  sw $t0,0($sp)
  lb $t0,c
  sb $t0,4($sp)
  
  jal construireSir
  
  move $t0,$sp
  addi $sp,$sp,1
  lw $t1,n
  add $sp,$sp,$t1

  lw $t1,n
  addi $t1,$t1,1
  li $t2,0
  la $t3,sir
  copiere:
 
  bge $s0,$t1,iesireCopiere
     lw $t4,0($t0)
     sb $t4,0($t3)
     addi $t0,$t0,4
     addi $t3,$t3,1
     addi $s0,$s0,1
     j copiere
  
  iesireCopiere:
  li $v0,4
  la $a0,sir
  syscall
  li $v0,10
  syscall
  
  
construireSir:
  subu $sp,$sp,8
  sw $fp,0($sp)
  sw $s0,4($sp)
  move $fp,$sp  #sp:fp:(fp vechi)(s0 vechi)(n)(c)
  
  lw $t0,8($fp)
  addi $t0,$t0,1
  add $t0,$t0,$t0
  add $t0,$t0,$t0
  sub $sp,$sp,$t0
  lw $t0,0($fp)  #copiem pe noua pozitie fp vechi
  sw $t0,0($sp)
  
  lw $t0,4($fp)  #copiem pe noua pozitie s0 vechi
  sw $t0,4($sp)
  
  lw $t0,8($fp)  #copiem pe noua pozitie n
  sw $t0,8($sp)
  
  lb $t0,12($fp)  #copiem pe noua pozitie c
  sb $t0,12($sp)
  
  addi $t2,$fp,12   #coada sirului
  addi $fp,$sp,8
  
  
  li $s0,0        #i=0
  lw $t0,0($fp)   #t0=n
  lb $t1,4($fp)   #t1=c
  
  sw $zero,0($t2)
  subu $t2,$t2,4
  
  for:
  bge $s0,$t0,iesireFor
      sb $t1,0($t2)
      subu $t2,$t2,4
      addi $s0,$s0,1
      j for
  iesireFor:
  
  lw $s0,-4($fp)
  lw $fp,-8($fp)
  
  addi $sp,$sp,16
  
  jr $ra
  