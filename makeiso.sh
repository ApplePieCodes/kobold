#!/bin/bash
set -e

if [ ! -d "build" ]; then
    meson setup build --cross-file x86_64.ini
fi

ninja -C build

# Clone limine if not already present
if [ ! -d "limine" ]; then
    git clone https://github.com/limine-bootloader/limine --branch=v9.x-binary --depth=1
fi

# Build limine
make -C limine

# Prepare ISO root directory
rm -rf iso_root
mkdir -p iso_root/boot
cp -v build/kobold iso_root/boot/

mkdir -p iso_root/boot/limine
cp -v limine.conf iso_root/boot/limine/

mkdir -p iso_root/EFI/BOOT
cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine/
cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/

# Create ISO
xorriso -as mkisofs \
  -R -r -J \
  -b boot/limine/limine-bios-cd.bin \
  -no-emul-boot -boot-load-size 4 -boot-info-table \
  -hfsplus -apm-block-size 2048 \
  --efi-boot boot/limine/limine-uefi-cd.bin \
  -efi-boot-part --efi-boot-image --protective-msdos-label \
  iso_root -o kobold.iso

# Install limine to ISO
./limine/limine bios-install kobold.iso
