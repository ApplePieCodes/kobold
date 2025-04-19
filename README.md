# The kobold kernel

The kobold kernel is an x86_64 kernel.

## Style Guidelines

Names are in camelCase.

Every file original to kobold should include the following header as a comment. If you contribute a meaningful change to the file, you can add your name as another set of name+contact.

The Kobold Kernel

[file path]
[month last updated (last modified in a commit)]

[full name](email/contact method(s));
[sources used]
This file is released under the GNU GPLv3. You can read the license at https://www.gnu.org/licenses/gpl-3.0.en.html

## Roadmap

### Milestone 1 - Userspace

[X] Terminal Output
[X] GDT
[X] PMM
[ ] VMM
[X] IDT
[ ] ACPI
[ ] APIC
[ ] HPET
[ ] SIMD
[ ] SMP
[ ] MultiTasking
[ ] Userspace

## Build Instructions

Run `./makeiso.sh`. It's that easy!