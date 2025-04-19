local function main()
    objects = {}

    for i, file in ipairs(kobuild_c_files) do
        local obj = file:gsub("%.c$", ".o")  -- replace .c with .o
        table.insert(objects, obj)
        local command = "x86_64-elf-gcc -c " .. file .. " " .. c_args .. " -o " .. obj
        local handle = io.popen(command .. " 2>&1")  -- capture stderr
        local result = handle:read("*a")
        handle:close()

        print(result)
    end

    for i, file in ipairs(kobuild_nasm_files) do
        local obj = file:gsub("%.asm$", ".o")  -- replace .c with .o
        table.insert(objects, obj)
        local command = "nasm -felf64 -w+orphan-labels " .. file .. " -o " .. obj
        local handle = io.popen(command .. " 2>&1")  -- capture stderr
        local result = handle:read("*a")
        local ok, exit, code = handle:close()
    end

    local link_command = "x86_64-elf-gcc -nostdlib -T res/linker/linker-x86_64.ld -o kobold " .. table.concat(objects, " ")
    local handle = io.popen(link_command .. " 2>&1")
    local result = handle:read("*a")
    handle:close()

    print(result)
    os.execute("rm -rf " .. table.concat(objects, " "))

    if not directory_exists("limine") then
        os.execute("git clone https://github.com/limine-bootloader/limine --branch=v9.x-binary --depth=1")
    end
    
    os.execute("make -C limine")
    os.execute("rm -rf iso_root")
    os.execute("mkdir -p iso_root/boot")
    os.execute("cp -v kobold iso_root/boot/")
    os.execute("mkdir -p iso_root/boot/limine")
    os.execute("cp -v limine.conf iso_root/boot/limine/")
    os.execute("mkdir -p iso_root/EFI/BOOT")
    os.execute("cp -v limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine/")
    os.execute("cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/")
    os.execute("cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/")
    os.execute("xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label iso_root -o kobold.iso")
    os.execute("./limine/limine bios-install kobold.iso")
end

main()