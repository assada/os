# Simple OS implementation

DeadOS is a minimalist operating system designed for x86 architecture, created solely for educational purposes. It is an ideal platform for learning and understanding the fundamental concepts of operating system development. While it is not intended to evolve into a fully-fledged OS, DeadOS provides a straightforward and manageable codebase that makes it perfect for experimentation and study.

## Requirements

- make
- GCC Cross-Compiler
- QEMU

## How to run

- `make`
- `qemu-system-x86_64 -monitor stdio -cdrom deados.iso`

## Features

- [x] Bootloader
- [x] Kernel
- [x] VGA Driver
- [x] Keyboard Driver
- [x] Shell
- [x] Basic commands
- [x] Timers
- [x] Interrupts
- [x] Kernel Extensions handling
- [ ] Paging
- [] Memory Management
- [] File System
- [x] User Space
- [x] Syscalls
- [ ] Multitasking
- [] stdlib

## Screenshot:

![image](https://github.com/assada/os/assets/1472664/9b67c053-36e1-4816-ad7f-093b89b03fce)
