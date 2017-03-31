#------- Data Segment ----------
.data
# Define the string messages
msg1:	.asciiz "Please enter the message all in capital letters: "
msg2:	.asciiz "Please enter the shift amount: "
msg3:   .asciiz "The encrypted text is: "
newline:.asciiz "\n"
input: .byte 0:100 #assume max input is 99-character

#------- Text Segment ----------
.text
.globl main
main:

# Print msg1
Label:	la $a0, msg1
	li $v0, 4
	syscall


# This is the syscall 8 to get the input string
# After the syscall, the string is loaded to the .byte array "input"
# the syscall will put a special LineFeed character to the end of the string
# just in front of the end of string character.
# i.e. if you enter "ABC", it will be stored as [A][B][C][LF][0] in the byte array "input"
# the LineFeed is due to the "Enter" key you pressed when you enter the string
	li $v0,8
	la $a0,input
	li $a1,100
	syscall


	la $a0, msg2
	li $v0, 4
	syscall

# Get the input shift amount from user (and store in $v0)
# assume the shift amount is always less than 26	 
	li $v0, 5
	syscall

# Copy the shift amount value to $s0, because we need to change $v0 for syscalls
# after this line $s0 contains the shift amount
        add $s0, $zero, $v0	

                

# TODO: Fill in your code below 
# You can add labels below as you wish
# load the letters (lbu) one by one from the address indicated by $s1
# then call the encrypt function to encrypt the letter 
# assume the letter is in $a2 and the encrypted letter is returned in $v1
# Assume the input can consists of *capital letters* and *spaces*
# Whenever you encounter a *space* (ASCII value 0x20) *DO NOT ENCRYPT it*
# Whenever you encounter a *LineFeed* (ASCII value 0xA) you have reached the end of the string, 
# you should stop encryption and process the string by putting '\0' (ASCII 0x0) in place of the LineFeed
# the LineFeed is due to the "Enter" key you pressed when you enter the string












#TODO 1 above
        
#Encryption done, print the result 
print:
	la $a0, msg3      # Output msg3
	li $v0, 4
	syscall
	
        add $a0,$s1,$zero   #$s1 contains the starting address of the input
	li $v0, 4           # output encrypted msg
	syscall
	
        j end	





# TODO 2: Fill in your code below 
# You can add labels below as you wish
# each time encrypts a single character
# assume the character is in $a2, and the return value in $v1
# assume all characters in the input string are capital characters
# ASCII code for 'A' is 0x41 ,and for 'Z' is 0x5A
encrypt:




















#TODO 2 above

#This is the end of the program
end:
        li $v0, 10
        syscall


