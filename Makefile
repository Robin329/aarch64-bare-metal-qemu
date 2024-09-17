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
CFLAGS =  -mcpu=cortex-a72 -Wall -Wextra -g

CFILES = $(wildcard *.c)
SFILES = $(wildcard *.S)
OBJS = $(addprefix $(OUTPUT)/, $(CFILES:.c=.o) $(SFILES:.S=.o))

all: $(IMAGE) kernel.bin

$(OUTPUT)/%.o: %.c | $(OUTPUT)
	$(CROSS_PREFIX)gcc -c $< -o $@

$(OUTPUT)/%.o: %.S | $(OUTPUT)
	# $(CROSS_PREFIX)as -c $< -o $@
	$(CC) ${CFLAGS} -c $< -o $@			# for include header file in assembly

$(IMAGE): $(OFILES) ${OBJS} | $(OUTPUT)
	$(CROSS_PREFIX)ld -nostdlib -Tlinker.ld $^ -o $@
	${OBJDUMP} -D $(OUTPUT)/kernel.elf > $(OUTPUT)/kernel.list

kernel.bin: $(IMAGE)
	$(CROSS_PREFIX)objcopy -O binary $< $@

run:
	$(MAKE)
	sudo qemu-system-aarch64 -M virt -cpu cortex-a72 -nographic -kernel build/kernel.elf

clean:
	rm -f build/*
build:
	mkdir -p build