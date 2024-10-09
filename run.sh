#!/bin/bash

sudo qemu-system-aarch64 -M virt -cpu cortex-a72 -m 512 -nographic  -kernel build/kernel.elf