.section .init
.global _start
@------------------
@SETUP VALUES
@------------------
.equ BASE,  0x3f200000 @Base address
.equ GPFSEL2, 0x08			@FSEL2 register offset 
.equ GPSET0,  0x1c			@GPSET0 register offset
.equ GPCLR0,0x28			@GPCLR0 register offset
.equ SET_BIT3,   0x09		@sets bit three b1001 ,set gpio 20 21
.equ SET_pin20,  1<<20 	    @sets gpio 20 
.equ SET_pin21,  1<<21 	    @sets gpio 21
.equ COUNTER, 0xf0000
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
ldr r1,=SET_BIT3
str r1,[r0,#GPFSEL2]
@------------------
@Set bit 21 in GPSET0
@------------------
ldr r1,=SET_pin20
ldr r3,=SET_pin21
str r1,[r0,#GPSET0]
@------------------
@MAKE LED BLINK
@------------------
@Infinite loop
@------------------
Infinite_loop:
	@TURN ON gpio 20 , TURN OFF gpio 21
	str r1,[r0,#GPSET0]	
	str r3,[r0,#GPCLR0]	
	@DELAY
	mov r10,#0
	delay:@loop to large number
		add r10,r10,#1
		cmp r10,r2	
		bne delay
	@TURN OF gpio 20 , TURN ON gpio 21
	str r1,[r0,#GPCLR0]	
	str r3,[r0,#GPSET0]	
	@DELAY2
	mov r10,#0
	delay2:
		add r10,r10,#1
		cmp r10,r2	
		bne delay2
b Infinite_loop
