.data
sir: .asciiz "()()"
deschis: .byte '('
inchis : .byte ')'
.text
main:

subu $sp,$sp,4
la $t0,sir
sw $t0,0($sp)

jal paranteze

addi $sp,$sp,4

move $t0,$v0
li $v0,1
move $a0,$t0
syscall

li $v0,10
syscall

paranteze:
li $v0,1
li $t1,0
lb $t2,deschis #t2=(
lb $t3,inchis #t3=)
subu $sp,$sp,8
sw $s0,0($sp)
sw $fp,4($sp)
move $fp,$sp   #sp:fp: (s0 vechi)(fp vechi)(sir)
lw $t0,8($fp)  #t0=sir
for:
lb $s0,0($t0)
bne $s0,$zero,NuEFinal
  j iesireProcedura
NuEFinal:
  beq $s0,$t2,Deschisa
      sub $t1,$t1,1
      j Comparatie
  Deschisa:
      addi $t1,$t1,1
  Comparatie:
      bltz $t1,PreaMulteInchise  #t1<0?
          j Continuare
      PreaMulteInchise:
          li $v0,0
          j iesireProcedura
      
  Continuare:
  addi $t0,$t0,1
  j for

iesireProcedura:
 
lw $s0,0($sp)
lw $fp,4($fp)
addi $sp,$sp,8

bnez $t1,Incorect
    jr $ra
Incorect:
    li $v0,0
    jr $ra