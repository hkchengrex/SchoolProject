#------- Data Segment ----------
.data

# Define the string messages
msg0:   .asciiz "Please enter the Multiplicand [0-255]: "
msg1:   .asciiz "Please enter the Multiplier   [0-255]: "
msg2:	.asciiz "The number should be from 0 to 255!\n "
msg3:   .asciiz "The result at the current iteration is: "
msg4:   .asciiz "\n"
msg5:	.asciiz "The product is: "

#------- Text Segment ----------
.text
.globl main
main:

# Get the first input value (multiplicand) from user (and store in $s0 )
# if the number is not within the correct range 0-255, display
# error msg and ask for input again
input1:
	la $a0, msg0 #prompt user input
	li $v0, 4
	syscall
	
	li $v0, 5 #get integer in $v0
	syscall
	
	jal checkvalid
	
	add $s0,$zero,$v0 #store the first input (multiplicand) in $s0
	bne $zero,$v1,input2#input is correct, get the second input
	jal input_error
	j   input1

#TODO 1: get the multiplier and store it in $s1	
# You can add labels below as you wish
# Get the second input value (multiplier) from user (and store in $s1 )
# if the number is not within the correct range 0-255, display
# error msg and ask for input again			
input2:
	la $a0, msg1 #prompt user input
	li $v0, 4
	syscall
	
	li $v0, 5 #get integer in $v0
	syscall
	
	jal checkvalid
	
	add $s1, $zero, $v0 #store the second input in $s1
	bne $zero, $v1, input_correct #input is correct, proceed
	jal input_error
	j   input2

#TODO 1 above

#assume inputs are correct then $s0 stores the multiplicand
#$1 stores the multiplier. 
#do the calculation by shifting, accumulate the results to $s2
input_correct:

	add  $s2,$zero,$zero
	addi $s3,$zero,1
	add  $s4,$zero,$zero
	addi $s5,$zero,8
		
#TODO 2: perform the multiplication steps accumulate results in $s2
# You can add labels below as you wish
#multiply $s0 by $s1 using sll
#do the calculation, accumulate the result to $s2
#output the value of $s2 at the current iteration
#When you output, please use syscall 34 (instead of syscall 1) to print the results in hexadecimal form
#for example if you wish to print a number stored in $s2 in hexadecimal form
#you need to copy 34 into $v0, and then copy $s2 into $a0 as shown below
#	addi $v0,$zero,34
#	add  $a0,$s2,$zero
#       syscall
#Once you are done with all the iterations, output the final product also in hexadecimal form

addi $t0, $zero, 8
addi $t1, $zero, 1
LoopStart:
	beq $t0, $zero, LoopEnd
	
	and $t2, $t1, $s1
	beq $t2, $zero, NoAdd
	addi $t3, $t0, -8 #t3 is shift amount
	sub $t3, $zero, $t3 #invert sign
	
	sllv $t4, $s0, $t3
	add $s2, $s2, $t4
	
	NoAdd:
	
	la $a0, msg3
	li $v0, 4
	syscall
	
	jal Prints2
	
	la $a0, msg4
	li $v0, 4
	syscall
	
	sll $t1, $t1, 1
	addi $t0, $t0, -1
	j LoopStart

LoopEnd:
	la $a0, msg5
	li $v0, 4
	syscall
	jal Prints2
	j end

Prints2:
	add $a0, $zero, $s2
	li $v0, 34
	syscall
	jr $ra


#TODO 2 above




#display the error message to indicate input error
input_error:
	addi $sp,$sp,-4
	sw   $ra,0($sp)

	la $a0,msg2
	li $v0,4
	syscall
	
	lw   $ra,0($sp)
	addi $sp,$sp,4
	
	jr $ra
	

#checks whether the value in $v0 is within [0-255]
#return 1 in $v0 if the value is within the range
#return 0 in $v0 otherwise
checkvalid:

	addi $sp,$sp,-4
	sw   $ra,0($sp)
	
	slti $t0,$v0,256
	sub  $t1,$zero,$v0
	slti $t2,$t1,1
	and  $v1,$t0,$t2
	
	lw   $ra,0($sp)
	addi $sp,$sp,4
	
	jr $ra	

#This is the end of the program	
end:
	li $v0, 10
	syscall

