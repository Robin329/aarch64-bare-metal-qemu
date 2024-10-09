shell echo "Waiting for 1 secs..."
shell sleep 1
shell echo "Executing gdb commands in local .gdbinit ..."

shell echo  "(gdb) target remote :1234"
target remote :1234

shell sleep 1
file build/kernel.elf

shell sleep 1
shell echo  "(gdb) break main"
break main

shell sleep 1
shell echo  "gdb bt"
bt
