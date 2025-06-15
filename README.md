# Simple OS implementation

[![Build ISO](https://github.com/assada/os/actions/workflows/build-dead-iso.yml/badge.svg)](https://github.com/assada/os/actions/workflows/build-dead-iso.yml)

DeadOS is a minimalist operating system designed for educational purposes. The code is organised so that architecture specific files live under `arch/<arch>` directories. The default architecture remains `x86`.

## Requirements

- make
- GCC Cross-Compiler
- QEMU

## How to run

- `make`
- `qemu-system-x86_64 -cdrom deados.iso -boot d -m 256 -serial stdio`

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
- [x] Paging
- [ ] Memory Management
- [ ] File System
- [x] User Space
- [x] Syscalls
- [ ] Multitasking
- [ ] stdlib

## Screenshot:

![image](https://github.com/assada/os/assets/1472664/b4e17d66-cb85-4652-9217-11608ad0753d)

