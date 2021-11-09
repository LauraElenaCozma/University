.data
v: .asciiz "3092"
val_zero: .ascii "0"
.text
main:

la $t0,v
subu $sp,$sp,4
sw $t0,0($sp)

jal succesor

li $v0,4
la $a0,v
syscall

addi $sp,$sp,4

li $v0,10
syscall

succesor:
subi $sp,$sp,8
sw $s0,4($sp)
sw $fp,0($sp)   #scum stiva e sp:(fp vechi)(s0 vechi)(v)
move $fp,$sp
lw $t0,8($fp)  #t0=v
ia_primul_caracter:
lb $s0,0($t0)   #prima cifra din sir, adica 9
li $t2,9
lb $t3,val_zero
sub $s0,$s0,$t3 #s0=s0-"0"

for:
beq $s0,$t2,EgalCu9
  j iesireFor
EgalCu9:
 # li $v0,1
 # move $a0,$s0
 # syscall
  sb $t3,0($t0)
  addi $t0,$t0,1
  j ia_primul_caracter
  
  
iesireFor:

add $s0,$s0,$t3

bne $s0,$zero,incrementare
   j iesireFunctie #am ajuns la null
incrementare:
sub $s0,$s0,$t3 #s0=s0-'0'
addi $s0,$s0,1#s0++
add $s0,$s0,$t3#transformam iar in caracter
sb $s0,0($t0)

iesireFunctie:
lw $s0,4($fp)
lw $fp,0($fp) 
addi $sp,$sp,8
jr $ra

