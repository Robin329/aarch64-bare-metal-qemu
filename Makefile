osname := $(shell uname -s)

#use Android toolchain on OS X
#use linaro bare metal toolchain on linux
ifeq ($(osname), Darwin)
CROSS_PREFIX=aarch64-linux-android-
else
CROSS_PREFIX=aarch64-linux-gnu-
endif

OUTPUT := build
IMAGE  := $(OUTPUT)/kernel.elf

CC = ${CROSS_PREFIX}gcc
AS = ${CROSS_PREFIX}as
LD = ${CROSS_PREFIX}ld
OBJDUMP = ${CROSS_PREFIX}objdump
CFLAGS       =  -mcpu=cortex-a57 -ffreestanding -mlittle-endian -Wall -Wextra -g -nostartfiles -fno-builtin 
CFLAGS      += -mgeneral-regs-only -nostartfiles -nodefaultlibs
CFLAGS		+= -I. 
LDFLAGS		:=	-Bstatic \
			-Tlinker.ld \
			-nostdlib -nostartfiles -nodefaultlibs

CFILES = $(wildcard *.c)
SFILES = $(wildcard *.S)
OBJS = $(addprefix $(OUTPUT)/, $(CFILES:.c=.o) $(SFILES:.S=.o))

# OBJS = boot.o printk.o uart.o kernel.o gic_v3.o exception.o aarch64.o psw.o timer.o uart.o vector.o

all: $(IMAGE) kernel.bin

$(OUTPUT)/%.o: %.c | $(OUTPUT)
	$(CROSS_PREFIX)gcc -c $< -o $@

$(OUTPUT)/%.o: %.S | $(OUTPUT)
	# $(CROSS_PREFIX)as -c $< -o $@
	$(CC) ${CFLAGS} -c $< -o $@			# for include header file in assembly

$(IMAGE): $(OFILES) ${OBJS} | $(OUTPUT)
	$(CROSS_PREFIX)ld $(LDFLAGS) $^ -o $@
	${OBJDUMP} -D $(OUTPUT)/kernel.elf > $(OUTPUT)/kernel.list

kernel.bin: $(IMAGE)
	$(CROSS_PREFIX)objcopy -O binary $< $@
gdb:
	sudo qemu-system-aarch64 -cpu cortex-a72 -machine virt,gic-version=3 -smp 4 -m 256  -nographic -kernel build/kernel.elf -S -s

run:
	clear
	$(MAKE)
	sudo qemu-system-aarch64 -M virt -cpu cortex-a72  -m 512 -nographic -kernel build/kernel.elf
	$(OBJDUMP) -D build/kernel.elf > objdump.txt

clean:
	rm -f build/*
build:
	mkdir -p build