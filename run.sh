#!/bin/bash

sudo qemu-system-aarch64 -M virt -cpu cortex-a72 -nographic  -kernel build/kernel.elf