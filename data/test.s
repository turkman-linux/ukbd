.section .text
.global _start

_start:
    mov $0x21,%rdi
    call ukbd_send

    mov $0x23,%rdi
    call ukbd_press

    mov $0x23,%rdi
    call ukbd_release

    mov $60,%rax
    mov $0,%rdi
    syscall
