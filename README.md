# aarch64-bare-metal-qemu
simple aarch64 bare metal 'Hello World' on qemu

Since I didn't write bare metal program on ARMv8/aarch64 before, I'll just do one.

1. starting from https://balau82.wordpress.com/2010/02/28/hello-world-for-bare-metal-arm-using-qemu/ seems a good idea
2. the toolchain is different, we need aarch64 cross compile toolchain. I think both linux and bare metal toolchains work for my testing purpose. However, I'll use bare metal one from linaro (http://releases.linaro.org/14.11/components/toolchain/binaries/aarch64-none-elf/gcc-linaro-4.9-2014.11-x86_64_aarch64-elf.tar.xz)
3. startup.s needs a bit tweek. We cannot ldr a value to the stack pointer (sp) directly. So I load the starting address of stack to x30, then load x30 into sp.
4. my modified startup.s is named [startup64.s](startup64.s) which is compiled into startup64.o by 'aarch64-none-elf-as -g startup64.s -o startup64.o'
5. One of the working aarch64 targets of qemu is virt, a look into qemu's [hw/arm/virt.c](http://git.qemu.org/?p=qemu.git;a=blob_plain;f=hw/arm/virt.c;hb=HEAD) shows that the memory mapped UART0 is located at 0x0900000. So the UART0DR in test.c should be changed to 0x09000000. My modified test.c is called [test64.c](test64.c), which is compiled into .o by 'aarch64-none-elf-gcc -c -g test64.c -o test64.o'
6. The address to load the program to should be changed too. '0x10000' is not valid RAM or ROM address for -M virt. According to virt.c, '0x40000000' is OK to use. So my linker script is modified and named [test64.ld](test64.ld)
7. I use 'aarch64-none-elf-ld -T test64.ld test64.o startup64.o -o test64.elf' to generate test64.elf
8. That's it. Since qemu can load elf directly now. We can use 'qemu-system-aarch64 -M virt -cpu cortex-a57 -nographic  -kernel test64.elf' to run the elf and see 'Hello Wolrd!'.

# How to run?

*	GDB (Terminal 1/2 should be in the same directory.)
	```
	Terminal 1:
		qemu-system-aarch64 -machine virt -cpu cortex-a57 -kernel kernel.elf -nographic -S -s
	Terminal 2:
		aarch64-linux-gnu-gdb kernel.elf --tui
		target remote :1234
	```
*	Timer IRQ works. It assert Timer_Handler() every 1 sec.
	```
	timer_test
	gic_v3_initialize()
	init_gicd()
	init_gicc()
	CurrentEL = 0x00000000 00000004
	RVBAR_EL1 = 0x00000000 00000000
	VBAR_EL1 = 0x00000000 40000000
	DAIF = 0x00000000 000003C0
	Disable the timer, CNTV_CTL_EL0 = 0x00000000 00000000
	System Frequency: CNTFRQ_EL0 = 0x00000000 03B9ACA0
	Current counter: CNTVCT_EL0 = 0x00000000 0001BA16
	Assert Timer IRQ after 1 sec: CNTV_CVAL_EL0 = 0x00000000 03BB66B6
	Enable the timer, CNTV_CTL_EL0 = 0x00000000 00000001
	Enable IRQ, DAIF = 0x00000000 00000340

	Exception Handler! (AARCH64_EXC_IRQ_SPX)
	IRQ found: 0x00000000 0000001B
	timer_handler:
			Disable the timer, CNTV_CTL_EL0 = 0x00000000 00000000
			System Frequency: CNTFRQ_EL0 = 0x00000000 03B9ACA0
			Current counter: CNTVCT_EL0 = 0x00000000 03BD40D5
			Assert Timer IRQ after 0x00000000 00000001 sec(s): CNTV_CVAL_EL0 = 0x00000000 0776ED75
			Enable the timer, CNTV_CTL_EL0 = 0x00000000 00000001

	Exception Handler! (AARCH64_EXC_IRQ_SPX)
	IRQ found: 0x00000000 0000001B
	timer_handler:
			Disable the timer, CNTV_CTL_EL0 = 0x00000000 00000000
			System Frequency: CNTFRQ_EL0 = 0x00000000 03B9ACA0
			Current counter: CNTVCT_EL0 = 0x00000000 0778E288
			Assert Timer IRQ after 0x00000000 00000001 sec(s): CNTV_CVAL_EL0 = 0x00000000 0B328F28
			Enable the timer, CNTV_CTL_EL0 = 0x00000000 00000001
	```

# Reference
*	Project
	*   [aarch64-bare-metal-qemu](https://github.com/freedomtan/aarch64-bare-metal-qemu)
	*   [raspberrypi](https://github.com/eggman/raspberrypi)
	*   [sample-tsk-sw](https://github.com/takeharukato/sample-tsk-sw)
*   QEMU
	*   [QEMU version 2.12.50 User Documentation](https://qemu.weilnetz.de/doc/qemu-doc.html)
*   Makefile
	*   [Makefile範例教學](http://maxubuntu.blogspot.com/2010/02/makefile.html)
	*   [GNU 的連結工具 (ld, nm, objdump, ar)](http://sp1.wikidot.com/gnulinker)
	*   [GCC Command-Line Options](http://tigcc.ticalc.org/doc/comopts.html)
	*   [LD Index](https://sourceware.org/binutils/docs/ld/LD-Index.html#LD-Index)
*	ARM
	*	[Arm® Compiler armasm User Guide](http://www.keil.com/support/man/docs/armclang_asm/armclang_asm_chunk708094578.htm)
	*	Application Note Bare-metal Boot Code for ARMv8-A Processors Version 1.0
	*	ARM® Architecture Reference Manual ARMv8, for ARMv8-A architecture profile Beta
	*	ARM® Cortex®-A57 MPCore™ Processor Revision: r1p0 Technical Reference Manual
	*	ARM® Cortex®-A Series Version: 1.0 Programmer’s Guide for ARMv8-A
	*	ARM® Generic Interrupt Controller Architecture Specification GIC architecture version 3.0 and version 4.0