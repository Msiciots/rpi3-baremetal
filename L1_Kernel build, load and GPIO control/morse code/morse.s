.section .init
.global _start
@------------------
@SETUP VALUES
@------------------
.equ BASE,  0x3f200000 @Base address
.equ GPFSEL2, 0x08			@FSEL2 register offset 
.equ GPSET0,  0x1c			@GPSET0 register offset
.equ GPCLR0,0x28			@GPCLR0 register offset
.equ SET_BITSEL,   0x09		@sets bit three b1001 ,set gpio 20 21
.equ SET_pin20,  1<<20 	    @sets gpio 20 
.equ SET_pin21,  1<<21 	    @sets gpio 21
.equ COUNTER, 0xfffff
@------------------
@Start label
@------------------
_start:
@------------------
@load register with BASE
@------------------
ldr r0,=BASE
@------------------
@Load register with COUNTER
@------------------
ldr r2,=COUNTER
@------------------
@Set bit 3 in GPFSEL2
@------------------
ldr r1,=SET_BITSEL
str r1,[r0,#GPFSEL2]
@------------------
@Set bit 21 in GPSET0
@------------------
ldr r1,=SET_pin20
@ ldr r3,=SET_pin21
str r1,[r0,#GPSET0]

.macro delay count 
mov r3, #\count
mov r4,#0
1:
	mov r10,#0
	2: @loop to large number
	add r10,r10,#1
	cmp r10,r2	
	bne 2b
add r4,r4,#1
cmp r4,r3	
bne 1b
.endm


Infinite_loop:
	@ show "R"
	str r1,[r0,#GPSET0]	//short
	delay 1
	str r1,[r0,#GPCLR0]	// gap
	delay 1
	str r1,[r0,#GPSET0]	// long
	delay 3
	str r1,[r0,#GPCLR0]	// gap
	delay 1
	str r1,[r0,#GPSET0]	// short
	delay 1
	str r1,[r0,#GPCLR0]	// end
	delay 3

	@ show "T"
	str r1,[r0,#GPSET0]	// long
	delay 3
	str r1,[r0,#GPCLR0]	// end
	delay 3
	
	@ show "E"
	str r1,[r0,#GPSET0]	// short
	delay 1
	str r1,[r0,#GPCLR0]	// end
	delay 3
	
	@ show "S"
	str r1,[r0,#GPSET0]	// short
	delay 1
	str r1,[r0,#GPCLR0]	// gap
	delay 1
	str r1,[r0,#GPSET0]	// short
	delay 1
	str r1,[r0,#GPCLR0]	// gap
	delay 1
	str r1,[r0,#GPSET0]	// short
	delay 1
	str r1,[r0,#GPCLR0]	// end of words
	delay 7


b Infinite_loop


