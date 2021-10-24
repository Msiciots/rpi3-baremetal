bin = kernel.img
elf = kernel.elf
obj = kernel.o				
code = turn_led_on.s   	                       
		
$(bin) : $(elf)
	arm-none-eabi-objcopy $(elf) -O binary $(bin)

$(elf) : $(obj)
	arm-none-eabi-ld $(obj) -o $(elf) 


$(obj) : $(code)
	arm-none-eabi-as -g -o $(obj) $(code)

clean:					
	rm *.o#@will remove all files with .o extension
