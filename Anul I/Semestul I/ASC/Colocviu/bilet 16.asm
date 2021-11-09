.data
sir: .asciiz "anisoara"
c: .byte 'k'
n: .word 6
mesaj: .asciiz "n e mai mare decat lungimea sirului "
.text
main:
subu $sp,$sp,12
la $t0,sir
sw $t0,0($sp)
lb $t0,c
sb $t0,4($sp)
lw $t0,n
sw $t0,8($sp)

jal inlocuire

addi $sp,$sp,12

li $v0,4
la $a0,sir
syscall

li $v0,10
syscall

inlocuire:
subu $sp,$sp,8
sw $fp,0($sp)
sw $s0,4($sp)
addi $fp,$sp,8  #sp:(fp vechi)(s0 vechi) fp:(sir)(c)(n)

lw $t0,0($fp)#t0=sir
lw $t1,4($fp)#t1=c
lw $t2,8($fp) #t2=n

li $s0,0
for:
lb $t3,0($t0) #t3=sir[i]
bge $s0,$t2,iesireFor   #if s0>=t2
     beq $t3,$zero,NULL
       j continuare
    NULL:
       li $v0,4
       la $a0,mesaj
       syscall
       
       j iesireFunctie
       
       
     continuare:
       addi $t0,$t0,1
       addi $s0,$s0,1
       j for

iesireFor:    
sb $t1,0($t0)

iesireFunctie:  
lw $s0,-4($fp)
lw $fp,-8($fp)
addi $sp,$sp,8

jr $ra

syscall