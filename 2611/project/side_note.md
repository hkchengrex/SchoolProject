s0 -- total number of fuels in a game level
s1 -- total number of aerolites in a game level
s2 -- current game score
s3 -- current game level
s4 -- status flag of bomb in a game level
s6 -- starting time of a game iteration

msg0:	.asciiz "Enter the number of fuels (max. limit of 10) you want? "
msg1:	.asciiz "Invalid size!\n"
msg2:	.asciiz "Enter the seed for random number generator? "
msg3:	.asciiz "You won!"
msg4:	.asciiz "You lost!"
newline: .asciiz "\n"

0 background.jpg
1 spaceship_right.png
2 spaceship_left.png
3 aerolite_right.png
4 aerolite_left.png
5 aerolite_d_right.png
6 aerolite_d_left.png
7 fuel_right.png
8 fuel_left.png
9 bomb.png
10 spaceship_up.png
11 spaceship_down.png

speed:	.word	8

spaceship:	.word 384 384 1 10 0	# 5 words for 5 properties of the ship: (in this order) top-left corner's x-coordinate, top-left corner's y-coordinate, image index, speed_h, speed_v
spaceshipSize: .word 32	32		# spaceship image's width and height

aerolites:	.word -1:500		# 5 words for each aerolite: (in this order) top-left corner's x-coordinate, top-left corner's y-coordinate, image index, speed, Hit point  
aeroliteSize: .word 60 60			# aerolite image's width and height

fuels:	.word -1:500			# 5 words for each fuel: (in this order) top-left corner's x-coordinate, top-left corner's y-coordinate, image index, speed, status
fuelSize: .word 32 32			# fuel image's width and height

bombs:	.word 0 0 0 0 0 0 		# 6 words for the bomb: (in this order) top-left corner's x-coordinate, top-left corner's y-coordinate, image index, speed_x, speed_y, status  
bombSize: .word 15 15			# bomb image's width and height


# Function: check whether two rectangles (say A and B) intersect each other
# return $v0: 0 -- false, 1 -- true
# a0 = x-coordinate of the top-left corner of rectangle A
# a1 = y-coordinate of the top-left corner of rectangle A
# a2 = width of rectangle A
# a3 = height of rectangle A
# t0 = x-coordinate of the top-left corner of rectangle B
# t1 = y-coordinate of the top-left corner of rectangle B
# t2 = width of rectangle B
# t3 = height of rectangle B

isIntersected: