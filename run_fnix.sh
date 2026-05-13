#!/bin/bash

# Script to install QEMU via Homebrew and run FNIX OS

echo "Installing QEMU via Homebrew..."
brew install qemu

echo "Running FNIX OS..."
qemu-system-i386 -kernel fnix.elf

echo "FNIX OS execution completed."